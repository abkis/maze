#include <windows.h>
#include "grid.h"
#include "maze.h"
#include <iostream>
#include <string>
#include "robot.h"

void CreateConsole() {
    AllocConsole();  // Allocates a new console for the calling process
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);  // Redirect stdout to the console
    std::cout.clear();
}

// bitmaps for maze
HBITMAP hMazeBitmap = nullptr;
HDC hdcMaze = nullptr;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// data to pass to window creation
struct WindowData {
    Grid* grid;
    Robot* robot;
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"GridWindowClass";
    CreateConsole();
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Set up custom grid
    Grid* grid = new Grid(ROWS, COLS, MAX_WEIGHT);
    grid->make_maze(END_WEIGHT);
    grid->remove_walls(REMOVE_WALLS);

    // create display
    std::shared_ptr<Display> display{ std::make_shared<Display>((HWND)GetForegroundWindow(), CreateSolidBrush(RGB(255, 0, 0))) };

    // create robot
    Robot* robot = new Robot{ grid->get_start(), grid->get_end(), display };

    // Set up WindowData
    WindowData* windowData = new WindowData{ grid, robot };

    // Create the window and pass the WindowData pointer via lParam
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Grid Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, windowData);  // Pass windowData as lParam

    if (hwnd == nullptr) {
        std::cout << "Oh No" << std::endl;
        delete grid;
        delete robot;
        delete windowData;
        return 0;
    }
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Clean up
    delete grid;
    delete robot;
    delete windowData;

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static WindowData* windowData = nullptr;
    
    // Get window dimensions
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    int windowWidth = COLS * SQUARE_SIZE;// clientRect.right - clientRect.left;
    int windowHeight = COLS * SQUARE_SIZE; // clientRect.bottom - clientRect.top;

    switch (uMsg) {

    case WM_CREATE: {
        HDC hdc = GetDC(hwnd);

        // get info passed from params
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        windowData = (WindowData*)pCreate->lpCreateParams;

        // Continue with your grid and display setup...
        Grid* grid = windowData->grid;
        Robot* robot = windowData->robot;

        // Create a memory device context and compatible bitmap for the maze
        hdcMaze = CreateCompatibleDC(hdc);
        hMazeBitmap = CreateCompatibleBitmap(hdc, windowWidth, windowHeight);
        SelectObject(hdcMaze, hMazeBitmap);

        // draw grid
        // Create brushes for black and white
        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));

        // Draw the grid of squares with walls
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                // Determine the rectangle for each square
                RECT rect;
                rect.left = col * SQUARE_SIZE;
                rect.top = row * SQUARE_SIZE;
                rect.right = rect.left + SQUARE_SIZE;
                rect.bottom = rect.top + SQUARE_SIZE;

                std::shared_ptr<Block> block = (*grid)[row][col];
                block->set_location(rect.left, rect.right, rect.top, rect.bottom);

                // Fill the square with white color
                FillRect(hdcMaze, &rect, whiteBrush);

                // Draw black lines where there are walls
                if (block) {
                    // shade depending on weight, can't be negative ofc
                    // Convert integer to wide string
                    std::wstring numStr = std::to_wstring(block->weight);

                    // Draw the number as text in the center of the block
                    DrawText(hdcMaze, numStr.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

                    // Get the coordinates for the square's edges
                    int left = rect.left;
                    int right = rect.right;
                    int top = rect.top;
                    int bottom = rect.bottom;

                    // Check each wall and draw a black line if the wall exists
                    if (block->walls[UP]) { // Top wall
                        RECT topWall = { left, top, right, top + WALL_THICKNESS };
                        FillRect(hdcMaze, &topWall, blackBrush);
                    }
                    if (block->walls[DOWN]) { // Bottom wall
                        RECT bottomWall = { left, bottom - WALL_THICKNESS, right, bottom };
                        FillRect(hdcMaze, &bottomWall, blackBrush);
                    }
                    if (block->walls[LEFT]) { // Left wall
                        RECT leftWall = { left, top, left + WALL_THICKNESS, bottom };
                        FillRect(hdcMaze, &leftWall, blackBrush);
                    }
                    if (block->walls[RIGHT]) { // Right wall
                        RECT rightWall = { right - WALL_THICKNESS, top, right, bottom };
                        FillRect(hdcMaze, &rightWall, blackBrush);
                    }

                    if (block->is_end) {
                        RECT bottomWall = { left, bottom - WALL_THICKNESS, right, bottom };
                        FillRect(hdcMaze, &bottomWall, redBrush);
                    }

                    if (block->is_start) {
                        RECT leftWall = { left, top, left + WALL_THICKNESS, bottom };
                        FillRect(hdcMaze, &leftWall, redBrush);
                    }
                }
            }
        }

        // Cleanup
        DeleteObject(blackBrush);
        DeleteObject(whiteBrush);
        DeleteObject(redBrush);
        ReleaseDC(hwnd, hdc);
        return 0;
    }

    case WM_PAINT: {
        if (windowData == nullptr) {
            break;  // Ensure windowData is valid before painting
        }

        PAINTSTRUCT ps;
        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
        HDC hdc = BeginPaint(hwnd, &ps);

        // Get window dimensions again (if needed)
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        int windowWidth = COLS * SQUARE_SIZE;
        int windowHeight = ROWS * SQUARE_SIZE;

        // Copy the pre-rendered maze from the off-screen bitmap
        BitBlt(hdc, 0, 0, windowWidth, windowHeight, hdcMaze, 0, 0, SRCCOPY);

        // Draw the robot's position as a red circle
        Robot* robot = windowData->robot;
        SelectObject(hdc, redBrush);  // Use the red brush to draw the robot
        Ellipse(hdc, robot->get_left(), robot->get_up(), robot->get_right(), robot->get_down());

        DeleteObject(redBrush);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

}

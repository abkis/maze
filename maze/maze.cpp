#include <windows.h>
#include "grid.h"
#include <iostream>

void CreateConsole() {
    AllocConsole();  // Allocates a new console for the calling process
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);  // Redirect stdout to the console
    std::cout.clear();
}

const int SQUARE_SIZE = 50; // Size of each square in pixels
const int ROWS = 10;        // Number of rows in the grid
const int COLS = 10;        // Number of columns in the grid

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"GridWindowClass";
    //CreateConsole();
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"Grid Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        nullptr, nullptr, hInstance, nullptr);

    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Create brushes for black and white
        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));

        // Set up custom grid
        Grid grid = Grid(ROWS, COLS);
        grid.make_maze();

        // Draw the grid of alternating black and white squares
        for (int row = 0; row < ROWS; ++row) {
            for (int col = 0; col < COLS; ++col) {
                // Determine the rectangle for each square
                RECT rect;
                rect.left = col * SQUARE_SIZE;
                rect.top = row * SQUARE_SIZE;
                rect.right = rect.left + SQUARE_SIZE;
                rect.bottom = rect.top + SQUARE_SIZE;

                std::weak_ptr<Block> curr = grid[row][col];

                // Choose black or white based on the row and column indices
                HBRUSH brush = ((row + col) % 2 == 0) ? blackBrush : whiteBrush;

                // unless have at least one open wall
                for (auto wall : curr.lock()->walls) {
                    if (!wall) {
                        brush = redBrush;
                        break;
                    }
                }

                FillRect(hdc, &rect, brush);
            }
        }

        // Cleanup brushes
        DeleteObject(blackBrush);
        DeleteObject(whiteBrush);

        EndPaint(hwnd, &ps);
    }
                 return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
}

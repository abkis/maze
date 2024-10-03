#include "display.h"

Display::Display(HWND window, HBRUSH displayBrush) : 
	window{window}, displayBrush{displayBrush} {}

// trigger WM_PAINT to redraw this portion of the maze
void Display::display_char() {
    // Redraw the window to show the updated position
    InvalidateRect(window, nullptr, TRUE);
    UpdateWindow(window);  // Ensures the window is updated immediately

    // Control the speed of the movement
    Sleep(500);  // 500ms pause between steps
}
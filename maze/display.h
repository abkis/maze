#pragma once
#include <windows.h>

// handle display of robot
class Display
{
	HWND window; // window to display to
	HBRUSH displayBrush; // color to display

public:
	Display(HWND window, HBRUSH displayBrush);

	void display_char(); // call this to display character
};


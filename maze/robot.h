#pragma once
#include "block.h"
#include "display.h"

// define "robot" class that goes thru maze and tries to solve it for best path
class Robot
{
	int points{ 0 }; // collect points as go thru maze, want to maximize this

	std::shared_ptr<Block> curr; // keep track of which block robot is at
	std::shared_ptr<Block> goal; // location of "exit" block

	std::shared_ptr<Display> display; // class for forcing robo display

public:
	Robot(std::shared_ptr<Block> start, std::shared_ptr<Block> end, std::shared_ptr<Display> display);

	void search();

	RECT get_rect() const; // return rect obj of location of robot 
};


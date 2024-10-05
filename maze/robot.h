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
	Robot(const std::shared_ptr<Block>& start, const std::shared_ptr<Block>& end, const std::shared_ptr<Display>& display);

	void search();

	int get_left() const; // return left obj of location of robot 

	int get_up() const;

	int get_down() const;

	int get_right() const;

};


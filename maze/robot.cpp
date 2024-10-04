#include "robot.h"

Robot::Robot(std::shared_ptr<Block> start, std::shared_ptr<Block> end, std::shared_ptr<Display> display) :
	curr{ start }, goal{ end }, display{ display } {}

void Robot::search() {
	// A* search to find best path
	
	display->display_char();
}

RECT Robot::get_rect() const {
	if (curr) {
		return curr->location;
	}
	return RECT();
}
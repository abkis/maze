#include "robot.h"
#include <iostream>

Robot::Robot(const std::shared_ptr<Block>& start, const std::shared_ptr<Block>& end, const std::shared_ptr<Display>& display) :
	curr{ start }, goal{ end }, display{ display } {}

void Robot::search() {
	// A* search to find best path
	
	display->display_char();
}

int Robot::get_left() const {
	return curr->location[LEFT];
}

int Robot::get_right() const {
	return curr->location[RIGHT];
}

int Robot::get_up() const {
	return curr->location[UP];
}

int Robot::get_down() const {
	return curr->location[DOWN];
}
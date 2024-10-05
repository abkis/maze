#include "block.h"

Block::Block(int weight, bool wall_up, bool wall_down, bool wall_left, bool wall_right) :
	walls{wall_up, wall_down, wall_left, wall_right}, weight{weight}
	{}

void Block::set_location(int left, int right, int top, int bottom) {
	location[UP] = top;
	location[DOWN] = bottom;
	location[LEFT] = left;
	location[RIGHT] = right;
}

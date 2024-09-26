#include "block.h"

Block::Block(bool wall_left, bool wall_right, bool wall_up, bool wall_down) : 
	wall_left{wall_left}, wall_right{wall_right}, wall_up{wall_up}, wall_down{wall_down},
	right{nullptr}, left{nullptr}, up{nullptr}, down{nullptr}
	{}

Block::~Block() {
	if (right) {
		delete right;
	}
	if (down) {
		delete down;
	}
	if (left) {
		delete left;
	}
	if (up) {
		delete up;
	}
}

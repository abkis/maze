#include "Block.h"
#include "cmath"

Block::Block(int x0, int y0, int x1, int y1, bool wall_left, bool wall_right, bool wall_up, bool wall_down) : 
	x0{x0}, x1{x1}, y0{y0}, y1{y1}, size{abs(x1-x0)*abs(y1-y0)}, 
	wall_left{wall_left}, wall_right{wall_right}, wall_up{wall_up}, wall_down{wall_down},
	right{nullptr}, left{nullptr}, up{nullptr}, down{nullptr}
	{}

Block::Block(int x0, int y0, int length, bool wall_left, bool wall_right, bool wall_up, bool wall_down) :
	x0{x0}, y0{y0}, size{length*length}, x1{x0+length}, y1{y0+length},
	wall_left{ wall_left }, wall_right{ wall_right }, wall_up{ wall_up }, wall_down{ wall_down },
	right{ nullptr }, left{ nullptr }, up{ nullptr }, down{ nullptr }
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

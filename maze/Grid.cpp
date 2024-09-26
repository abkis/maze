
#include "Grid.h"
#include <stdexcept>

Grid::Grid(unsigned int width, unsigned int height) {
	if (width == 0 || height == 0) {
		throw std::invalid_argument("Cannot have grid of zero size");
	}
	this->width = width;
	this->height = height;
	size = width * height;

	// init grid of correct size by creating appropriate number of blocks
	// initial block should not have a wall_left 

	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; i < width; ++i) {

		}
	}
}

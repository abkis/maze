
#include "grid.h"
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
		std::vector<Block*> temp;
		for (unsigned int j = 0; j < width; ++j) {
			if (i == 0 && j == 0) {
				// first block
				temp.push_back(new Block(false));
			}
			else {
				temp.push_back(new Block()); // defaults to "true" for all walls
			}
		}
		grid.push_back(temp);
	}

	// have blocks, now connect them
	for (unsigned int i = 0; i < height; ++i) {
		for (unsigned int j = 0; j < width; ++j) {
			Block* curr = grid[i][j];
			if (i > 0) {
				curr->up = grid[i - 1][j];
			}
			if (i + 1 < height) {
				curr->down = grid[i + 1][j];
			}
			if (j > 0) {
				curr->left = grid[i][j - 1];
			}
			if (j + 1 < width) {
				curr->right = grid[i][j + 1];
			}
		}
	}
}

std::vector<std::vector<Block*>>& Grid::get_grid() { return grid; }

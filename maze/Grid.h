#pragma once
#include "block.h"
#include <vector>

// grid of blocks
class Grid
{
	unsigned int width, height, size;

	// use vector of block vectors to mimick array
	// hold series of block object pointers that make up grid
	std::vector<std::vector<Block*>> grid; // TODO: is there more memory-efficient way to store this?

public:
	Grid(unsigned int width, unsigned int height);

	std::vector<std::vector<Block*>>& get_grid();
};


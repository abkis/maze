#pragma once
#include "Block.h"

// grid of blocks
class Grid
{
	unsigned int width, height, size;

	Block* start; // maze always starts at upper-left spot

public:
	Grid(unsigned int width, unsigned int height);
	~Grid();
};


#pragma once
#include "block.h"
#include <vector>
#include "memory"

// grid of blocks
class Grid
{
	// width == columns, height == rows
	int width, height, size;


	// use vector of block vectors to mimick array
	// hold series of block object pointers that make up grid
	std::vector<std::vector<std::shared_ptr<Block>>> grid; // TODO: is there more memory-efficient way to store this?

public:
	Grid(int width, int height);

	void make_maze(); // randomized depth-first search maze generation algo

	// Overload operator[] to return a reference to grid
	std::vector<std::shared_ptr<Block>>& operator[](size_t row) {
		return grid[row];  
	}

	const std::vector<std::shared_ptr<Block>>& operator[](size_t row) const {
		return grid[row];  
	}
};


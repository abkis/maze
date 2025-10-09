#pragma once
#include "block.h"
#include <vector>
#include "memory"
#include "constants.h"

// grid of blocks
class Grid
{
	// width == columns, height == rows
	int width, height, size;

	std::weak_ptr<Block> start, end; // track where to enter/exit maze

	// use vector of block vectors to mimick array
	// hold series of block object pointers that make up grid
	std::vector<std::vector<std::shared_ptr<Block>>> grid; // TODO: is there more memory-efficient way to store this?

public:
	Grid(int width, int height);

	void make_maze(); // randomized depth-first search maze generation algo

	inline std::weak_ptr<Block> get_start() const { return start; }

	// Overload operator[] to return a reference to grid
	std::vector<std::shared_ptr<Block>> &operator[](size_t row)
	{
		return grid[row];
	}

	const std::vector<std::shared_ptr<Block>> &operator[](size_t row) const
	{
		return grid[row];
	}

	inline const std::shared_ptr<Block> get_block(size_t row, size_t col) const
	{
		return grid[row][col];
	}
};

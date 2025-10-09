#pragma once

// class hollding info abt each block
// window is made up of a certain number of blocks

#include <vector>
#include <memory>
#include "constants.h"

class Block
{
	bool robot_location = false;
	float cost{1};

	// will have up to four blocks ("nodes") it connects to
	// ORDER: Up, Down, Left, Right
	std::vector<std::weak_ptr<Block>> neighbors;
	std::pair<int, int> coords; // coorinate in maze

	bool in_maze{false};  // set to true if maze generation algo has already seen it
	bool is_end{false};	  // set to true => final spot
	bool is_start{false}; // set to true => maze  start

	bool is_GR{false}; // set to true if in goal region

	bool seen{false}; // set to true if visited by robot

	// has zero to four walls
	// up, down, left, right
	std::vector<bool> walls;

public:
	Block(int i, int j, float cost = 1, bool U = true, bool D = true, bool L = true, bool R = true);

	inline bool wall_up() const { return walls[UP]; };
	inline bool wall_down() const { return walls[DOWN]; };
	inline bool wall_left() const { return walls[LEFT]; };
	inline bool wall_right() const { return walls[RIGHT]; };

	inline void set_robot(bool here) { robot_location = here; };

	inline bool has_robot() const { return robot_location; };
	inline bool block_in_maze() const { return in_maze; };
	inline bool block_is_end() const { return is_end; };
	inline bool block_is_start() const { return is_start; };
	inline bool block_in_GR() const { return is_GR; };
	inline float get_cost() const { return cost; };

	inline void toggle_maze() { in_maze = !in_maze; };
	inline void set_start() { is_start = true; };
	inline void set_end() { is_end = true; };
	inline void set_GR() { is_GR = true; };

	inline bool wall_at(DIR dir) const { return walls[dir]; };

	inline void set_seen() { seen = true; };
	inline bool was_seen() const { return seen; };
	inline std::pair<int, int> get_coords() const { return coords; }

	inline size_t num_neighbors() const { return neighbors.size(); };

	inline std::vector<std::weak_ptr<Block>> get_neighbors() const { return neighbors; };

	friend class Grid;
};

#pragma once

// class hollding info abt each block
// window is made up of a certain number of blocks

#include <vector>
#include <memory>

class Block
{
public:

	// will have up to four blocks ("nodes") it connects to
	// ORDER: Up, Down, Left, Right
	std::vector<std::weak_ptr<Block>> neighbors;

	bool in_maze{ false }; // set to true if maze generation algo has already seen it

	// has zero to four walls
	std::vector<bool> walls;

	Block(bool U=true, bool D=true, bool L = true, bool R = true);

};


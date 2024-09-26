#pragma once
#include <winapifamily.h>

// color that block can take
// white => wall, black => empty space
enum class BlockColor { WHITE, BLACK };

// class hollding info abt each block
// should be square with specified color (default is black)
// use to build maze == linked list (tree) of blocks
// window is made up of a certain number of blocks

class Block
{
	int x0, y0, x1, y1; // use to mark box corners
	int size; // width * height of box

public:

	// will have up to four blocks ("nodes") it connects to

	Block* right;
	Block* left; 
	Block* up;
	Block* down;

	// has zero to four walls

	bool wall_left{ true }, wall_right{ true }, wall_up{ true }, wall_down{ true };

	Block(int x0, int y0, int x1, int y1, bool wall_left=true, bool wall_right=true, bool wall_up=true, bool wall_down=true);
	Block(int x0, int y0, int length, bool wall_left = true, bool wall_right = true, bool wall_up = true, bool wall_down = true);
	~Block();

};


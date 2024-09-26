#pragma once

// class hollding info abt each block
// window is made up of a certain number of blocks

class Block
{
public:

	// will have up to four blocks ("nodes") it connects to

	Block* right;
	Block* left; 
	Block* up;
	Block* down;

	// has zero to four walls

	bool wall_left{ true }, wall_right{ true }, wall_up{ true }, wall_down{ true };

	Block(bool wall_left=true, bool wall_right=true, bool wall_up=true, bool wall_down=true);
	Block(bool wall_left = true, bool wall_right = true, bool wall_up = true, bool wall_down = true);
	~Block();

};


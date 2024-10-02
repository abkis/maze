
#include "grid.h"
#include <stdexcept>
#include <stdlib.h>

Grid::Grid(int width, int height) {
	if (width <= 0 || height <= 0) {
		throw std::invalid_argument("Cannot have grid of zero or negative size");
	}
	this->width = width;
	this->height = height;
	size = width * height;

	// init grid of correct size by creating appropriate number of blocks
	// initial block should not have a wall_left 

	for (int i = 0; i < height; ++i) {
		std::vector<std::shared_ptr<Block>> temp;
		for (int j = 0; j < width; ++j) {
			temp.push_back(std::make_shared<Block>()); // defaults to "true" for all walls
		}
		grid.push_back(temp);
	}

	// have blocks, now connect them
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			std::shared_ptr<Block> curr = grid[i][j];
			if (curr->neighbors.size() == 0) {
				// need to add neighbors!
				// order: Up, Down, Left, Right
				if (i > 0) {
					curr->neighbors.push_back(grid[i - 1][j]);
				}
				else {
					curr->neighbors.push_back(std::weak_ptr<Block>());
				}

				if (i + 1 < height) {
					curr->neighbors.push_back(grid[i + 1][j]);
				}
				else {
					curr->neighbors.push_back(std::weak_ptr<Block>());
				}

				if (j > 0) {
					curr->neighbors.push_back(grid[i][j-1]);
				}
				else {
					curr->neighbors.push_back(std::weak_ptr<Block>());
				}

				if (j + 1 < width) {
					curr->neighbors.push_back(grid[i][j + 1]);
				}
				else {
					curr->neighbors.push_back(std::weak_ptr<Block>());
				}
			}
		}
	}
}


void Grid::make_maze() {

	std::vector<std::weak_ptr<Block>> stack; // add visited nodes here so can easily backtrack

	// get random values for where to start maze gen
	int col{ rand() % width }, row{ rand() % height };

	std::weak_ptr<Block> curr = grid[row][col];
	curr.lock()->in_maze = true; // mark as seen

	// add to stack 
	stack.push_back(curr);

	// repeat process while stack is nonempty
	while (!stack.empty()) {

		// grab current item
		curr = stack.back();
		stack.pop_back(); // remove last item from stack

		std::vector<size_t> indices; // possible indices of nbr vec we can move to

		// only allow random choice from non-visited neighbors
		for (size_t i = 0; i < curr.lock()->neighbors.size(); ++i) {
			auto nbr = curr.lock()->neighbors[i];
			if (nbr.lock() && !nbr.lock()->in_maze) {
				// make sure ptr has been assigned/is not expired
				indices.push_back(i);
			}
		}

		if (indices.empty()) {
			// no non-visited neighbors
			continue;
		}

		unsigned int index{ rand() % indices.size() }; //  index of next item to add to "seen" stack

		// grab next item to add to maze
		size_t nbr_index = indices[index];
		std::weak_ptr<Block> next = curr.lock()->neighbors[nbr_index];

		// remove wall bw curr and next, mark as seen, add to stack
		curr.lock()->walls[nbr_index] = false; // remove wall curr -> next
		curr.lock()->in_maze = true; // added to maze
		stack.push_back(curr); // update stack

		// need to remove wall next -> curr as well!
		// note: up <=> down & left <=> right when translated
		int next_nbr_index = mapping[nbr_index];

		next.lock()->walls[next_nbr_index] = false;
		next.lock()->in_maze = true;
		stack.push_back(next);
	}

	// start should be top leftmost & end is bottom rightmost
	start = grid[0][0];
	end = grid[height-1][width-1];

	// make sure no walls
	start.lock()->walls[LEFT] = false;
	start.lock()->is_start = true;

	end.lock()->walls[DOWN] = false;
	end.lock()->is_end = true;

}

void Grid::remove_walls(unsigned int remove) {
	unsigned int removed{ 0 }; // counter
	int max_it{ 0}; // make sure don't enter infinite loop

	while (removed < remove && max_it < size) {
		// get random val to determine which block to look at 
		int col{ rand() % (width - 1) + 1 }, row{ rand() % (height-1)+1 };
		std::weak_ptr<Block> block = grid[row][col];

		// get random value to determine which wall to remove
		unsigned int wall{ rand() %  block.lock()->walls.size()};

		if (block.lock()->walls[wall]) {
			block.lock()->walls[wall] = false;

			// need to remove neighbor's wall as well
			int nbr_wall = mapping[wall];
			std::weak_ptr<Block> neighbor = block.lock()->neighbors[wall];
			if (neighbor.lock()) {
				neighbor.lock()->walls[nbr_wall] = false;
			}

			++removed;
		}
		++max_it;
	}
}

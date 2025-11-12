#pragma once
#include "block.h"

class Robot
{
    std::weak_ptr<Block> location;
    float k1, k2;                   // weighting constants
    float N;                        // max distance to center of GR
    std::pair<int, int> end_coords; // end coordinates
    float goal_seeking_cost(const std::weak_ptr<Block> block, DIR direction) const;
    bool finished{false};

public:
    Robot(std::weak_ptr<Block> location, std::pair<int, int> end_coords, float k1 = K1, float k2 = K2);
    void traverse_maze(); // function called to try and traverse through maze
    void walk();          // function called to take a step in "right" direction

    inline bool at_end() const { return finished; }
};
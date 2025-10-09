#pragma once
#include "block.h"

class Robot
{
    std::weak_ptr<Block> location;

public:
    Robot(std::weak_ptr<Block> location);
    void traverse_maze(); // function called to try and traverse through maze
};
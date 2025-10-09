#include "robot.h"

Robot::Robot(std::weak_ptr<Block> location) : location{location}
{
    location.lock()->set_robot(true);
}

// reach end of maze
void Robot::traverse_maze()
{
    std::weak_ptr<Block> curr = location;
    while (!curr.lock()->block_is_end())
    {
        auto neighbors = curr.lock()->get_neighbors();
        for (auto &nbr : neighbors)
        {
        }
    }
}
#include "robot.h"
#include <cmath>

int manhattan(std::pair<int, int> start, std::pair<int, int> end)
{
    return std::abs(start.first - end.first) + std::abs(start.second - end.second);
}

Robot::Robot(std::weak_ptr<Block> location, std::pair<int, int> end_coords, float k1, float k2) : location{location},
                                                                                                  end_coords{end_coords}, k1{k1}, k2{k2}
{
    location.lock()->set_robot(true);
    // use manhattan distance for end coords
    std::pair<int, int> loc = location.lock()->get_coords();
    N = manhattan(loc, end_coords);
}

// obtain goal-seeking cost of block
// G_s = K_1G_D-K_2C+g where K_1,K_2 weighting constants
// C is cost of reaching frontier cell from current position
// g = 0 if frontier cell not in goal region GR, else g = N where
// N is largest possible distance between any cell in the grid and the centroid cell of GR
//  G_D = N-D_f where D_f is distance from frontier cell and CG
// Note: If frontier cells are in GR take K_1=0 to force simple exploratory behavior so robot stays in GR until reaching goal
// direction refers to direction robot must go in to reach block
float Robot::goal_seeking_cost(const std::weak_ptr<Block> block, DIR direction) const
{
    if (location.lock()->wall_at(direction))
    {
        // wall blocking it so cannot reach
        return std::numeric_limits<float>::min();
    }
    float g = block.lock()->block_in_GR() ? N : 0;
    float kone = block.lock()->block_in_GR() ? 0 : k1;
    int G_D = N - manhattan(block.lock()->get_coords(), end_coords);
    float C = block.lock()->get_cost();
    return kone * G_D - k2 * C + g;
}

// reach end of maze
void Robot::traverse_maze()
{
    std::weak_ptr<Block> curr = location;
    while (!curr.lock()->block_is_end())
    {
        // get all neighbors of current locataion
        auto neighbors = curr.lock()->get_neighbors();
        std::vector<std::pair<size_t, float>> frontier; // hold index of frontier in neighbor list
        // float is goal-seeking cost
        if (neighbors.size() > 0)
        {
            size_t i = 0;
            for (auto &nbr : neighbors)
            {
                if (nbr.lock()->was_seen())
                {
                    // block was already visited so not frontier
                    continue;
                }
                // block not yet visited so frontier
                frontier.push_back({i, goal_seeking_cost(nbr, (DIR)i)});
                ++i;
            }
        }
    }
}
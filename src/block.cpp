#include "block.h"

Block::Block(int i, int j, float cost, bool wall_up, bool wall_down, bool wall_left, bool wall_right) : walls{wall_up, wall_down, wall_left, wall_right},
                                                                                                        cost{cost}, coords{i, j}
{
}

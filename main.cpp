#include <SFML/Graphics.hpp>
#include "grid.h"
#include <memory>
#include "constants.h"
#include "robot.h"
#include "display.h"

int main()
{
    Grid maze(grid_width, grid_height);
    maze.make_maze();
    // add robot to start
    Robot robot{maze.get_start(), maze.end_coords()};

    Display display{grid_width, grid_height};
    int frame_counter = 0;

    int i = 0;
    while (display.is_open())
    {

        display.handle_event();
        display.draw_maze(maze);

        if (robot.at_end())
        {
            display.draw_celebration();
        }
        else if (++frame_counter >= 100)
        {
            robot.walk();
            frame_counter = 0;
        }

        display.display();
    }
}

#include <SFML/Graphics.hpp>
#include "grid.h"
#include <memory>
#include "constants.h"
#include "robot.h"
#include <iostream>

int main()
{
    Grid maze(grid_width, grid_height);
    maze.make_maze();
    // add robot to start
    Robot robot{maze.get_start(), maze.end_coords()};

    sf::RenderWindow window(sf::VideoMode(grid_width * pixels_per_cell, grid_height * pixels_per_cell), "Maze Viewer");
    int i = 0;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        // Draw maze
        for (int row = 0; row < grid_height; ++row)
        {
            for (int col = 0; col < grid_width; ++col)
            {
                auto block = maze.get_block(row, col);

                float x = col * pixels_per_cell;
                float y = row * pixels_per_cell;

                // highlight robot location
                if (block->has_robot())
                {
                    sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                    rect.setPosition(x, y);
                    rect.setFillColor(sf::Color(0, 255, 0, 100));
                    window.draw(rect);
                }
                // highlight if seen
                if (block->was_seen())
                {
                    sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                    rect.setPosition(x, y);
                    rect.setFillColor(sf::Color(255, 0, 0, 100));
                    window.draw(rect);
                }

                sf::Vertex line[2];

                // UP
                if (block->wall_up())
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // DOWN
                if (block->wall_down())
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y + pixels_per_cell), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // LEFT
                if (block->wall_left())
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // RIGHT
                if (block->wall_right())
                {
                    line[0] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
        try
        {
            if (i == 2500)
            {
                std::cout << " walk " << std::endl;
                robot.walk();
                i = 0;
            }
            ++i;
        }
        catch (const std::runtime_error &e)
        {
            std::cout << "Caught specific runtime_error: " << e.what() << std::endl;
        }
        catch (const std::exception &e)
        {
            // Catch any other std::exception-derived exceptions
            std::cout << "Caught general std::exception: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Other error" << std::endl;
        }
    }
}

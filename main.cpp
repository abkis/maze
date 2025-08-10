#include <SFML/Graphics.hpp>
#include "grid.h"
#include <memory>
#include "constants.h"

int main()
{
    Grid maze(grid_width, grid_height);
    maze.make_maze();

    sf::RenderWindow window(sf::VideoMode(grid_width * pixels_per_cell, grid_height * pixels_per_cell), "Maze Viewer");

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

                // Optional: highlight start & end
                if (block->is_start)
                {
                    sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                    rect.setPosition(x, y);
                    rect.setFillColor(sf::Color(0, 255, 0, 100));
                    window.draw(rect);
                }
                if (block->is_end)
                {
                    sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                    rect.setPosition(x, y);
                    rect.setFillColor(sf::Color(255, 0, 0, 100));
                    window.draw(rect);
                }

                sf::Vertex line[2];

                // UP
                if (block->walls[UP])
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // DOWN
                if (block->walls[DOWN])
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y + pixels_per_cell), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // LEFT
                if (block->walls[LEFT])
                {
                    line[0] = sf::Vertex(sf::Vector2f(x, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
                // RIGHT
                if (block->walls[RIGHT])
                {
                    line[0] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y), sf::Color::White);
                    line[1] = sf::Vertex(sf::Vector2f(x + pixels_per_cell, y + pixels_per_cell), sf::Color::White);
                    window.draw(line, 2, sf::Lines);
                }
            }
        }

        window.display();
    }
}

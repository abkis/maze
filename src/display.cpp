#include "display.h"
#include <iostream>

Display::Display(int width, int height) : window{sf::VideoMode(width * pixels_per_cell, height * pixels_per_cell), "Maze Viewer"}
{
    if (!font.loadFromFile("DejaVuSans.ttf"))
    {
        std::cerr << "Font not loaded!" << std::endl;
    }
}

void Display::handle_event()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

// draw maze blocks
void Display::draw_maze(const Grid &maze)
{
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
            // highlight if seen or visited
            else if (block->get_visited_counter() > 0)
            {
                sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                rect.setPosition(x, y);
                rect.setFillColor(sf::Color(100, 100, 0, 100));
                window.draw(rect);
            }

            else if (block->was_seen())
            {
                sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                rect.setPosition(x, y);
                rect.setFillColor(sf::Color(255, 0, 0, 100));
                window.draw(rect);
            }

            if (block->block_is_end())
            {
                sf::RectangleShape rect(sf::Vector2f(pixels_per_cell, pixels_per_cell));
                rect.setPosition(x, y);
                rect.setFillColor(sf::Color(255, 255, 0, 100));
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
}

// draw celebration
void Display::draw_celebration()
{
    if (!celebration_initialized)
    {
        const int CONFETTI_COUNT = 200;
        for (int i = 0; i < CONFETTI_COUNT; ++i)
        {
            sf::CircleShape piece(3.f);
            piece.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            piece.setPosition(rand() % window.getSize().x, rand() % window.getSize().y);
            confetti.push_back(piece);
        }
        celebration_initialized = true;
    }

    for (auto &piece : confetti)
    {
        piece.move(0, 2);
        if (piece.getPosition().y > window.getSize().y)
            piece.setPosition(rand() % window.getSize().x, 0);
        window.draw(piece);
    }

    sf::RectangleShape overlay({(float)window.getSize().x, (float)window.getSize().y});
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    window.draw(overlay);

    sf::Text text("Robot reached the end!", font, 40);
    text.setFillColor(sf::Color::Yellow);
    text.setStyle(sf::Text::Bold);
    text.setPosition(window.getSize().x / 2.f - 250, window.getSize().y / 2.f - 50);
    window.draw(text);
}

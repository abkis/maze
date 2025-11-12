#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"
#include "robot.h"

// handle display stuff in main.cpp
class Display
{
    sf::RenderWindow window;
    sf::Font font;
    std::vector<sf::CircleShape> confetti;
    bool celebration_initialized{false};

public:
    Display(int width, int height);
    inline bool is_open() const { return window.isOpen(); };
    void handle_event();
    void draw_maze(const Grid &maze);
    void draw_celebration();
    inline void display() { window.display(); };
    inline sf::RenderWindow &get_window() { return window; };
};
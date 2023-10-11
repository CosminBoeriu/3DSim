#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "linesegment.h"

int main()
{
    rotationMatrix::CALCULATE_ROTATION_MATRIX();

    Vector v1(std::vector<double>{0, 0, 0, 1});
    LineSegment ls = LineSegment(v1, -0.7853981634, 0.615479, 1);
    std::array<Vector, 2>x = ls.get_ends();

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event{};
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
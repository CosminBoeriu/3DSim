#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "linesegment.h"
#include "frustum.h"

int main()
{
    rotationMatrix::CALCULATE_ROTATION_MATRIX();

    Vector v1(std::vector<double>{sqrt(3), 0, 0, 1});
    Vector v2(std::vector<double>{1, 1, 1, 1});
    Vector axis = v1.get_perpendicular_vector(v2);
    rotationAxis rot = rotationAxis(axis);
    Vector test = rot.rotateAroundAxis(v1, -54.735610317245346*PI/180);

    Camera CAMERA = Camera();
    Vector test2 = CAMERA.calculate_new_coordinates(test);


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
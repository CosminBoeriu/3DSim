#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "linesegment.h"
#include "frustum.h"
#include "projection.h"
#include <chrono>
#include <thread>

int main()
{
    rotationMatrix::CALCULATE_ROTATION_MATRIX();

    /*Vector v1(std::vector<double>{sqrt(3), 0, 0, 1});
    Vector v2(std::vector<double>{1, 1, 1, 1});
    Vector axis = v1.get_perpendicular_vector(v2);
    rotationAxis rot = rotationAxis(axis);
    Vector test = rot.rotateAroundAxis(v1, -54.735610317245346*PI/180);*/

    Camera CAMERA = Camera();
    /*Vector point_in_space(std::vector<double>{1000, 2000, 5000, 1});
    Vector test2 = CAMERA.calculate_coordinates_of_point(point_in_space);*/

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    Tetrahedron Shp;
    Projection Prj(Shp);
    sf::RenderWindow window(sf::VideoMode(1600, 900), "SFML window");

    // Start the game loop
    while (window.isOpen()){
        auto start = std::chrono::high_resolution_clock::now();
        // Process events
        sf::Event event{};
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        Prj.update(CAMERA);
        std::cout<<Prj.calculate_transformed_center()<<'\n';
        window.clear();
        window.draw(Prj.get_edges());
        window.display();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = (std::chrono::duration_cast<std::chrono::microseconds>(stop - start));
        std::this_thread::sleep_for(std::chrono::milliseconds(14));
    }

    return EXIT_SUCCESS;
}
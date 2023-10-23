#pragma once
#include "frustum.h"
#include "shape.h"

class Screen{
private:
    sf::RenderWindow window;
    Camera myCamera;
    std::vector<Shape>myShapes;
public:
    Screen(int x, int y): window(sf::RenderWindow(sf::VideoMode(x, y), "SFML window")){
        myCamera = Camera();
    }
};

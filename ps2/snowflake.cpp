// File: snowflake.cpp
// Project: ps2
// Associated Project Files: Triangle.cpp Triangle.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/3/2022

#include <math.h>
#include <time.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Triangle.hpp"

void snowflake(sf::RenderWindow&, int, double, double, double);
void recursiveTriangles(sf::RenderWindow&, int, double, double, double,
                        double, int = 0, bool = true);
double getSway(int, double);
sf::Color getColor(double, double, double);
struct Point;

const double PI = 3.14159;
const bool ANIMATE = true;

int main(int argc, char **argv) {
    Triangle t;
    char *garbage;
    double sideLength = std::strtof(argv[1], &garbage);
    int recursionDepth = std::strtol(argv[2], &garbage, 0);
    double width = 2 * sideLength * 3,
           height = width * sin(PI / 3);

    sf::RenderWindow window(sf::VideoMode(width, height), "Snowflake");
    window.setFramerateLimit(60);

    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(sf::Color::White);

    snowflake(window, recursionDepth, sideLength, width / 2, height / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        window.draw(rectangle);

        snowflake(window, recursionDepth, sideLength, width / 2, height / 2);

        window.display();
    }

    return 0;
}

void snowflake(sf::RenderWindow &window, int depth,
               double sideLength, double x, double y) {
    double radius = sideLength * sqrt(3) / 2,
           animationSway = getSway(depth, time(0)) * 0.5;
    for (double direction = -PI / 2 + animationSway;
         direction < 3 * PI / 2 + animationSway; direction += PI / 3) {
        double x2 = x + cos(direction) * radius,
               y2 = y + sin(direction) * radius;
        recursiveTriangles(window, depth + 1, x2, y2, direction,
                           sideLength / 2);
    }
}

struct Point {
 public:
    double x, y;
};

double getSway(int depth, double time) {
    return ANIMATE ? 0.02 * sin(time + depth * 0.5) : 0;
}

sf::Color getColor(double x, double y, double time) {
              // vary red 0 - 224
    const int r = (sin(time * 0.5 + x * 0.02) + 1) * 112,
              // vary green 128 - 224
              g = (sin(time * 0.5 + y * 0.02) + 1) * 48 + 128;
    return sf::Color(r, g, 255, 128);
}

void recursiveTriangles(sf::RenderWindow &window, int depth, double x, double y,
                        double direction, double sideLength,
                        int consecutiveTurns, bool isBase) {
    if (!depth) return;
    // animate snowflake with slow waving motion
    if (ANIMATE) direction += getSway(depth, time(0));

    const double holdSin = sin(direction),
                 holdCos = cos(direction);
    Point p1, p2, p3;
    p1.x = x + holdCos * sideLength * sqrt(3);
    p1.y = y + holdSin * sideLength * sqrt(3);
    p2.x = x - holdSin * sideLength;
    p2.y = y + holdCos * sideLength;
    p3.x = x + holdSin * sideLength;
    p3.y = y - holdCos * sideLength;
    sideLength /= 2;

    Triangle triangle;
    triangle.setPointPosition(0, p1.x, p1.y);
    triangle.setPointPosition(1, p2.x, p2.y);
    triangle.setPointPosition(2, p3.x, p3.y);
    triangle.setPointColor(0, getColor(p1.x, p1.y, time(0)));
    triangle.setPointColor(1, getColor(p2.x, p2.y, time(0)));
    triangle.setPointColor(2, getColor(p3.x, p3.y, time(0)));
    window.draw(triangle);

    if (abs(consecutiveTurns) != 2)
        recursiveTriangles(window, depth - 1, p1.x, p1.y, direction,
                           sideLength, 0, false);
    if (isBase) return;
    recursiveTriangles(window, depth - 1, p2.x, p2.y, direction + 2 * PI / 3,
                       sideLength, consecutiveTurns < 1 ? 1 : 2, false);
    recursiveTriangles(window, depth - 1, p3.x, p3.y, direction - 2 * PI / 3,
                       sideLength, consecutiveTurns > -1 ? -1 : -2, false);
}

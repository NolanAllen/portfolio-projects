// File: Triangle.cpp
// Project: ps2
// Associated Project Files: snowflake.cpp Triangle.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/3/2022

#include "Triangle.hpp"

void Triangle::setPointPosition(int i, double x, double y) {
    vertices[i].position = sf::Vector2f(x, y);
}

void Triangle::setPointColor(int i, sf::Color c) {
    vertices[i].color = c;
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(vertices, states);
}

// File: Triangle.hpp
// Project: ps2
// Associated Project Files: snowflake.cpp Triangle.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/3/2022

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Triangle : public sf::Drawable {
 public:
    Triangle() : vertices(sf::VertexArray(sf::Triangles, 3)) {}
    void setPointPosition(int, double, double);
    void setPointColor(int, sf::Color);
 private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::VertexArray vertices;
};

#endif  // TRIANGLE_HPP_

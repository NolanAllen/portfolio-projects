// File: main.cpp
// Project: ps4b
// Associated Project Files: Sokoban.cpp Sokoban.hpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/24/2022

#include <iostream>
#include <fstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"

int main(int argc, char **argv) {
    std::string filename;
    if (argc > 1)
        filename = argv[1];
    else
        filename = "level1.txt";
    std::ifstream lvlFile;
    lvlFile.open(filename, std::ifstream::in);
    if (!lvlFile)
        throw std::invalid_argument("Level file not found.");
    Sokoban sokoban;
    lvlFile >> sokoban;
    lvlFile.close();

    sf::RenderWindow window(sf::VideoMode(sokoban.getWidth(),
        sokoban.getHeight()), "Sokoban");
    window.setFramerateLimit(60);

    sf::RectangleShape rectangle(sf::Vector2f(640, 640));
    rectangle.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Up:
                case sf::Keyboard::W: sokoban.movePlayer(Sokoban::UP); break;
                case sf::Keyboard::Left:
                case sf::Keyboard::A: sokoban.movePlayer(Sokoban::LEFT); break;
                case sf::Keyboard::Down:
                case sf::Keyboard::S: sokoban.movePlayer(Sokoban::DOWN); break;
                case sf::Keyboard::Right:
                case sf::Keyboard::D: sokoban.movePlayer(Sokoban::RIGHT); break;
                case sf::Keyboard::R: sokoban.reset(); break;
                case sf::Keyboard::U: sokoban.undo(); break;
                default: break;
                }
                break;

            default:
                break;
            }
        }
        window.clear();
        window.draw(sokoban);
        window.display();
    }

    return 0;
}

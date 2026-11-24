// File: Sokoban.hpp
// Project: ps4a
// Associated Files: Sokoban.cpp, main.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/24/2022

#ifndef SOKOBAN_HPP_
#define SOKOBAN_HPP_

#include <time.h>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iostream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Move;

class Sokoban : public sf::Drawable {
 public:
    Sokoban();
    virtual ~Sokoban() { delete []map; }
    // enum numbered to make it easy to get opposite direction
    enum Direction { UP = -2, LEFT = -1, DOWN = 2, RIGHT = 1 };
    bool isWon() const;
    void movePlayer(Direction direction);
    bool undo(bool override = false);
    void reset();
    int getWidth() const { return lvlWidth * TILE_WIDTH; }
    int getHeight() const { return lvlHeight * TILE_HEIGHT + VERTICAL_OFFSET; }
    friend std::istream& operator>>(std::istream& is, Sokoban& s);

 private:
    // moveObject updates a object index and returns number of objects modified
    int moveObject(int &object, int targetOffset);
    // updateTempWalls works with pressure plates to determine
    // whether temporary walls should be active
    void updateTempWalls();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void initializeWin();
    sf::Texture groundTxt,
                wallTxt,
                storageTxt,
                crateTxt,
                pressPlateTxt,
                playerTxt[4],
                clockTxt[11],
                winTxt;
    sf::SoundBuffer winSoundBuffer;
    sf::Sound winSound;
    int lvlWidth,
        lvlHeight;
    char * map;
    int playerIndex;
    Direction playerDirection;
    std::time_t startTimestamp;
    std::vector<int> storageIndices;
    std::vector<int> pressurePlateIndices;
    std::vector<int> tempWallIndices;
    std::vector<Move> moveHistory;
    bool gameActive;
    static const int TILE_WIDTH = 64,
                     TILE_HEIGHT = 64,
                     VERTICAL_OFFSET = 32;
};

std::istream& operator>>(std::istream& is, Sokoban& s);

class Move {
 public:
    Move(Sokoban::Direction direction, bool withBlock):
       dir(direction), block(withBlock) {}
    Sokoban::Direction direction() { return dir; }
    bool withBlock() { return block; }

 private:
    Sokoban::Direction dir;
    bool block;
};

#endif  // SOKOBAN_HPP_

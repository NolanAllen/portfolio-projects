// File: Sokoban.cpp
// Project: ps4a
// Associated Project Files: Sokoban.hpp main.cpp
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 10/28/2022

#include "Sokoban.hpp"

Sokoban::Sokoban() : lvlWidth(0), lvlHeight(0), map(nullptr),
                     playerIndex(0), playerDirection(DOWN),
                     startTimestamp(std::time(nullptr)), gameActive(true) {
    // level tiles
    if (!groundTxt.loadFromFile("./graphics/ground_01.png"))
        throw std::runtime_error("Texture ground_01.png not found.");
    if (!wallTxt.loadFromFile("./graphics/block_06.png"))
        throw std::runtime_error("Texture block_06.png not found.");
    if (!storageTxt.loadFromFile("./graphics/ground_04.png"))
        throw std::runtime_error("Texture ground_04.png not found.");
    if (!crateTxt.loadFromFile("./graphics/crate_03.png"))
        throw std::runtime_error("Texture crate_03.png not found.");
    if (!pressPlateTxt.loadFromFile("./graphics/pressure_plate.png"))
        throw std::runtime_error("Texture pressure_plate.png not found.");
    // player costumes
    if (!playerTxt[3].loadFromFile("./graphics/player_05.png"))
        throw std::runtime_error("Texture player_05.png not found.");
    if (!playerTxt[0].loadFromFile("./graphics/player_08.png"))
        throw std::runtime_error("Texture player_08.png not found.");
    if (!playerTxt[2].loadFromFile("./graphics/player_17.png"))
        throw std::runtime_error("Texture player_17.png not found.");
    if (!playerTxt[1].loadFromFile("./graphics/player_20.png"))
        throw std::runtime_error("Texture player_20.png not found.");
    // clock costumes
    if (!clockTxt[0].loadFromFile("./graphics/clock/clock_0.png"))
        throw std::runtime_error("Texture clock_0.png not found.");
    if (!clockTxt[1].loadFromFile("./graphics/clock/clock_1.png"))
        throw std::runtime_error("Texture clock_1.png not found.");
    if (!clockTxt[2].loadFromFile("./graphics/clock/clock_2.png"))
        throw std::runtime_error("Texture clock_2.png not found.");
    if (!clockTxt[3].loadFromFile("./graphics/clock/clock_3.png"))
        throw std::runtime_error("Texture clock_3.png not found.");
    if (!clockTxt[4].loadFromFile("./graphics/clock/clock_4.png"))
        throw std::runtime_error("Texture clock_4.png not found.");
    if (!clockTxt[5].loadFromFile("./graphics/clock/clock_5.png"))
        throw std::runtime_error("Texture clock_5.png not found.");
    if (!clockTxt[6].loadFromFile("./graphics/clock/clock_6.png"))
        throw std::runtime_error("Texture clock_6.png not found.");
    if (!clockTxt[7].loadFromFile("./graphics/clock/clock_7.png"))
        throw std::runtime_error("Texture clock_7.png not found.");
    if (!clockTxt[8].loadFromFile("./graphics/clock/clock_8.png"))
        throw std::runtime_error("Texture clock_8.png not found.");
    if (!clockTxt[9].loadFromFile("./graphics/clock/clock_9.png"))
        throw std::runtime_error("Texture clock_9.png not found.");
    if (!clockTxt[10].loadFromFile("./graphics/clock/clock_colon.png"))
        throw std::runtime_error("Texture clock_colon.png not found.");
    std::for_each(clockTxt, clockTxt+11,
                  [](sf::Texture &txt){ txt.setSmooth(true); });
    // win screen costume
    if (!winTxt.loadFromFile("./graphics/You_Win.png"))
        throw std::runtime_error("Texture You_Win.png not found.");
    winTxt.setSmooth(true);
    // win sound
    if (!winSoundBuffer.loadFromFile("Triumph.wav"))
        throw std::runtime_error("Sound Triumph.wav not found.");
    winSound.setBuffer(winSoundBuffer);
}

bool Sokoban::isWon() const {  // check if every storage space has a crate
    for (auto i : storageIndices)
        if (map[i] != 'O') return false;
    return true;
}

void Sokoban::movePlayer(Direction direction) {
    if (!gameActive) return;
    int c;  // objects updated
    switch (direction) {
        case UP: c = moveObject(playerIndex, -lvlWidth); break;
        case LEFT: c = moveObject(playerIndex, -1); break;
        case DOWN: c = moveObject(playerIndex, lvlWidth); break;
        case RIGHT: c = moveObject(playerIndex, 1); default: break;
    }
    if (c > 0) {
        moveHistory.push_back(Move(direction, c == 2));
        playerDirection = direction;
    }
    updateTempWalls();
    if (isWon()) initializeWin();
}

int Sokoban::moveObject(int &object, int targetOffset) {
    int objectsModified = 0;
    switch (map[object + targetOffset]) {
        case 'O':
        if (map[object + 2 * targetOffset] == '.') {
            map[object + 2 * targetOffset] = 'O';
            map[object + targetOffset] = '.';
            objectsModified++;
        } else {
            break;
        }
        case '.': object += targetOffset; objectsModified++; break;
        default: break;
    }
    return objectsModified;
}

void Sokoban::updateTempWalls() {
    bool plateActivated = false;
    for (auto i : pressurePlateIndices) {
        if (map[i] == 'O' || i == playerIndex) {
            plateActivated = true;
            break;
        }
    }
    if (plateActivated) {
        for (auto i : tempWallIndices) {
            if (map[i] == '%') map[i] = '.';
        }
    } else {
        for (auto i : tempWallIndices) {
            if (i == playerIndex)
                map[i] = '.';
            else
                if (map[i] == '.')
                    map[i] = '%';
        }
    }
}

bool Sokoban::undo(bool override) {
    if (moveHistory.size() == 0 || !(gameActive || override)) return false;
    if (moveHistory.back().withBlock()) {  // undo crate movements
        map[playerIndex] = 'O';
        switch (moveHistory.back().direction()) {
            case UP: map[playerIndex - lvlWidth] = '.'; break;
            case LEFT: map[playerIndex - 1] = '.'; break;
            case DOWN: map[playerIndex + lvlWidth] = '.'; break;
            case RIGHT: map[playerIndex + 1] = '.'; break;
            default: break;
        }
    }
    switch (-moveHistory.back().direction()) {
        case UP: playerIndex -= lvlWidth; break;
        case LEFT: playerIndex--; break;
        case DOWN: playerIndex += lvlWidth; break;
        case RIGHT: playerIndex++; break;
        default: break;
    }
    playerDirection = moveHistory.back().direction();
    moveHistory.pop_back();
    updateTempWalls();
    return true;
}

void Sokoban::reset() {
    while (undo(true)) continue;
    playerDirection = DOWN;
    startTimestamp = std::time(nullptr);
    gameActive = true;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // clock
    sf::Sprite clock;
    clock.setScale(sf::Vector2f(0.05, 0.05));
    int offset = (442 * 0.05) / 2;
    std::int64_t gameTime;
    if (gameActive)
        gameTime = std::time(nullptr) - startTimestamp;
    else
        gameTime = startTimestamp;
    clock.setPosition(sf::Vector2f(getWidth() / 2 - 36 - offset, 1));
    clock.setTexture(clockTxt[gameTime / (60 * 10) % 10]);
    target.draw(clock, states);
    clock.setPosition(sf::Vector2f(getWidth() / 2 - 15 - offset, 1));
    clock.setTexture(clockTxt[gameTime / 60 % 10]);
    target.draw(clock, states);
    clock.setPosition(sf::Vector2f(getWidth() / 2 - (122 * 0.05) / 2, 1));
    clock.setTexture(clockTxt[10]);
    target.draw(clock, states);
    clock.setPosition(sf::Vector2f(getWidth() / 2 + 15 - offset, 1));
    clock.setTexture(clockTxt[gameTime / 10 % 6]);
    target.draw(clock, states);
    clock.setPosition(sf::Vector2f(getWidth() / 2 + 36 - offset, 1));
    clock.setTexture(clockTxt[gameTime % 10]);
    target.draw(clock, states);
    // tiles from map array
    sf::Sprite tile;
    for (int i = 0; i < lvlHeight; i++) {
        for (int j = 0; j < lvlWidth; j++) {
            tile.setPosition(sf::Vector2f(j * TILE_HEIGHT,
                                          i * TILE_WIDTH + VERTICAL_OFFSET));
            switch (map[i * lvlWidth + j]) {
                case '%': tile.setColor(sf::Color(191, 191, 191));  // darken
                case '#': tile.setTexture(wallTxt); break;
                case 'O':
                tile.setTexture(groundTxt);
                target.draw(tile, states);
                tile.setTexture(crateTxt);
                break;
                case '.': default: tile.setTexture(groundTxt); break;
            }
            target.draw(tile, states);
            tile.setColor(sf::Color(255, 255, 255));  // reset default color
        }
    }
    // storage tiles
    tile.setTexture(storageTxt);
    for (int i : storageIndices) {
        if (map[i] == 'O') continue;  // don't draw on top of a crate
        tile.setPosition(
            sf::Vector2f(i % lvlWidth * TILE_HEIGHT,
                         i / lvlWidth * TILE_WIDTH + VERTICAL_OFFSET));
        target.draw(tile, states);
    }
    // pressure plate tiles
    tile.setTexture(pressPlateTxt);
    for (int i : pressurePlateIndices) {
        if (map[i] == 'O') continue;  // don't draw on top of a crate
        tile.setPosition(
            sf::Vector2f(i % lvlWidth * TILE_HEIGHT,
                         i / lvlWidth * TILE_WIDTH + VERTICAL_OFFSET));
        target.draw(tile, states);
    }
    // player
    tile.setPosition(
        sf::Vector2f(playerIndex % lvlWidth * TILE_HEIGHT,
                     playerIndex / lvlWidth * TILE_WIDTH + VERTICAL_OFFSET));
    int txtIndex = playerDirection + 1 + (playerDirection < 0);
    tile.setTexture(playerTxt[txtIndex]);
    target.draw(tile, states);
    // win screen
    if (!gameActive) {
        sf::Sprite winBanner(winTxt);
        float txtWidth = 960,
            txtHeight = 294;
        winBanner.setScale(sf::Vector2f(getWidth() / txtWidth,
                                        getWidth() / txtWidth));
        winBanner.setPosition(sf::Vector2f(0.0,
                                          (getHeight() - txtHeight
                                          * (getWidth() / txtWidth))
                                          / 2.0));
        target.draw(winBanner, states);
    }
}

void Sokoban::initializeWin() {
    gameActive = false;
    startTimestamp = std::time(nullptr) - startTimestamp;
    winSound.play();
}

std::istream& operator>>(std::istream& is, Sokoban& s) {
    delete []s.map;
    is >> s.lvlWidth >> s.lvlHeight;
    s.map = new char[s.lvlWidth * s.lvlHeight];
    for (int i = 0; i < s.lvlWidth * s.lvlHeight; i++) {
        do {
            is >> s.map[i];
        } while (s.map[i] == '\n');
        // player and storage indices are stored separately from the map array
        switch (s.map[i]) {
            case '@':
            s.playerIndex = i;
            s.map[i] = '.';
            break;
            case '*':
            s.storageIndices.push_back(i);
            s.map[i] = '.';
            break;
            case 'X':
            s.pressurePlateIndices.push_back(i);
            s.map[i] = '.';
            break;
            case '%':
            s.tempWallIndices.push_back(i);
            break;
            default:
            break;
        }
    }
    s.updateTempWalls();
    return is;
}

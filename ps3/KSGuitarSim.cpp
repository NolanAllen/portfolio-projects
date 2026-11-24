/*
  Copyright 2015 Fred Martin, 
  Y. Rykalova, 2020
  J. Daly 2022
  N. Allen 2022
*/

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include "CircularBuffer.hpp"
#include "StringSound.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamples(StringSound& gs) {
    std::vector<sf::Int16> samples;

    gs.pluck();
    int duration = 8;  // seconds
    int i;
    for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
        gs.tick();
        samples.push_back(gs.sample());
    }

    return samples;
}

enum Instrument {
    Guitar,
    SpringSynth
};

int main(int argc, char **argv) {
    Instrument instrument;
    if (argc > 1) {
        std::string input(argv[1]);
        if (input == "Guitar") {
            instrument = Guitar;
            std::cout << "Instrument: Guitar\n";
        } else if (input == "SpringSynth") {
            instrument = SpringSynth;
            std::cout << "Instrument: SpringSynth\n";
        } else {
            instrument = Guitar;
            std::cout << "Unknown Instrument\nInstrument: Guitar (default)\n";
        }
    } else {
            instrument = Guitar;
            std::cout << "Instrument: Guitar (default)\n";
    }

    std::map<sf::Keyboard::Key, int> keys;
    keys[sf::Keyboard::Q] = 0;
    keys[sf::Keyboard::Num2] = 1;
    keys[sf::Keyboard::W] = 2;
    keys[sf::Keyboard::E] = 3;
    keys[sf::Keyboard::Num4] = 4;
    keys[sf::Keyboard::R] = 5;
    keys[sf::Keyboard::Num5] = 6;
    keys[sf::Keyboard::T] = 7;
    keys[sf::Keyboard::Y] = 8;
    keys[sf::Keyboard::Num7] = 9;
    keys[sf::Keyboard::U] = 10;
    keys[sf::Keyboard::Num8] = 11;
    keys[sf::Keyboard::I] = 12;
    keys[sf::Keyboard::Num9] = 13;
    keys[sf::Keyboard::O] = 14;
    keys[sf::Keyboard::P] = 15;
    keys[sf::Keyboard::Dash] = 16;
    keys[sf::Keyboard::LBracket] = 17;
    keys[sf::Keyboard::Equal] = 18;
    keys[sf::Keyboard::Z] = 19;
    keys[sf::Keyboard::X] = 20;
    keys[sf::Keyboard::D] = 21;
    keys[sf::Keyboard::C] = 22;
    keys[sf::Keyboard::F] = 23;
    keys[sf::Keyboard::V] = 24;
    keys[sf::Keyboard::G] = 25;
    keys[sf::Keyboard::B] = 26;
    keys[sf::Keyboard::N] = 27;
    keys[sf::Keyboard::J] = 28;
    keys[sf::Keyboard::M] = 29;
    keys[sf::Keyboard::K] = 30;
    keys[sf::Keyboard::Comma] = 31;
    keys[sf::Keyboard::Period] = 32;
    keys[sf::Keyboard::SemiColon] = 33;
    keys[sf::Keyboard::Slash] = 34;
    keys[sf::Keyboard::Quote] = 35;
    keys[sf::Keyboard::Space] = 36;

    sf::RenderWindow window(sf::VideoMode(300, 200),
        "SFML Plucked String Sound Lite");
    sf::Event event;

    std::vector<sf::Int16> samples;
    std::vector<sf::SoundBuffer> buffers;
    std::vector<sf::Sound> sounds;
    for (size_t i = 0; i < keys.size(); i++) {
        buffers.push_back(sf::SoundBuffer());
    }
    sf::Sound sound;
    for (size_t i = 0; i < keys.size(); i++) {
        double freq = CONCERT_A * pow(2, (i-12.0)/12.0);
        StringSound guitarString(freq);
        if (instrument == SpringSynth) {
            guitarString.setTickFunc(
                [](std::shared_ptr<CircularBuffer<sf::Int16>> buffer) ->
                    sf::Int16 {
                        static int i = 0;
                        i++;
                        if (i % 100 == 0 && buffer->size() > 2)
                            buffer->dequeue();
                        return 0.985 * (0.9 * buffer->dequeue()
                            + 0.1 * buffer->peek());
                    });
        }
        samples = makeSamples(guitarString);
        if (!buffers[i].loadFromSamples(&samples[0], samples.size(), 2,
            SAMPLES_PER_SEC)
        )
            throw std::runtime_error(
                "sf::SoundBuffer: failed to load from samples.");
        sounds.push_back(sound);
        sounds.back().setBuffer(buffers[i]);}

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                try {
                    sounds.at(keys.at(event.key.code)).play();
                } catch (const std::out_of_range& e) { }
                break;

            default:
                break;
            }

            window.clear();
            window.display();
        }
    }
    return 0;
}

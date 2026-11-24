// File: PhotoMagic.cpp
// Project: ps1b
// Associated Files: FibLFSR.hpp FibLFSR.cpp test.cpp
// Written by: Nolan Allen
// Last Update: 9/26/2022

#include "FibLFSR.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <bitset>

void transform(sf::Image&, FibLFSR*);
std::string getSeedFromPassword(std::string);
int getCharID(char);

int main(int argc, char **argv)
{
	// the three command-line arguments
	std::string seed = argv[3],
				inputFile = argv[1],
				outputFile = argv[2];

	// determine if command line argument is a password or a seed
	bool isPassword = false;
	if (seed.length() == 16) {
		for (int i = 0; i < 16; i++) {
			if (seed[i] != '0' && seed[i] != '1') {
				isPassword = true;
				break;
			}
		}
	} else
		isPassword = true;
	if (isPassword) // if necessary, convert the password to a seed
		seed = getSeedFromPassword(seed);

	// load the image from a file
	sf::Image image;
	if (!image.loadFromFile(inputFile))
		return -1;

	// instantiate the register used to encrypt the image
	FibLFSR flfsr(seed);

	// encrypt the image
	transform(image, &flfsr);

	sf::Vector2u size = image.getSize();
	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Original Image");
	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Encrypted/Decrypted Image");

	// set up textures using the images
	sf::Texture texture1;
	texture1.loadFromFile(inputFile);
	sf::Texture texture2;
	texture2.loadFromImage(image);

	// apply the textures to sprites
	sf::Sprite sprite1;
	sprite1.setTexture(texture1);
	sf::Sprite sprite2;
	sprite2.setTexture(texture2);

	// continue displaying the images until one of the windows is closed
	while (window1.isOpen() && window2.isOpen())
	{
		// determine if a window has been closed
		sf::Event event;
		while (window1.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window1.close();
		}
		while (window2.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window2.close();
		}

		// display the two windows
		window1.clear();
		window1.draw(sprite1);
		window1.display();
		window2.clear();
		window2.draw(sprite2);
		window2.display();
	}

	// write the image to the output file
	if (!image.saveToFile(outputFile))
		return -1;

	// end the program
	return 0;
}

// function transform takes an image and a FibLFSR and encrypts or decrypts the image
//  input: string, only first 3 chars are used, chars must be alphanumeric, '-', or '_'
//  output: string representation of 16-digit binary number
void transform(sf::Image& image, FibLFSR* flfsr) {
	// for each pixel, XOR its rgb values with the 8-bit output of the shift register
	sf::Color p;
	for (unsigned int x = 0; x<image.getSize().x; x++) {
		for (unsigned int y = 0; y< image.getSize().y; y++) {
			p = image.getPixel(x, y);
			p.r = p.r ^ flfsr->generate(8);
			p.g = p.g ^ flfsr->generate(8);
			p.b = p.b ^ flfsr->generate(8);
			image.setPixel(x, y, p);
		}
	}
}

// function getSeedFromPassword takes a string and outputs a 16-digit binary number as a string
//  input: string, chars (case-sensitive) must be alphanumeric, '-', or '_'
//  output: string representation of 16-digit binary number
//  note: can return 2^16 unique values, but the possible password combinations exceedes this,
//   allowing multiple passwords to generate the same seed
std::string getSeedFromPassword(std::string password) {
	// initialize a seed with a valid encryption value
	std::string seed = "0000000000000001";
	// iterate through the password and seed characters
	for (unsigned int pwIndex = 0, seedIndex = 0; pwIndex < password.length(); pwIndex++, seedIndex++) {
		// get a string of 6 binary numbers representing a character ID
		const std::string pwChar = std::bitset<6>(getCharID(password[pwIndex])).to_string();
		// iterate through the seed and password-chars characters
		for (unsigned int pwCharIndex = 0; pwCharIndex < pwChar.length(); pwCharIndex++, seedIndex++) {
			seedIndex = seedIndex % seed.length(); // ensure a valid index
			seed[seedIndex] = seed[seedIndex] != pwChar[pwCharIndex] ? '1' : '0'; // XOR characters
		}
	}

	// ensure that the seed will encrypt the image (16 0's will leave it unencrypted)
	if (seed == "0000000000000000")
		seed = "0000000000000001";

	return seed;
}

// function getCharID takes a character and outputs a 6-digit binary number
//  input: char, must be alphanumeric, '-', or '_'
//  output: int in range 0 to 63
int getCharID(char c) {
	if ('0' <= c && c <= '9')
		return c - '0'; // return id for numeric char
	if ('a' <= c && c <= 'z')
		return (c - 'a') + ('9' - '0' + 1); // return id for alphabetical lowercase char
	if ('A' <= c && c <= 'Z')
		return (c - 'A') + ('9' - '0' + 1) + ('z' - 'a' + 1); // return id for alphabetical uppercase char
	if (c == '-')
		return ('9' - '0' + 1) + ('z' - 'a' + 1) + ('Z' - 'A' + 1); // return id for dash char
	if (c == '_')
		return ('9' - '0' + 1) + ('z' - 'a' + 1) + ('Z' - 'A' + 1) + 1; // return id for underscore char
	else
		throw std::invalid_argument("character must be alphanumeric, '-', or '_'"); // invalid character passed to function
}

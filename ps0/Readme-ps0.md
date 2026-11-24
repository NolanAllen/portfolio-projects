# PS0: Hello SFML

## Contact
Name: Nolan Allen

Time to Complete: 21h 20m total, 6h 35m writing code and associated files, 14h 45m attempting to install/use the Linux software


## Description
The goal of this assignment was to become acquainted with makefiles and basic components of SFML. The program can be run with `./sfml-app`. Movement is controlled with the w, a, s, and d keys, and turning is controlled with the arrow keys.

### Accomplishments
The program successfully launches a foundational sprite-based 3D projection engine. The engine is structured into several classes. Triple is used to hold and manipulate a position in 3D space, Camera is used to process data about the viewing point in the world, and Object is used to display individual sprites at specific points in the world. These three classes work together to project sprites onto a viewing plane to simulate a 3D world.

### Prior Knowledge
Going into this assignment, I had a thorough knowledge of sprite-based 3D projection engines from my extensive work on them in the last few years. Despite never having implemented one in C++, this experience gave me a general idea of how to approach the project as well as a comprehensive understanding of the math involved.

### What I Learned
This was my first introduction to reading code documentation. Previously when I encountered problems I typically searched for people on Stack Overflow in similar situations. I found, however, that looking up documentation for SFML provided more succinct results with more efficiency. I plan on attempting to look up documentation to solve future problems as well.

### Challenges
This was my first introduction to reading code documentation. Previously when I encountered problems I typically searched for people on Stack Overflow in similar situations. I found, however, that looking up documentation for SFML provided more succinct results with more efficiency. I plan on attempting to look up documentation to solve future problems as well.


## Changes
9/15/2022 - project created
11/30/2022 - lint command added to Makefile, main.cpp updated to pass lint, Changes section added to Readme


## Acknowledgements
A great source of help was my years of experience with building 3D projection engines in Scratch.
The sfml documentation was also extremely helpful in bringing this project to life visually: https://www.sfml-dev.org/documentation/2.4.2/

### Credits
sprite.png - id Software's Doom (1993)

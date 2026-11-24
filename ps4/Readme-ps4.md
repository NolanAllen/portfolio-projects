# PS4: Sokoban

## Contact
Name: Nolan Allen
Time to Complete: 9 hours for part b, 16 hours for complete Sokoban game


## Description
The goal of this assignment was to create a sokoban game. The program can be run with `./Sokoban (level file)`.

### Accomplishments
The program successfully takes a level file and creates a Sokoban game based on it. In a given level file, the first two numbers represent the width and height, and the rest of the characters represent individual tiles in the level.

The most efficient method I found of organizing level data was to use a char array to hold walls, floors, crates, and active temporary walls. The player is stored as index to the array, and all other objects (storage locations, pressure plates, and temporary walls) are stored in vectors as indices to the array. This allows efficient memory usage as well as efficient time complexity for tasks such as moving the player, checking for open space in a given location, checking if a pressure plate is activated, and checking if all storage locations have been filled.

### Prior Knowledge
Going into this assignment, I had a general knowledge game design theory and several years of experience making games. This helped significantly in designing levels, adding new features, and organizing the program's overall structure.

### What I Learned
Through this project, I learned a lot about puzzle design and creating a level around game features. Regarding programming, I learned how to better think through the ways users could potentially break the code and how to improve it through iteration.

### Challenges
The most troublesome challenge I encountered was implementing the undo feature. This code went through several iterations as I implemented features such as temporary walls and pressure plates, and it forced me to try to think through every possible way to break the code with level design and player choices.


## Acknowledgements
All .png files in the clock directory (clock_colon, clock_0, clock_1, etc.) and pressure_plate.png were created by Nolan Allen with TurboWarp (https://turbowarp.org/editor) in the bitmap editor using the default Sans Serif font.
You_Win.png was arranged by Nolan Allen with TuboWarp (https://turbowarp.org/editor) in the bitmap editor using the default Sans Serif font and assembled from graphics created by Kenny Vleugels (see license and website info below).
All other .png files were created by Kenney Vleugels and are licensed under the Creative Commons Zero license and can be found at https://kenney.nl/assets/sokoban.
Triumph.wav is liscensed under Creative Commons Zero and can be found in the TurboWarp sound library at https://turbowarp.org/editor.

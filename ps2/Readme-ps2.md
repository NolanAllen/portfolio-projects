# PS2: Recursive Graphics (Triangle Fractal)

## Contact
Name: Nolan Allen


## Description
The goal of this assignment was to write a recursive function to draw a snowflake fractal with SFML. The program can be run with `./snowflake [side length] [recursion depth]`.

### Accomplishments
The program successfully displays a recursively drawn snowflake on the screen matching the user's specifications for side length and recursion depth. The snowflake also subtly sways and changes color over time, ranging from blue to cyan to pink to white. Data, aside from side length and recursion depth, is not stored across multiple frames; rather, the recursive algorithm generates all the data each frame. This is partly because of how color and position changes each frame. It seemed more efficient to create new data than to update existing data.

### Prior Knowledge
Going into this assignment, I had a thorough knowledge of trigonometry and related geometry. This really helped me with the assignment as I immediately had an idea of how to approach it both programmatically and geometrically.

### What I Learned
Before this project, I had largely dealt with my own code. A data structures class had me implement a professor's interface in Java several times, but other than that I coded everything myself. This assignment forced me to research code in the SFML library to see how classes fit together and write my own subclass to the sf::Drawable abstract class, and I gained valuable experience through this process that will definitely help me in the future.

### Challenges
The main challenge I encountered was implementing sf::Drawable as a parent class. I did not have much experience looking at other people's classes and figuring out how to incorporate my own with them. It took some time to get everything working, but in the end my class meshed seamlessly with sf::Drawable to the extent that I used it in my project.


## Acknowledgements
The SFML documentation was referenced for all uses of SFML code.

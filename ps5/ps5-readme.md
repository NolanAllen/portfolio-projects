# PS6: DNA Sequence Alignment

## Contact
Name: Nolan Allen

Time to Complete: 14h

## Discription
The goal of this assignment was to implement an algorithm to find the optimal matching between two sets of characters, primarily DNA sequences, along with the edit distance. The program can be run with `./EDistance < [input file] > [output file]`.

### Accomplishments
The program successfully finds the optimal alignment and edit distance between two sets of characters given in the standard input and outputs the results to the standard output. I decided to implement the dynamic programming approach. I chose this primarily with the intent to gain experience coding in this way as I have no previous experience with dynamic programming. The main benefit of dynamic programming is O(NxM) time complexity, while the main drawback is O(NxM) space complexity.

### Prior Knowledge
Going into this assignment, I had no knowledge of dynamic programming. That served as something of an hurdle, seeing as this project was largely based around it.

### What I Learned
When I started this project, I did not typically run unit tests until my code was finished. Through the process of bug-fixing this program, I realized just how valuable unit tests could be when written earlier and run often.

### Challenges
The main challenge I encountered was fixing various edge cases. Mostly this was because the program worked most of the time except in a few key scenarios that I did not test until the bulk of the code had been written.


## Acknowledgements
Help was received from Anson on Dr. Daly's Discord server in fixing
my Valgrind command.

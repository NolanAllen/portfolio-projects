# PS6: RandWriter

## Contact
Name: Nolan Allen

Time to Complete: 15h


## Discription
The goal of this assignment was to generate random text in the style of a given text. The two programs, one based on characters and one based on words, can be run with `./TextWriter [number of characters to generate] [substring length] < [input file]\space\space\space\space` and `./WordWriter [number of words to generate] [substring length, in words] <\newline [input file]`.

### Accomplishments
The program successfully generates random text in the style of a given text. The generated text is made up of substrings of length k, specified by the user, and will be k characters in TextWriter and k words in WordWriter. All substrings are taken from the original text and selected in a probabilistic manner. All unique substrings of length k in the text are recorded along with their respective frequencies in a std::unordered_map. The unordered_map was chosen for its hash table implementation, giving constant time complexity to access each element. Each k-length substring is stored alongside each unique character that appears after it, along with that character's frequency. These char-frequency pairs are stored in a std:vector. My original implementation stored them in a std::map for O(logn) time complexity for element access, but I switched to a vector for two reasons: (1) I needed to frequently iterate over the elements, and (2) often the structure only needed to hold a single or a few characters, and the vector reduced memory usage.

The second, word-based version of the program uses the same program structure with several changes to aid in the transition from generating by char to generating by std::string.

### Prior Knowledge
Going into this assignment, I had no knowledge of the techniques used in this project to generate random text in the style of another text.

### What I Learned
Random generation through a probabilistic model is a powerful tool about which I was excited to learn over the course of this assignment. I also gained experience working with various data structures such as hashtables while analyzing tasks to determine what structures would be best for various use cases.

### Challenges
The single biggest challenge I encountered was duplicating and editing the program to generate text word by word instead of character by character. Luckily, much of the code transitioned very well simply by changing data types from char to std::string. This was also facilitated by templated functions and classes along with liberal use of the `auto` keyword.


## Acknowledgements
The RandWriter class declaration was adapted from Dr. Daly's PS6 pdf.

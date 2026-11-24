# PS1: PhotoMagic

## Contact
Name: Nolan Allen

Time to Complete: 7 hours 30 minutes


## Description
The goal of this assignment was to implement image encryption and decryption using a Fibonacci linear-feedback shift register. The program can be run with `./PhotoMagic [input file] [output file] [password or 16-bit seed]`.

### Accomplishments
The program successfully encrypts and decrypts an image using a password. I implemented the shift register with an array of ints, using pointer arithmetic to give a constant time complexity to all operations except, of course, initialization and outputting the register as a string.

### Prior Knowledge
Going into this assignment, I had a basic knowledge of shift registers from an assembly language course. This gave me a general idea of how to implement one in this project. Aside from that, my knowledge of encryption techniques extended to basic ciphers, but not much beyond that.

### What I Learned
When I started this project, I had the mindset that it was best to code from the ground up, building everything from scratch. This can be seen in my choice to use an array and pointer arithmetic. This, however, is not always the best way to code. Towards the end of this assignment, I learned that C++'s STL deque class would have provided the same functionality with similar time complexity, and it would have saved time in both coding and bug fixing. This is the project that started to shift my coding style towards using C++ libraries far more frequently.

### Challenges
The main challenge I encountered was implementing the password function, specifically converting a given password to a 16-bit seed with significant variety between similar passwords. My final approach was to convert each valid character (alphanumeric, -, and \textunderscore) to a 6-bit number, then loop simultaneously over the seed digits and through the password characters, XORing the 6 bits from the password character with the next 6 bit of the seed. The result was satisfactory; similar passwords produced very different seeds.


## Acknowledgements
Command line arguments in C/C++ https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/ was used to learn how to pass arguments to a C++ program from the command line.

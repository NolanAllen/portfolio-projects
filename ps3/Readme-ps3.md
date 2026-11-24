# PS3: StringSound

## Contact
Name: Nolan Allen


## Description
The goal of this assignment was to simulate the sound of plucking a guitar string. The program can be run with `./KSGuitarSim (instrument)`, with the optional `instrument` argument currently supporting `Guitar` and `SpringSynth`.

### Accomplishments
The program successfully generates sound data to simulate a guitar. These sounds can be played by pressing various keys on the keyboard. My implementation primarily uses vectors to hold various sound data required for playing the generated sounds through SFML. The sound data itself is generated with a circular buffer class I coded which leverages the STL deque. I chose the deque for its constant time complexity for most operations I intended to use. The STL map is also used to map key inputs to the index of sound data.

### Prior Knowledge
Going into this assignment, I had a thorough knowledge of all the music theory required for this project. This certainly helped when reading the assignment specifications, as well as determining whether the program generated the correct sounds.

### What I Learned
When I started this project, I had no idea how instruments were synthesized. After implementing the Karplus-Strong algorithm, I have developed a basic understanding of one method and an interest in learning more. I also gained much experience reading through SFML documentation.

### Challenges
The main challenge I encountered was initializing the vectors of samples, buffers, and sounds. The issue largely stemmed from not realizing when data from one vector was required for another. Another notable challenge I encountered was figuring out how best to add the capacity for additional instruments. Initially I considered adding variables to the StringSound class to control various aspects of the StringSound::Tick() function such as buffer size. This, however, would have required the addition of several data fields as well as the functions to set them. Still, however, this would not have provided the flexibility I wanted. Instead, my final implementation involved passing a lambda expression to the StringSound object to be used in its Tick() function. This provided much more flexibility in addition to a cleaner interface between the KSGuitarSim program and the StringSound class.


## Acknowledgements
SFML documentation was referenced extensively.

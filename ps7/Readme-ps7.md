# PS7: Kronos Log Parsing

## Contact
Name: Nolan Allen
Time to Complete: 11 hours


## Description
The goal of this assignment was to write a program to parse a log file from a Kronos InTouch time clock to gather time and success data about boots and associated services. The program can be run with `./ps7 [log file]`.

### Accomplishments
The program successfully parses a log file and outputs a report to a file with the name of the log file plus the suffix .rpt. Regex expressions were used to parse the file and identify specific sequences indicating boots and services. As some services could start before others had finished, a vector is used to hold data relating to service starts.

### Prior Knowledge
Going into this assignment, I had a basic knowledge of regex expressions from using them to unit test the random text generator from the previous assignment. This helped me a lot as I already was somewhat accustomed to the syntax.

### What I Learned
This project reminded me of the great benefits of structuring and organizing a program with classes and functions. For this assignment, I didn't write any classes or functions until the towards the end of the project. The result was a rather lengthy main function that works but could be more readable and likely more easily maintainable if more classes and functions were used.

### Challenges
The main challenge I encountered was parsing the file for services. I assumed incorrectly that multiple services would not be running simultaneously, and while fixing this error was easy, discovering it took some time. The assignment specifications also asked for a list of services that were not started in the event of a boot failure. As the log file does not list a service that was not started, I implemented the functionality by having a list of all distinct services I could identify in the file and, in the event of a boot failure, outputting that they had not started.


## Acknowledgements
Professor Daly's presentations were very helpful in writing regex and time code.
The Computing IV Discord server was helpful in getting boost/time_date to work.

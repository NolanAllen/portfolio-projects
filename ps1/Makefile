CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

all: PhotoMagic test

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

PhotoMagic: PhotoMagic.o FibLFSR.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o FibLFSR.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o PhotoMagic test

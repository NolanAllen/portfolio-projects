CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB =  -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: KSGuitarSim test lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

KSGuitarSim: KSGuitarSim.o StringSound.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o StringSound.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.hpp

clean:
	rm *.o KSGuitarSim test

CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB =
# valgrind command:	valgrind --tool=massif --leak-check=full ./EDistance < sequence/ecoli2500.txt > output.txt

all: EDistance lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

EDistance: main.o EDistance.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.hpp

clean:
	rm *.o EDistance

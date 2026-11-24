CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lboost_unit_test_framework
# valgrind command:	valgrind --tool=memcheck --leak-check=full ./TextWriter 1000 10 < tomsawyer.txt

all: TextWriter WordWriter test lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

TextWriter: TextWriter.o RandWriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

WordWriter: WordWriter.o RandWordWriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: test.o RandWriter.o RandWordWriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.hpp

clean:
	rm *.o TextWriter WordWriter test

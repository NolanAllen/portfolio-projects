CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-window -lsfml-system

all: snowflake lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

snowflake: snowflake.o Triangle.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *

clean:
	rm *.o snowflake

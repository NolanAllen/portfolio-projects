CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

all: sfml-app lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

sfml-app: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.hpp

clean:
	rm *.o sfml-app

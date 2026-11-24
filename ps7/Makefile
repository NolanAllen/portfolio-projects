CC = g++
CFLAGS = --std=c++14 -Wall -Werror -pedantic
LIB = -lboost_date_time
# valgrind command:	valgrind --tool=memcheck --leak-check=full ./ps7 device5_intouch.log

all: ps7 lint

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

ps7: KronosLogParser.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

lint:
	cpplint --filter=-runtime/references,-build/c++11 --root=. *.cpp *.hpp

clean:
	rm *.o ps7

CC = g++
FLAGS = -O3 -std=c++20 -pedantic -Wall -Wextra -o $@
CFLAGS = -c $< $(FLAGS)
OBJS = main.o Solution.o
EXE = solve.exe

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FLAGS) $^

main.o: main.cpp Solution.h Rule.h Range.h Point.h
	$(CC) $(CFLAGS)

Solution.o: Solution.cpp Solution.h Rule.h Range.h Point.h
	$(CC) $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXE)

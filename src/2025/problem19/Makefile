CC = g++
FLAGS = -O3 -std=c++20 -pedantic -Wall -Wextra -o $@
CFLAGS = -c $< $(FLAGS)
OBJS = main.o
EXE = solve.exe

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(FLAGS) $^

main.o: main.cpp Solution.h tree.h
	$(CC) $(CFLAGS)

clean:
	rm -f $(OBJS) $(EXE)

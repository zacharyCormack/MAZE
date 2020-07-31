#ifndef MAZE
#define MAZE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

typedef struct
{
	bool type;
	unsigned left;
	unsigned right;
} Point;

typedef struct
{
	unsigned size;
	Point points[];
} Maze;

Maze make_maze(unsigned);
void step(unsigned*, unsigned**, Maze*);

#endif
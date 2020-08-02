#ifndef MAZE
#define MAZE
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
using namespace std;

typedef struct
{
	unsigned short size;
	vector<unsigned short> connections;
} Maze;

Maze make_maze(unsigned short);
void step(unsigned short*, Maze*);

#endif
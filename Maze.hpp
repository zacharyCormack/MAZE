#ifndef MAZE
#define MAZE
#define REPEAT22(x) x x x x x x x x x x x x x x x x x x x x x x
#define REPEAT7(x)  x x x x x x x
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <cmath>
using namespace std;

struct Colour
{
	char nm[7];
};

typedef struct
{
	vector<unsigned short> connections;
	vector<unsigned char> doors;
	unsigned char room;
} Point;

typedef struct
{
	unsigned short size;
	vector<Point> points;
} Maze;

Maze make_maze(unsigned short, float);
bool step(Point*, Maze*);

extern vector<Colour> door_colours;
extern vector<Colour> room_colours;

#endif

#ifndef MAZE
#define MAZE
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

typedef struct
{
	unsigned short room_num;
	vector<unsigned short> connections;
}	Point;

typedef struct
{
	unsigned short size;
	vector<Point> points;
} Maze;

Maze make_maze(unsigned short);
bool step(Point*, Maze*);

#endif
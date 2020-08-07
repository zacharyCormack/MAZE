#ifndef MAZE
#define MAZE
#define REPEAT24(x) x x x x x x x x x x x x x x x x x x x x x x x x
#define REPEAT7(x) x x x x x x x
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <cmath>
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

Maze make_maze(unsigned short, float);
bool step(Point*, Maze*);

#endif
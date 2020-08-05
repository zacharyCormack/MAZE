#ifndef MAZE
#define MAZE
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <vector>
#define REPEAT11(x) x x x x x x x x x x x
#define REPEAT7(x) x x x x x x x
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
#include "Maze.h"

int main()
{
	printf("WELCOME TO THE MAZE.\nGame size: ");
	unsigned size;
	scanf("%d", &size);
	Maze game = make_maze(size);
	unsigned pos=0;
	unsigned* depths = (unsigned*)malloc(size*sizeof(unsigned));
	while(pos<size)
		step(&pos, &depths, &game);
	return 0;
}
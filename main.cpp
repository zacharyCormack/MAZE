#include "Maze.hpp"

int main()
{
	system("tabs -2");
	cout << "WELCOME TO THE MAZE.\nGame size: ";
	unsigned size;
	cin >> size;
	Maze game = make_maze(size);
	unsigned short pos=0;
	while(pos<size-1)
		step(&pos, &game);
	return 0;
}
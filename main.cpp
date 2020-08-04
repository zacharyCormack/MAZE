#include "Maze.hpp"

int main()
{
	cout << "\nWELCOME TO THE MAZE.\nGame size: ";
	unsigned size;
	cin >> size;
	Maze game = make_maze(size);
	unsigned short timer=51;
	Point point = game.points[0];
	cout << "\n\e[s";
	while(step(&point, &game)&&--timer)
		cout << "\e[u\e[KTIMER: " << timer << "\n";
	cout << "\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K\e[A\e[K";
	cout << "\nYOU" << (timer?"WIN":"LOSE") << "!\n";
	cin.ignore();
	return 0;
}
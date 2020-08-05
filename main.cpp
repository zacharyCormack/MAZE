#include "Maze.hpp"

int main()
{
	bool play_again=true;
	while (play_again)
	{
		cout << "\nWELCOME TO THE MAZE.\nGame size: ";
		unsigned size;
		cin >> size;
		Maze game = make_maze(size);
		unsigned short timer=size*size/8+size+8;
		Point point = game.points[0];
		cout << "\n\e[s";
		while(step(&point, &game)&&--timer)
			cout << "\e[u\e[KTIMER: " << timer << "\n";
		cout << REPEAT11("\e[A\e[K") << "\nYOU " << (timer?"WIN":"LOSE") << "!\n";
		cin.ignore();
		string ans = "";
		while (ans != "y")
		{
			cout << "\nPlay again? y/n: ";
			cin >> ans;
			if (ans == "n")
			{
				play_again=false;
				break;
			}
		}
	}
	return 0;
}
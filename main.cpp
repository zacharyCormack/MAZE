#include "Maze.hpp"

int main()
{
	unsigned high_score=0;
	bool play_again=true;
	while (play_again)
	{
		cout << "\nWELCOME TO THE MAZE.\nGame size: ";
		unsigned size;
		cin >> size;
		cout <<
		"Choose Difficulty Value:\n"
		"  1.5  Beginner\n"
		"  2    Easy\n"
		"  2.5  Moderate\n"
		"  3    Challenging\n"
		"  3.5  Difficult\n"
		"  4.5  Hard\n"
		"  5    Very Hard\n"
		"  6    Insane\n"
		"Difficuly: ";
		float difficulty;
		cin >> difficulty;
		Maze game = make_maze(size, (difficulty-1)/difficulty);
		unsigned short timer=size*size/8+size+8;
		unsigned short max = timer;
		Point point = game.points[0];
		cout << "\n\e[s";
		while(step(&point, &game)&&--timer)
			cout << "\e[u\e[KTIMER: " << timer << "\n";
		cout << REPEAT22("\e[A\e[K") << "\nYOU " << (timer?"WIN":"LOSE") << "!\n";
		if (timer)
		{
			unsigned score=(unsigned)(difficulty*log(size)*timer/max);
			high_score=high_score>score?high_score:score;
			cout << "SCORE: " << score << "\nHIGH SCORE: " << high_score;
		}
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
		// if (play_again)
			cout << REPEAT7("\e[A\e[K");
	}
	return 0;
}
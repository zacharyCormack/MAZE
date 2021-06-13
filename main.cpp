#include "Maze.hpp"

unsigned get_scr(float df, unsigned sz, unsigned short tm, unsigned short mx)
{
	return (unsigned)(df*log(sz)*tm/mx);
}

int main()
{
	unsigned high_score=0;
	ifstream record(".hiscr");
	if (record)
		record >> high_score;
	bool play_again=true;

	door_colours.push_back((Colour){"red   "});
	door_colours.push_back((Colour){"orange"});
	door_colours.push_back((Colour){"yellow"});
	door_colours.push_back((Colour){"green "});
	door_colours.push_back((Colour){"blue  "});
	door_colours.push_back((Colour){"violet"});

	room_colours.push_back((Colour){"red   "});
	room_colours.push_back((Colour){"orange"});
	room_colours.push_back((Colour){"yellow"});
	room_colours.push_back((Colour){"green "});
	room_colours.push_back((Colour){"blue  "});
	room_colours.push_back((Colour){"violet"});

	while (play_again)
	{
		cout <<
		"\nWELCOME TO THE MAZE.\n"
		"Choose Difficulty Value:\n"
		"  1.5  Beginner\n"
		"  2    Easy\n"
		"  2.5  Moderate\n"
		"  3    Challenging\n"
		"  3.5  Difficult\n"
		"  4    Hard\n"
		"  5    Very Hard\n"
		"  6    Insane\n"
		"Difficuly: ";

		float difficulty;
		cin >> difficulty;
		unsigned size=0;
		unsigned min=5*difficulty;

		cout << "Size must be at least " << min << " for this difficulty level.\n\n";

		while (size<min)
		{
			cout << "\e[A\e[KGame size: ";
			cin >> size;
		}

		Maze game = make_maze(size, (difficulty-1)/difficulty);
		unsigned short timer=size*size/8+size+8;
		unsigned short max = timer;
		Point point = game.points[0];

		cout << "\n\e[s";

		while(step(&point, &game)&&--timer)
			cout << "\e[u\e[KTIMER: " << timer << " (" << get_scr(difficulty, size, timer, max) << ")\n";
		
		cout << REPEAT7("\e[K\e[A") "\e[u" REPEAT7("\n") REPEAT22("\e[A\e[K") << "\n\nYOU " << (timer?"WIN":"LOSE") << "!\n";

		if (timer)
		{
			unsigned score=get_scr(difficulty, size, timer, max);
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

		cout << "\n" REPEAT7("\e[A\e[K");
	}

	ofstream new_record(".hiscr");
	new_record << high_score;
	
	return 0;
}

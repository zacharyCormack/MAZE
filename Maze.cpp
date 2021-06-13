#include "Maze.hpp"

vector<Colour> door_colours, room_colours;

void link_rooms(unsigned start, unsigned end, Maze *maze, float d)
{
	if (start==end)
		return;

	if (start+1==end)
	{
		unsigned short door = rand() % door_colours.size();

		maze->points[start].connections.push_back(end  );
		maze->points[end  ].connections.push_back(start);

		maze->points[start].doors.push_back(door);
		maze->points[end  ].doors.push_back(door);

		return;
	}

	unsigned a = 0;

	if (rand()%2)
	{
		while ((float)rand()/RAND_MAX<d)
			if (++a==end-start-1)
				break;
		
		unsigned short door = rand() % door_colours.size();

		maze->points[start    ].connections.push_back(start+a+1);
		maze->points[start+a+1].connections.push_back(start    );

		maze->points[start+a+1].doors.push_back(door);
		maze->points[start    ].doors.push_back(door);

		link_rooms(start, start+a, maze, d);
		link_rooms(start+a+1, end, maze, d);
	}
	else
	{
		while ((float)rand()/RAND_MAX>d)
			if (a++==end-start-1)
				break;
		
		link_rooms(start, start+a, maze, d);
		link_rooms(start+a, end, maze, d);
	}
}

Maze make_maze(unsigned short n, float d)
{
	srand((unsigned)time(NULL));
	
	unsigned i=n;
	vector<Point> points;

	while (i--)
	{
		Point point;
		point.room=rand() % room_colours.size();
		points.push_back(point);
	}

	Maze m = (Maze){n, points};
	link_rooms(0, n-1, &m, d);

	return m;
}

bool step(Point *spot, Maze *maze)
{
	cout << "\e[KRoom: " << room_colours[spot->room].nm << "\nThis room has " << spot->connections.size() << " door" << (spot->connections.size()!=1?"s":"") << "\e[K\n\e[K";

	vector<unsigned short> choices, chc_opts = spot->connections;
	vector<unsigned char>  colours, clr_opts = spot->doors;

	while (chc_opts.size())
	{
		unsigned char pos = rand() % chc_opts.size();

		choices.push_back(chc_opts[pos]);
		colours.push_back(clr_opts[pos]);

		chc_opts.erase(chc_opts.begin() + pos);
		clr_opts.erase(clr_opts.begin() + pos);
	}

	for(unsigned i=0; i<choices.size(); i++)
		cout << i+1 << ": " << door_colours[colours[i]].nm << " door, leading to a " << room_colours[maze->points[choices[i]].room].nm << " room.\n\e[K";

	unsigned choice=0;
	cout << REPEAT22("\n\e[K") "\e[19A";

	while (choice == 0 || choice > choices.size())
	{
		cout << "\e[2A\e[KWhich door?\n\e[K";
		cin >> choice;
	}

	if (choices[choice-1] == maze->size-1)
		return false;
	
	*spot=maze->points[choices[choice-1]];

	return true;
}

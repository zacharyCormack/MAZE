#include "Maze.hpp"

void link_rooms(unsigned start, unsigned end, Maze* maze)
{
	if (start==end)
		return;
	if (start+1==end)
	{
		maze->points[start].connections.push_back(end);
		maze->points[end].connections.push_back(start);
		return;
	}
	unsigned a = 0;
	while (rand()%2)
		if (++a==end-start-1)
			break;
	if (rand()%2)
	{
		maze->points[start].connections.push_back(start+a+1);
		maze->points[start+a+1].connections.push_back(start);
		link_rooms(start, start+a, maze);
		link_rooms(start+a+1, end, maze);
	}
	else
	{
		link_rooms(start, start+a, maze);
		link_rooms(start+a, end, maze);
	}
}

Maze make_maze(unsigned short n)
{
	srand((unsigned)time(NULL));
	vector<unsigned short> nums;
	unsigned i=0;
	while (i++<n)
		nums.push_back(i);
	random_shuffle(nums.begin(), nums.end());
	vector<Point> points;
	while (i--)
	{
		Point point = (Point){.room_num=nums[i]};
		points.push_back(point);
	}
	Maze m = (Maze){n, points};
	link_rooms(0, n-1, &m);
	return m;
}

bool step(Point* spot, Maze* maze)
{
	cout << "\e[KRoom ID: " << spot->room_num << "\nThis room has " << spot->connections.size() << " door" << (spot->connections.size()!=1?"s":"") << "\e[K\n\e[K";
	vector<unsigned short> choices = spot->connections;
	random_shuffle(choices.begin(), choices.end());
	for(unsigned i=0; i<choices.size(); i++)
		cout << i+1 << ": ROOM ID " << maze->points[choices[i]].room_num << "\n\e[K";
	unsigned choice=0;
	cout << REPEAT7("\n\e[K") "\e[4A";
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
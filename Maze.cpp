#include "Maze.hpp"

int mygetch()
{
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

	ch = getchar();
	
	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

void link_rooms(unsigned start, unsigned end, Maze* maze)
{
	// cout << "linking " << start << " to " << end << '\n';
	// usleep(375000);
	if (start==end)
		return;
	if (start+1==end)
	{
		maze->connections.push_back(start);
		maze->connections.push_back(end);
		return;
	}
	unsigned a = 0;
	while (rand()%2)
		if (++a==end-start-1)
			break;
	if (rand()%2)
	{
		maze->connections.push_back(start);
		maze->connections.push_back(start+a);
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
	Maze m = (Maze){.size=n};
	link_rooms(0, n-1, &m);
	return m;
}

void step(unsigned short* spot, Maze* maze)
{
	unsigned num_opts=0;
	for (unsigned i=0; i<maze->size*2-2; i++)
		if (maze->connections[i]==*spot)
			num_opts++;
	cout << "This room has " << num_opts << " doors\n";
	hash<unsigned short> mk_hash;
	size_t spot_hash = mk_hash(*spot);
	cout << spot_hash << "\n";
	// for (unsigned j=0; j<7; j++)
	// {
	// 	for (unsigned k=0; j<num_opts; j++)
	// 		if (j==3)
	// 			cout << "\e[0m   \e[34;41m  " << k << "   []  ";
	// 		else
	// 			cout << "\e[0m   \e[34;41m          ";
	// 	cout << "\e[0m\n";
	// }
	unsigned i=0, choice;
	cout << "Which door?\n";
	cin >> choice;
	choice--;
	while (choice)
		if (maze->connections[i++]==*spot)
			--choice;
	*spot+=maze->connections[(i%2?i-1:i)];
}
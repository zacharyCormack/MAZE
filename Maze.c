#include "Maze.h"

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

Maze make_maze(unsigned n)
{
	srand((unsigned)time(NULL));
	Maze* m = malloc(sizeof(Maze)+sizeof(Point)*n);
	*m = (Maze){.size=n};
	Point ms[] = &(m->points[0]);
	unsigned depths[n];
	for(unsigned i=0; i<n; i++)
	{
		unsigned j=0;
		while(depths[++j])
			depths[j]--;
		ms[i].left=0;
		while(rand()%2&ms[i].left<depths[j]-1)
			ms[i].left++;
		ms[i].right=depths[j]-ms[i].left-1;
		depths[j+1]=ms[i].left;
		ms[i].type=rand()%2;
	}
	return *m;
}

void step(unsigned* spot, unsigned** depths, Maze* maze)
{

}
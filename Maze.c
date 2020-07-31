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
	Maze* m = (Maze*)malloc(sizeof(Maze)+sizeof(Point)*n);
	*m = (Maze){.size=n};
	Point* ms = &(m->points[0]);
	unsigned depths[n];
	for(unsigned i=0; i<n; i++)
	{
		unsigned j=0;
		while(depths[++j])
			depths[j]--;
		ms[i].left=0;
		while(rand()%2 && ms[i].left<depths[j]-1)
			ms[i].left++;
		ms[i].right=depths[j]-ms[i].left-1;
		depths[j+1]=ms[i].left;
		ms[i].type=rand()%2;
	}
	Maze maze = *m;
	free(m);
	return maze;
}

void step(unsigned* spot, unsigned** depths, Maze* maze)
{
	unsigned i=0;
	unsigned base_opts[3] = {*spot-1, *spot+1, -1};
	while (*depths[++i])
		if (maze->points[*spot-*depths[i]].type)
		{
			if (*depths[i]+1==maze->points[*spot-*depths[i]].left)
				base_opts[0] = -1;
			if (*depths[i]+1==maze->points[*spot-*depths[i]].left)
				base_opts[1] = -1;
			if (*depths[i] == 1)
				base_opts[2] = maze->points[*spot].left+*spot;
		}
	unsigned num_opts = 2;
	if (base_opts[0] >= maze->size)
		num_opts--;
	if (base_opts[1] >= maze->size)
		num_opts--;
	if (base_opts[2] < maze->size)
	{
		unsigned slot = *spot-*depths[i];
		num_opts++;
		while (maze->points[slot].type)
		{
			num_opts++;
			slot += maze->points[slot].left;
		}
	}
	printf("\e[34;41m");
	unsigned choice = 0;
	bool cont=true;
	while (cont)
	{
		switch (mygetch())
		{
		case 'a':
			if (choice > 0)
				choice--;
			break;
		case 's':
			if (choice++==num_opts)
				choice--;
			break;
		case 'd':
			cont=false;
			break;
		default:
			break;
		}
		for (unsigned j=0; j<7; j++)
		{
			for (unsigned k=0; j<num_opts; j++)
				if (j==3)
					if (k==choice)
						printf("\t      88  ");
					else
						printf("\t      []  ");
				else
					printf("\t          ");
			printf("\n");
		}
	}
	unsigned choice_slot=choice;
	if (base_opts[0] >= maze->size)
		choice_slot++;
	if (base_opts[1] >= maze->size && choice_slot)
		choice_slot++;
	switch (choice_slot)
	{
	case 0:
		for (unsigned j=0; j<i; j++)
			if (maze->points[*spot-(++*depths[j])].left==*depths[j])
				*depths[j]=0;
		break;
	case 1:
		for (unsigned j=0; j<i; j++)
			if (depths[j])
				(*depths[j])--;
		break;
	default:
		unsigned slot;
		unsigned j=i;
		for (unsigned slot=*depths[j]; j<i+choice_slot-1; j++)
		{
			unsigned add=maze->points[slot].left;
			for (unsigned k=0; k<j; k++)
				*depths[k]+=add;
			slot+=add;
		}
		*spot=slot;
		break;
	}
}
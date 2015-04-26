#include <cstdio>
#include <cstdlib>
#include <string>
#include <iostream>

void errorExit(std::string const &emsg)
{
	std::cout<<emsg;
	exit(1);
}
char COLOR;
int DEPTHLIMIT, TIMELIMIT1, TIMELIMIT2;
std::string cmd;


struct move
{
	int x;
	int y;
};

void readMove(struct move *opponent_move)
{
	scanf("%d %d", &(opponent_move->x), &(opponent_move->y));
}

/*int play_as defines to either start by reading or moving
Start by reading: 1
Start by moving: 0
*/
void play(int play_as)
{
	//Play as white
	if (play_as)
	{
		//readMove();
		//play(0);
	}
	else
	{
		//makeMove();
		//play(1);
	}	
}
int main(int argc, char *argv[])
{
	//if (argc != 5)
		//errorExit("Bad input. Terminating.\n");
	std::cin>>cmd>>COLOR>>DEPTHLIMIT>>TIMELIMIT1>>TIMELIMIT2;
	if (COLOR == 'B')
		play(0);
	else if (COLOR == 'W')
		play(1);
	return 0;
}

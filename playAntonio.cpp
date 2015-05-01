#include<iostream>
#include<cstdio> //not actually needed
#include<cstring>
#include<ctime>
#include<vector>
#include <climits>
#include "state.h"

#define SIZE 8
State best = NULL:
char COLOR;
int DEPTHLIMIT, TIMELIMIT1, TIMELIMIT2;
clock_t move_start, game_start, now;

int currentState[SIZE][SIZE];


struct move {
     int x;
     int y;
};


void initBoard(int [] [] board)
{
	for(int i = 0; i<SIZE; i++)
		for (int j = 0; j<SIZE; j++)
			board[i][j] = 0;
  	board[3][3] = -1;
	board[4][4] = -1;
	board[3][4] = 1;
	board[4][3] = 1;
	return;
}
int readMove(struct move *opponent_move)
{
	char movebuf[10];
	if (fgets(movebuf, 10, stdin) != NULL)
	{
		start = clock();
		if (strncmp(movebuf, "pass", 4)!=0)	
    		return (!scanf("%d %d\n", &(opponent_move->x), &(opponent_move->y)));
	}
}

void updateState(int x, int y, player)
{
	currentState[x][y] = player;
	return;
}
std::vector<State> actions (const State& state, int player) {
  std::vector<State> ret;
  // Build player1's move set
  for (size_t i = 0; i < SIZE; i++) {
    for (size_t j = 0; j < SIZE; j++) {
      State next(&state, i, j);
      bool flag = false; // Have we flipped any pieces?
      if (next[i][j] == State::Value::FREE) {
        //Right
        for (size_t k = i + 1; k < SIZE; k++) {
          if (next[k][j] == player) {
            for (size_t l = i + 1; l < k; l++) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[k][j] == State::Value::FREE)
            break;
        }
        //Up+Right
        for (size_t k = 1; i + k < SIZE && j + k < SIZE; k++) {
          if (next[i + k][j + k] == player) {
            for (size_t l = 1; l < k; l++) {
              next[i + l][j + l] = player;
            }
            flag = true;
            break;
          }
          if (next[i + k][j + k] == State::Value::FREE)
            break;
        }
        //Up
        for (size_t k = i + 1; k < SIZE; k++) {
          if (next[i][k] == player) {
            for (size_t l = j + 1; l < k; l++) {
              next[i][l] = player;
            }
            flag = true;
            break;
          }
          if (next[i][k] == State::Value::FREE)
            break;
        }
        //Up+Left
        for (size_t k = 1; i - k >= 0 && j + k < SIZE; k++) {
          if (next[i - k][j + k] == player) {
            for (size_t l = 1; l < k; l++) {
              next[i - l][j + l] = player;
            }
            flag = true;
            break;
          }
          if (next[i - k][j + k] == State::Value::FREE)
            break;
        }
        //Left
        for (size_t k = i - 1; k >= 0; k--) {
          if (next[k][j] == player) {
            for (size_t l = i - 1; l > k; l--) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[k][j] == State::Value::FREE)
            break;
        }
        //Left+Down
        for (size_t k = 1; i - k >= 0 && j - k >= 0; k--) {
          if (next[i - k][j - k] == player) {
            for (size_t l = 1; l < k; l++) {
              next[i - l][j - l] = player;
            }
            flag = true;
            break;
          }
          if (next[i - k][j - k] == State::Value::FREE)
            break;
        }
        //Down
        for (size_t k = j - 1; k >= 0; k--) {
          if (next[i][k] == player) {
            for (size_t l = j - 1; l > k; l--) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[i][k] == State::Value::FREE)
            break;
        }
        //Down+Right
        for (size_t k = 1; i + k < SIZE && j - k >= 0; k++) {
          if (next[i + k][j - k] == player) {
            for (size_t l = 1; l < k; l++) {
              next[i + l][j - l] = player;
            }
            flag = true;
            break;
          }
          if (next[i + k][j - k] == State::Value::FREE)
            break;
        }
        if (flag)
          ret.insert(next);
      }
    }
  }
  return ret;
}


//Returns 1 if time is up
int cutoffTest(State state, int depth)
{
	clock_t now = clock();
	if ((now - start) / (CLOCKS_PER_SEC/1000) >= TIMELIMIT1)
		return 1;
	if((now - game_start) / (CLOCKS_PER_SEC/1000) >=TIMELIMIT2)
		return 1;
	if (depth>DEPTHLIMIT)
		return 1;
	return 0;
}

//Takes a pair of coordinates for the move
//When x is set to -1, a pass is done
void makeMove(int x, int y)
{
	if (x == -1)
		printf("pass\n");
	else
		printf("%d %d\n", x, y);
	return;
}

/* player 1 is max player, player -1 is min player */
State alphaBeta(State state, int depth, int alpha, int beta, int player)
{
	int i;
	int value;
	if(cutoffTest(state, depth))
	{
		makeMove(best.move[0], best.move[1]);
    	return best;
	}
	best = NULL; /* Handles early pruning or no possible moves */
	if(player == 1){ //max player
    
    for(State action : actions(state, player)){ // This line requires C++11
      (child, unused) = result(state, action); //todo
      value = alphaBeta(child, depth+1, alpha, beta, -player);

      if(value > alpha){
        alpha = value;
        best = action;
      }
      if(beta <= alpha)
        break; /* beta cut-off */
    }
    return (alpha, best);
  }
  else{ //min player
    for(State action : actions(state, player)){ // This line also requires C++11
      (child, unused) = result(state, action);
      value = alphaBeta(child, depth+1, alpha, beta, -player);

      if(value < beta){
        beta = value;
        best = action;
      }
      if(beta <= alpha) /*alpha cut-off*/
        break; 
    }
    return (beta, best);
  }
}

int cost(const State &state) {
  int cost = 0;
  for(int i = 0; i<SIZE; i++)
    for (int j = 0; j<SIZE; j++)
      cost+=state[i][j];
}

/*
 * Counts stable pieces (those which cannot be fliped)
 * TODO: Fix double counting if a player controlls an entire edge
 * TODO: Fix stable pieces of color other than corner color not being counted
 */
int count_stable (const State& state) {
  int count = 0;
  ssize_t minlen;
  State::Value color;
  
  // Count from top left
  if ((color = state[0][7]) != State::Value::FREE) {
    minlen = -1;
    for (ssize_t i = 0; i < 8 && state[i][7] == color; i++) {
      for (ssize_t j = 7; j > minlen; j--) {
        if (state[i][j] != color)
          minlen = j;
        else
          count++;
      }
    }
  }
  // Count from top right
  if ((color = state[7][7]) != State::Value::FREE) {
    minlen = -1;
    for (ssize_t i = 7; i >= 0 && state[i][7] == color; i--) {
      for (ssize_t j = 7; j > minlen; j--) {
        if (state[i][j] != color)
          minlen = j;
        else
          count++;
      }
    }
  }
  // Count from bottom left
  if ((color = state[0][0]) != State::Value::FREE) {
    minlen = 8;
    for (ssize_t i = 0; i < 8 && state[i][0] == color; i++) {
      for (ssize_t j = 0; j < minlen; j++) {
        if (state[i][j] != color)
          minlen = j;
        else
          count++;
      }
    }
  }
  // Count from bottom right
  if ((color = state[7][0]) != State::Value::FREE) {
    minlen = 8;
    for (ssize_t i = 7; i >= 0 && state[i][0] == color; i--) {
      for (ssize_t j = 0; j < minlen; j++) {
        if (state[i][j] != color)
          minlen = j;
        else
          count++;
      }
    }
  }

  return count;
}

int main()
{
	int player;
	struct move enemy_move;
    std::cin>>COLOR>>COLOR>>DEPTHLIMIT>>TIMELIMIT1>>TIMELIMIT2;
	initBoard();
    if (COLOR == 'B')
	{
		player = -1;
		move_start = clock();
		alphaBeta(State s(currentState), 0, MAX_INT, MIN_INT, player);
	}
	else
		player = 1;
    while (readMove(&enemy_move))
	{	
		updateState(enemy_move.x, enemy_move.y, -player);
		alphaBeta(State s(currentState), 0, MAX_INT, MIN_INT, player);
	}
    return 0;
}

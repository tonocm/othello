#include <iostream>
#include <cstdio> //not actually needed
#include <cstring>
#include <ctime>
#include <vector>
#include <climits>
#include "state.h"

State best = NULL;
char COLOR;
int DEPTHLIMIT, TIMELIMIT1, TIMELIMIT2;
clock_t move_start, game_start, now;

State currentState(NULL, -1, -1);

struct move {
     int x;
     int y;
};

void initBoard(State& board)
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
		if (strncmp(movebuf, "pass", 4)!=0)	
                  return (!scanf("%d %d\n", &(opponent_move->x), &(opponent_move->y)));
	}
}

void updateState(int x, int y, int plyr)
{
  State::Value player;
  if(plyr == 1)
    player = WHITE;
  else
    player = BLACK;
  
	currentState[x][y] = player;
  int xx, yy, xxx, yyy;
  bool flag;

  /* check left */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    --xx;
    if(xx < 0)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(xx=xx; xx < x; xx++)
      currentState[xx][y] = player;
  }
  //else, no flips
  
  /* check right */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    ++xx;
    if(xx >= SIZE)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(xx=xx; xx > x; xx--)
      currentState[xx][y] = player;
  }
  //else, no flips

  /* check down */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    ++yy;
    if(yy >= SIZE)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy > y; yy--)
      currentState[xx][y] = player;
  }
  //else, no flips

  
  /* check up */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    --yy;
    if(yy < 0)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy < y ; yy++)
      currentState[xx][y] = player;
  }
  //else, no flips
  
  /* check down-right */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    ++yy;
    ++xx;
    if(yy >= SIZE || xx >= SIZE)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy > y; yy--){
      --xx;
      currentState[xx][yy] = player;
    }
  }
  //else, no flips
  
  /* check down-left */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    ++yy;
    --xx;
    if(yy >= SIZE || xx < 0)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy > y; yy--){
      ++xx;
      currentState[xx][yy] = player;
    }
  }
  //else, no flips

  /* up-right */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    --yy;
    ++xx;
    if(yy < 0 || xx >= SIZE)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy > y; yy++){
      --xx;
      currentState[xx][yy] = player;
    }
  }
  //else, no flips
  
  /* check up-left */
  flag = true;
  xx = x;
  yy = y;
  while(flag){
    --yy;
    --xx;
    if(yy < 0 || xx < 0)
      break;
    
    if(currentState[xx][yy] == player){
      flag = false;
    } 
  }
  if(!flag){
    for(yy=yy; yy > y; yy++){
      ++xx;
      currentState[xx][yy] = player;
    }
  }
  //else, no flips
  
	return;
}

std::vector<State> actions (const State& state, int plyr) {


  State::Value player;
  if(plyr == 1)
    player = WHITE;
  else
    player = BLACK;

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
  static State best = NULL;
  int i;
  int value;
  vector<State> successors;
  if(cutoffTest(state, depth)) {
      makeMove(best.move[0], best.move[1]);
      return best;
  }

  successors = actions(state, player);
  if (successors.size() == 0) {
    if (depth == 0)
    {
	makeMove(-1, -1);
	return NULL;
    }
    else
      return alphaBeta(state, depth + 1, alpha, beta, -player);
  }
  for(State action : successors){ // This line requires C++11
    value = alphaBeta(child, depth+1, alpha, beta, -player);
    if(player == 1){ //max player 
      if(value > alpha){
        alpha = value;
        best = action;
      }
      if(beta <= alpha)  /* beta cut-off */
        return beta;
    }
    else{ //min player
      if(value < beta){
        beta = value;
        best = action;
      }
      if(beta <= alpha) /*alpha cut-off*/
        return alpha;
    }
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
pair<int, int> count_stable (const State& state) {
  int count[] = {0, 0, 0};
  ssize_t minlen;
  State::Value color;
  
  // Count from top left
  if ((color = state[0][SIZE - 1]) != State::Value::FREE) {
    minlen = -1;
    for (ssize_t i = 0; i < SIZE && state[i][SIZE - 1] == color; i++) {
      for (ssize_t j = SIZE - 1; j > minlen; j--) {
        if (state[i][j] != color)
          minlen = j;
        else
          count[color + 1]++;
      }
    }
  }
  // Count from top right
  if ((color = state[SIZE - 1][SIZE - 1]) != State::Value::FREE) {
    minlen = -1;
    for (ssize_t i = SIZE - 1; i >= 0 && state[i][SIZE - 1] == color; i--) {
      for (ssize_t j = SIZE - 1; j > minlen; j--) {
        if (state[i][j] != color)
          minlen = j;
        else
          count[color + 1]++;
      }
    }
  }
  // Count from bottom left
  if ((color = state[0][0]) != State::Value::FREE) {
    minlen = SIZE;
    for (ssize_t i = 0; i < SIZE && state[i][0] == color; i++) {
      for (ssize_t j = 0; j < minlen; j++) {
        if (state[i][j] != color)
          minlen = j;
        else
          count[color + 1]++;
      }
    }
  }
  // Count from bottom right
  if ((color = state[SIZE - 1][0]) != State::Value::FREE) {
    minlen = SIZE;
    for (ssize_t i = SIZE - 1; i >= 0 && state[i][0] == color; i--) {
      for (ssize_t j = 0; j < minlen; j++) {
        if (state[i][j] != color)
          minlen = j;
        else
          count[color + 1]++;
      }
    }
  }
  return make_pair(count[0], count[2]);
}

int main()
{
    int player;
    struct move enemy_move;
    std::cin>>COLOR>>COLOR>>DEPTHLIMIT>>TIMELIMIT1>>TIMELIMIT2;
    initBoard(currentState);
    game_start = clock();
    if (COLOR == 'B')
    {
	player = -1;
	move_start = clock();
	alphaBeta(currentState, 0, INT_MAX, INT_MIN, player);
    }
    else
	player = 1;
    while (readMove(&enemy_move))
    {
	move_start = clock();
	updateState(enemy_move.x, enemy_move.y, -player);
	alphaBeta(currentState, 0, INT_MAX, INT_MIN, player);
    }
    return 0;
}

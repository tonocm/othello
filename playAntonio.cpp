#include <iostream>
#include <cstdio> //not actually needed
#include <cstring>
#include <ctime>
#include <vector>
#include <climits>
#include "state.h"

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
                  board[i][j] = State::Value::FREE;
  	board[3][3] = State::Value::BLACK;
	board[4][4] = State::Value::BLACK;
	board[3][4] = State::Value::WHITE;
	board[4][3] = State::Value::WHITE;
	return;
}

int readMove(struct move *opponent_move)
{
	char movebuf[10];
	std::cin.getline(movebuf, 10);
        if (!std::cin.good())
          return 0;
        if (strncmp(movebuf, "pass", 4)!=0)	
          return (sscanf(movebuf, "%d %d\n", &(opponent_move->x), &(opponent_move->y)));
        opponent_move->x = opponent_move->y = -1;
        return 1;
}

void updateState(int x, int y, int iplayer)
{
  State::Value player;
  if(iplayer == 1)
    player = State::WHITE;
  else
    player = State::BLACK;
  
  currentState[x][y] = player;
  int xx, yy;
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

std::vector<State> actions (const State& state, int iplayer) {
  State::Value player;
  if(iplayer == 1)
    player = State::WHITE;
  else
    player = State::BLACK;

  std::vector<State> ret;
  // Build player1's move set
  for (ssize_t i = 0; i < SIZE; i++) {
    for (ssize_t j = 0; j < SIZE; j++) {
      State next(&state, i, j);
      bool flag = false; // Have we flipped any pieces?
      if (next[i][j] == State::Value::FREE) {
        //Right
        for (ssize_t k = i + 1; k < SIZE; k++) {
          if (next[k][j] == player) {
            for (ssize_t l = i + 1; l < k; l++) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[k][j] == State::Value::FREE)
            break;
        }
        //Up+Right
        for (ssize_t k = 1; i + k < SIZE && j + k < SIZE; k++) {
          if (next[i + k][j + k] == player) {
            for (ssize_t l = 1; l < k; l++) {
              next[i + l][j + l] = player;
            }
            flag = true;
            break;
          }
          if (next[i + k][j + k] == State::Value::FREE)
            break;
        }
        //Up
        for (ssize_t k = i + 1; k < SIZE; k++) {
          if (next[i][k] == player) {
            for (ssize_t l = j + 1; l < k; l++) {
              next[i][l] = player;
            }
            flag = true;
            break;
          }
          if (next[i][k] == State::Value::FREE)
            break;
        }
        //Up+Left
        for (ssize_t k = 1; i - k >= 0 && j + k < SIZE; k++) {
          if (next[i - k][j + k] == player) {
            for (ssize_t l = 1; l < k; l++) {
              next[i - l][j + l] = player;
            }
            flag = true;
            break;
          }
          if (next[i - k][j + k] == State::Value::FREE)
            break;
        }
        //Left
        for (ssize_t k = i - 1; k >= 0; k--) {
          if (next[k][j] == player) {
            for (ssize_t l = i - 1; l > k; l--) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[k][j] == State::Value::FREE)
            break;
        }
        //Left+Down
        for (ssize_t k = 1; i - k >= 0 && j - k >= 0; k--) {
          if (next[i - k][j - k] == player) {
            for (ssize_t l = 1; l < k; l++) {
              next[i - l][j - l] = player;
            }
            flag = true;
            break;
          }
          if (next[i - k][j - k] == State::Value::FREE)
            break;
        }
        //Down
        for (ssize_t k = j - 1; k >= 0; k--) {
          if (next[i][k] == player) {
            for (ssize_t l = j - 1; l > k; l--) {
              next[l][j] = player;
            }
            flag = true;
            break;
          }
          if (next[i][k] == State::Value::FREE)
            break;
        }
        //Down+Right
        for (ssize_t k = 1; i + k < SIZE && j - k >= 0; k++) {
          if (next[i + k][j - k] == player) {
            for (ssize_t l = 1; l < k; l++) {
              next[i + l][j - l] = player;
            }
            flag = true;
            break;
          }
          if (next[i + k][j - k] == State::Value::FREE)
            break;
        }
        if (flag)
          ret.push_back(std::move(next));
      }
    }
  }
  return ret;
}

//Returns 1 if time is up
int cutoffTest(int depth)
{
	clock_t now = clock();
	if ((now - move_start) / (CLOCKS_PER_SEC/1000) >= TIMELIMIT1)
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
std::pair<int, move> alphaBeta(State &state, int depth, int alpha, int beta, int player)
{
  std::pair<int, move> best;
  int value;
  std::vector<State> successors;
  if(cutoffTest(depth)) {
      makeMove(best.second.y, best.second.y);
      return best;
  }

  successors = actions(state, player);
  if (successors.size() == 0) {
    if (depth == 0)
    {
	makeMove(-1, -1); //Pass
	return std::make_pair(player == 1 ? alpha : beta,  move{.x = -1, .y = -1});
    }
    else
      return alphaBeta(state, depth + 1, alpha, beta, -player);
  }
  for(State& action : successors){ // This line requires C++11
    value = alphaBeta(action, depth + 1, alpha, beta, -player).first;
    if(player == 1){ //max player 
      if(value > alpha){
        alpha = value;
        best = std::make_pair(alpha, move{.x = action.move[0], .y = action.move[1]});
      }
      if(beta <= alpha)  /* beta cut-off */
        return std::make_pair(beta, move{.x = state.move[0], .y = state.move[1]});
    }
    else{ //min player
      if(value < beta){
        beta = value;
        best = std::make_pair(beta, move{.x = action.move[0], .y = action.move[1]});
      }
      if(beta <= alpha) /*alpha cut-off*/
        return std::make_pair(alpha, move{.x = state.move[0], .y = state.move[1]});
    }
  }
  return best;
}

int cost(State &state) {
  int cost = 0;
  for(int i = 0; i<SIZE; i++)
    for (int j = 0; j<SIZE; j++)
      cost+=state[i][j];
  return cost;
}

/*
 * Counts stable pieces (those which cannot be fliped)
 * TODO: Fix double counting if a player controlls an entire edge
 * TODO: Fix stable pieces of color other than corner color not being counted
 */
std::pair<int, int> count_stable (State& state) {
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
  return std::make_pair(count[0], count[2]);
}

int main()
{
    int player;
    struct move enemy_move;
    char buf[48];
    std::cin.getline(buf, 48);
    sscanf(buf, "game %c %d %d %d\n", &COLOR, &DEPTHLIMIT, &TIMELIMIT1, &TIMELIMIT2);
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
        fprintf(stderr, "enemy move: %d %d\n", enemy_move.x, enemy_move.y);
	move_start = clock();
	updateState(enemy_move.x, enemy_move.y, -player);
	alphaBeta(currentState, 0, INT_MAX, INT_MIN, player);
    }
    return 0;
}

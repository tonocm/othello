#include<iostream>
#include<cstdio> //not actually needed
#include<cstring>
#include<ctime>
#include<vector>
#include "state.h"

State best = NULL:
char COLOR;
int DEPTHLIMIT, TIMELIMIT1, TIMELIMIT2;
<<<<<<< HEAD
clock_t move_start, now;

struct move
{
=======
struct move {
>>>>>>> 2a7eee60d58927ccf42ef7562a7cf846b4098daf
     int x;
     int y;
};

<<<<<<< HEAD
void readMove(struct move *opponent_move)
{
    scanf("%d %d\n", &(opponent_move->x), &(opponent_move->y));
	start = clock();
=======
void readMove(struct move *opponent_move) {
     scanf("%d %d\n", &(opponent_move->x), &(opponent_move->y));
>>>>>>> 2a7eee60d58927ccf42ef7562a7cf846b4098daf
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
int cutOffTest(State state, int depth)
{
	clock_t now = clock();
	if ((now - start) / (CLOCKS_PER_SEC/1000) >= TIMELIMIT1)
		return 1;
	if (depth>DEPTHLIMIT)
		return 1;
	return 0;
}

/* player 1 is max player, player 0 is min player */
void alphaBeta(State state, int depth, int alpha, int beta, int player){
  int i;
  int value;
  if(cutoffTest(state, depth)) //todo
    return (eval(state),null);//todo

  best = NULL; /* Handles early pruning or no possible moves */

  if(player == 1){ //max player
    
    for(State action : actions(state, player)){ // This line requires C++11

      (child, unused) = result(state, action); //todo
      value = alphaBeta(child, depth+1, alpha, beta, 0);

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
      value = alphaBeta(child, depth+1, alpha, beta, 0);

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

int main()
{
     std::cin>>COLOR>>COLOR>>DEPTHLIMIT>>TIMELIMIT1>>TIMELIMIT2;
     if (COLOR == 'B')
	  ;
     if (COLOR == 'W')
	  ;
     return 0;
}

#include<iosAtream>
#include<cstdio> //not actually needed
#include<cstring>
#include<time.h>
#include<vector>

int SIZE = 8;

class State{  
public:
  enum Value { // Enum of possible states of a grid space
    WHITE = 1,
    BLACK = -1,
    FREE = 0
  };

  State() : State(NULL){

  }

  State(const State *parent, int move_x, int move_y){
    this->parent = parent;
    if (parent) {
      memcpy(_state, parent->_state, sizeof(Value) * SIZE * SIZE);
    }
    move[0] = move_x;
    move[1] = move_y;
  }

  State (State&& s) {
    memcpy(_state, s._state, sizeof(Value) * SIZE * SIZE);
    parent = s.parent;
    memcpy(move, s.move, sizeof(int) * 2);
  }

  Value *operator[] (size_t idx) {
    return _state[idx];
  }
private:
  Value _state[SIZE][SIZE];
  State *parent;
  int move[2];
};

/* player 1 is max player, player 0 is min player */
void alphaBeta(board state, int depth, int alpha, int beta, int player){

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

 int i;
  int actionsLength=0;
  
  if(cutoffTest(state, depth))
    return (eval(state),null);

  best = null; /* Handles early pruning or no possible moves */
  if(player == 1){ //max player
    
    for(State action : actions(state, player)){ // This line requires C++11

      (child, unused) = result(state, action);
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



int cost(int [][] state) {
  int cost = 0;
  for(int i = 0; i<sizeof(state[0]); i++)
	  for (int j = 0; j<sizeof(state[0]); j++)
      cost+=state[i][j];
}

int main(){

  alphaBeta(arg1, arg2, arg3, arg4, arg5);
  
  return 1;
}

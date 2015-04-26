#include <iostream>
#include <cstdio> //not actually needed
#include <cstring>
#include <time.h>
#include <vector>
class State{  
public:
  enum Value { // Enum of possible states of a grid space
    WHITE = 1,
    BLACK = -1,
    FREE
  };

  State() : State(NULL){

  }

  State(const State *parent, int move_x, int move_y){
    this->parent = parent;
    if (parent) {
      memcpy(_state, parent->_state, sizeof(Value) * 64);
    }
    move[0] = move_x;
    move[1] = move_y;
    someting = -1; //wrote whatever, just testing
  }

  State (State&& s) {
    memcpy(_state, s._state, sizeof(Value) * 64);
    parent = s.parent;
    memcpy(move, s.move, sizeof(Value) * 64);
  }

  Value *operator[] (size_t idx) {
    return _state[idx];
  }
private:
  Value _state[8][8];
  State *parent;
  int move[2];
  int something;
};


std::vector<State> actions (const State& state, int player) {
  std::vector<State> ret;
  if (player == 1) {
    // Build player1's move set
    for (size_t i = 0; i < 8; i++) {
      for (size_t j = 0; j < 8; j++) {
        State next(&state);
        bool flag;
        if (next[i][j] == State::Value::FREE) {
          for (size_t k = i + 1; k < 8; k++) {
            
          }
        }
      }
    }
  }
  else {
    // Build player2's move set
  }
  return ret;
}

/* player 1 is max player, player 0 is min player */
void alphaBeta(State state, int depth, int alpha, int beta, int player){

  int i;
  int actionsLength=0;
  
  if(cutoffTes(state, depth))
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

int main(){

  alphaBeta(arg1, arg2, arg3, arg4, arg5);
  
  return 1;
}

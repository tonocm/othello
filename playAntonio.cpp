#include<iostream>
#include<cstdio>
#include<time.h>

typedef signed char board[8][8];
int BOARDLENGTH = 8;

void makeBoard(board &b){
  int i, j;
  for(i=0; i < BOARDLENGTH; i++){
    for(j=0; j < BOARDLENGTH;j++){
      b[i][j] = 'o';
    }
  }
}

class State{
  State * parent;
  int something;
  board current;
  
public:
  State(){
    parent = null;
    someting = -1; //wrote whatever, just testing
  }
  State(State &parent){
    this->parent = &parent;
    someting = -1; //wrote whatever, just testing
  }
};

/* player 1 is max player, player 0 is min player */
void alphaBeta(board state, int depth, int alpha, int beta, int player){
  int i;
  int actionsLength=0;
  
  if(cutoffTest(state, depth))
    return (eval(state),null);

  best = null; /* Handles early pruning or no possible moves */
  if(player == 1){ //max player
    
    for(i=0; i < actionsLength; i++){
      result(state, action); //links the result with its parent
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
    for(i=0; i < actionsLength; i++){
      (child, unused) = result(state, action);
      value = alphaBeta(child, depth+1, alpha, beta, 0);

      if(value < beta){
        beta = value;
        best = action;
      }
      if(beta <= alpha) /*alpha cut-off*/
        break; 
    }
    return (besta, best);
  }
}

int main(){

  alphaBeta(arg1, arg2, arg3, arg4, arg5);
  
  return 1;
}

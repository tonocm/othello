#include<iostream>
#include<cstdio> //not actually needed
#include<time.h>

class State{

  State * parent;
  int something;
  
public:
  State(){
    parent = null;
    someting = -1; //wrote whatever, just testing
    
  }
  State(State &parent){
    this->parent = parent;
    someting = -1; //wrote whatever, just testing
  }
  ~State(){ //destructor
    free(this); // i dont even know if this actually will work
  }
};


/* player 1 is max player, player 0 is min player */
void alphaBeta(itn state, int depth, int alpha, int beta, int player){

  int i;
  int actionsLength=0;
  
  if(cutoffTes(state, depth))
    return (eval(state),null);

  best = null; /* Handles early pruning or no possible moves */
  if(player == 1){ //max player
    
    for(i=0; i < actionsLength; i++){

      (child, unused) = result(state, action);
      value = alphaBeta(child, depth+1, alpha, beta, 0);

      if(value > alpha){
        alpha = value;
        best = action;
      }
      if(beta <= alpha)
        break; /* beta cut-off */
    }
    
  }
  else{ //min player


  }
  
}

int main(){

  alphaBeta(arg1, arg2, arg3, arg4, arg5);
  
  return 1;
}

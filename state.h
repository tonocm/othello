int SIZE = 8;

class State{
public:
  enum Value { // Enum of possible states of a grid space
    WHITE = 1,
    BLACK = -1,
        FREE = 0
  };
	int move[2];
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

  State(int board[SIZE][SIZE]){
    for(int i = 0; i<SIZE; i++)
      for(int j = 0; j<SIZE; j++)
	_state[i][j] = board[i][j];
    parent = NULL;
    move[0] = move[1] = -1;
  }

  Value *operator[] (size_t idx) {
    return _state[idx];
  }
private:
  Value _state[SIZE][SIZE];
  State *parent;
};

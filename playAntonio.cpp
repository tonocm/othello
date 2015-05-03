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

void printboard(State& state, int player, int turn, int X, int Y)
{
    int i, j, num;
    num = 64;

    fprintf(stderr, "%2d. %c plays (%2d, %2d)\n", turn, (player==-1 ? 'B' : 'W'), X, Y);
    for(i = 0; i < SIZE; i ++) {
        for(j = 0; j < SIZE; j++){
            fprintf(stderr, "%4d", (int)state[i][j]);
            if((int)state[i][j]) num --;
        }
        printf("\n");
    }
    printf("number of blanks = %d\n", num);
}
/*
 * Goes in the given direction until it hits an edge, another piece belonging to the player, or a free space
 * If it hits another of the player's pieces, the pieces in between are flipped
 * Returns true if pieces were flipped, false otherwise
 */
bool flip (State& state, move _move, move dir, State::Value player) {
    bool flag;
  
    for (ssize_t i = _move.x + dir.x, j = _move.y + dir.y; i < SIZE && i >= 0 && j < SIZE && j >= 0; i += dir.x, j += dir.y) {
        if (state[i][j] == player) {
            flag = false;
            for (ssize_t k = _move.x + dir.x, l = _move.y + dir.y; k != i || l != j; k += dir.x, l += dir.y) {
                state[k][l] = player;
                flag = true;
            }
            return flag;
        }
        if (state[i][j] == State::Value::FREE)
            return false;
    }
    return false;
}

/*
 * Makes the specified move for the player
 * Calls flip in all directions
 * Returns true if pieces were flipped, false otherwise
 */
bool make_move (State& state, move _move, State::Value player) {
    bool flag = false;
  
    state[_move.x][_move.y] = player;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            flag |= flip(state, _move, move{.x = i, .y = j}, player);

    return flag;
}

/*
 * Sets up the default board
 */
void initBoard(State& board)
{
    for(int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            board[i][j] = State::Value::FREE;
    board[3][3] = State::Value::WHITE;
    board[4][4] = State::Value::WHITE;
    board[3][4] = State::Value::BLACK;
    board[4][3] = State::Value::BLACK;
    return;
}

/*
 * Reads a move from stdin
 * Returns true if it was able to read a valid move, false otherwise
 */
int readMove(struct move *opponent_move)
{
    char movebuf[10];
    std::cin.getline(movebuf, 10);
    if (!std::cin.good())
        return 0;
    if (strncmp(movebuf, "pass", 4)!=0)	
        return (sscanf(movebuf, "%d %d\n", &(opponent_move->y), &(opponent_move->x)));
    opponent_move->x = opponent_move->y = -1;
    return 1;
}

/*
 * Makes the move (x, y) for the player iplayer
 */
void updateState(int x, int y, int iplayer)
{
    State::Value player;
    if(iplayer == 1)
        player = State::WHITE;
    else
        player = State::BLACK;
  
    make_move(currentState, move{.x = x, .y = y}, player);
    return;
}

/*
 * Returns a collection of all possible successor states for the state with iplayer playing
 */
std::vector<State> actions (const State& state, int iplayer) {
    State::Value player;
    if(iplayer == 1)
        player = State::WHITE;
    else
        player = State::BLACK;

    std::vector<State> ret;
    // Build player1's move set
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            State next(&state, i, j);
            bool flag; // Have we flipped any pieces?
            if (next[i][j] == State::Value::FREE) {
                flag = make_move(next, move{.x = i, .y = j}, player);
                if (flag)
                    ret.push_back(std::move(next));
            }
        }
    }
    return ret;
}

/*
 * Returns 1 if time is up or the depth limit was reached
 */
int cutoffTest(int depth)
{
    clock_t now = clock();
    if (TIMELIMIT1 > 0 && (now - move_start) / (CLOCKS_PER_SEC/1000) >= TIMELIMIT1)
        return 1;
    if(TIMELIMIT2 > 0 && (now - game_start) / (CLOCKS_PER_SEC/1000) >=TIMELIMIT2)
        return 1;
    if (DEPTHLIMIT > 0 && depth>DEPTHLIMIT)
        return 1;
    return 0;
}

/*
 * Returns Max pieces - Min pieces
 */
int cost(State &state) {
    int cost = 0;
    for(int i = 0; i<SIZE; i++)
        for (int j = 0; j<SIZE; j++)
            cost+=state[i][j];
    return cost;
}

/*
 * Counts stable pieces (those which cannot be fliped)
 * Returns a pair (Min_stable_pieces, Max_stable_pieces)
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

/*
 * Takes a pair of coordinates for the move
 * When x is set to -1, a pass is done
 */
void makeMove(int x, int y)
{
    if (x == -1)
        printf("pass\n");
    else
        printf("%d %d\n", y, x);
}

/*
 * Alpha-Beta pruning Minimax function
 * player 1 is max player, player -1 is min player
 */
std::pair<int, move> alphaBeta(State &state, int depth, int limit, int alpha, int beta, int player)
{
    std::pair<int, move> best;
    int value;
    std::vector<State> successors;
    if (depth > limit) {
        std::pair<int, int> count = count_stable(state);
        return std::make_pair(count.second - count.first,  move{.x = state.move[0], .y = state.move[1]}); // Heuristic function, needs improvement
    }
    if(cutoffTest(depth)) { // This is broken
        // makeMove(best.second.x, best.second.y);
        return best;
    }

    successors = actions(state, player);
    if (successors.size() == 0) {
        // fprintf(stderr, "No successors\n");
        if (depth == 0)
            return std::make_pair(player == 1 ? alpha : beta,  move{.x = -1, .y = -1});
        else
            return alphaBeta(state, depth + 1, limit, alpha, beta, -player);
    }
    for(State& action : successors){ // This line requires C++11
        // This for loop could run in parallel (At least for the top one or two calls)
        // printboard(action, player, depth, action.move[0], action.move[1]);
        value = alphaBeta(action, depth + 1, limit, alpha, beta, -player).first;
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
            if(beta <= alpha) /* alpha cut-off */
                return std::make_pair(alpha, move{.x = state.move[0], .y = state.move[1]});
        }
    }
    return best;
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
            move m;
            player = -1;
            move_start = clock();
            m = alphaBeta(currentState, 0, 4, INT_MIN, INT_MAX, player).second; // Should do iterative deepening until out of time
            makeMove(m.x, m.y);
            updateState(m.x, m.y, player);
        }
    else
	player = 1;
    while (readMove(&enemy_move))
        {
            move m;
            // fprintf(stderr, "enemy move: %d %d\n", enemy_move.x, enemy_move.y);
            move_start = clock();
            updateState(enemy_move.x, enemy_move.y, -player);
            // printboard(currentState, player, 0, enemy_move.x, enemy_move.y);
            m = alphaBeta(currentState, 0, 4, INT_MIN, INT_MAX, player).second; // Should do iterative deepening until out of time
            makeMove(m.x, m.y);
            updateState(m.x, m.y, player);
        }
    return 0;
}

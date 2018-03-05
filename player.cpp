#include "player.hpp"

using namespace std;

#define BOARD_SIZE 8

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side s) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
     side = s;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    if (testingMinimax)
    {
        
        return minimax;
    }
    /* Process opponent's move. */
    board.doMove(opponentsMove, getOtherSide());
    /* Do the first valid move we find. */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Move move(i, j);
            if (board.checkMove(&move, side)) {
                board.doMove(&move, side);
                return new Move(i, j);
            }
        }
    }
    return nullptr;
}

Move * Player::minimax(Move * opponentsMove, int msLeft, Side side, int depth)
{
    //heuristic(move, side, board)
    std::vector<Move> moves;
    std::vector<int> hScores;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Move move(i, j);
            if (board.checkMove(&move, side)) {
                moves.push_back(move);
            }
        }
    }

    for (int i = 0;  i < moves.size(); i++)
    {
        hScores.append()
    }
}

void Player::switchBoard(Board * b){
    board = *b;
}
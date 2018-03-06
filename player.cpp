#include "player.hpp"
#include <vector>
#include <cassert>

using namespace std;

#define BOARD_SIZE 8
#define CORNER_BONUS 32
#define EDGE_BONUS 8

int Player::heuristic(Move move, Side s, Board b)
{
    assert(b.checkMove(&move, s));
    int total = 0;
    total += b.isEdge(move.getX(), move.getY()) * EDGE_BONUS;
    total += b.isCorner(move.getX(), move.getY()) * CORNER_BONUS;
    total -= b.count(s);
    b.doMove(&move, s);
    total += b.count(s);
    return total;
}

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
    

    /* Process opponent's move. */
    board.doMove(opponentsMove, getOtherSide());
    /* List all possible moves. */
    vector<Move> moves;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Move move(i, j);
            if (board.checkMove(&move, side))
            {
                moves.push_back(move);
            }
        }
    }

    /* Find best move by minimax. */
    if (testingMinimax)
    {
        int best = 0;
        for (unsigned int i = 0; i < moves.size(); i++)
        {
            if (minimax(board, msLeft, getOtherSide(), 2, moves[best]) 
                < minimax(board, msLeft, getOtherSide(), 2, moves[i]))
            {
                best = i;
            }
        }
        return new Move(moves[best]);
    }

    /* Find best move by heuristic. */
    int best = 0;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        if (heuristic(moves[best], side, board) 
            < heuristic(moves[i], side, board))
        {
            best = i;
        }
    }

    if (moves.size() > 0)
    {
        board.doMove(&moves[best], side);
        return new Move(moves[best]);
    }
    else
    {
        return nullptr;
    }
}

int Player::minimax(Board b, int msLeft, Side s, int depth, Move m)
{
    /* Process move in question. */
    b.doMove(&m, s);

    /* Find all possible moves. */
    vector<Move> moves;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Move move(i, j);
            if (b.checkMove(&move, side))
            {
                moves.push_back(move);
            }
        }
    }

    /* Base Case */
    if (depth == 1){
        int best = heuristic(moves[0], side, b);
        for (unsigned int i = 0; i < moves.size(); i++)
        {
            if ((heuristic(moves[i], side, b) 
                > best && side == s) || (heuristic(moves[i], side, b) 
                < best && side != s))
            {
                best = heuristic(moves[i], side, b);
            }
        }
        return best;
    }

    /* Find best move by minimax. */

    int best = heuristic(moves[0], side, b) + 
                    minimax(b, msLeft, otherSide(s), depth - 1, moves[0]);
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        int result = heuristic(moves[i], side, b) + 
                    minimax(b, msLeft, otherSide(s), depth - 1, moves[i]);
        if ((s == side && result > best) || (s != side && result < best)){
            best = result;
        }

    }
    return best;

}

void Player::switchBoard(Board * b){
    board = *b;
}
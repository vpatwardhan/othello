#include "player.hpp"
#include <vector>
#include <cassert>
#include <limits.h>

using namespace std;

#define BOARD_SIZE 8
#define CORNER_BONUS 40
#define EDGE_BONUS 8
#define WIN_VALUE 300
#define PASS_PENALTY 0

int Player::heuristic(Move move, Side s, Board b)
{
    assert(b.checkMove(&move, s));

    b.doMove(&move, s);
    int total = b.count(s) - b.count(otherSide(s));
    for (int i = 1; i < BOARD_SIZE-1; i++)
    {   
        //top row edges
        if (b.get(s,i,0))
        {
            total += EDGE_BONUS;
        }
        else if(b.get(otherSide(s),i, 0))
        {
            total -= EDGE_BONUS;
        }

        //bottom row edges
        if (b.get(s,i,BOARD_SIZE - 1))
        {
            total += EDGE_BONUS;
        }
        else if(b.get(otherSide(s),i, BOARD_SIZE-1))
        {
            total -= EDGE_BONUS;
        }

        //left column edges
        if (b.get(s, 0, i))
        {
            total += EDGE_BONUS;
        }
        else if(b.get(otherSide(s), 0, i))
        {
            total -= EDGE_BONUS;
        }

        //right column edges
        if (b.get(s,0,BOARD_SIZE-1))
        {
            total += EDGE_BONUS;
        }
        else if(b.get(otherSide(s),0, BOARD_SIZE-1))
        {
            total -= EDGE_BONUS;
        }
    }
    if (b.get(s, 0,0))
    {
        total += CORNER_BONUS;
    }
    else if (b.get(otherSide(s), 0,0))
    {
        total -= CORNER_BONUS;
    }

    if (b.get(s, 0,BOARD_SIZE - 1))
    {
        total += CORNER_BONUS;
    }
    else if (b.get(otherSide(s), 0,BOARD_SIZE - 1))
    {
        total -= CORNER_BONUS;
    }

    if (b.get(s, BOARD_SIZE - 1,0))
    {
        total += CORNER_BONUS;
    }
    else if (b.get(otherSide(s), BOARD_SIZE - 1,0))
    {
        total -= CORNER_BONUS;
    }
    if (b.get(s, BOARD_SIZE - 1,BOARD_SIZE - 1))
    {
        total += CORNER_BONUS;
    }
    else if (b.get(otherSide(s), BOARD_SIZE - 1,BOARD_SIZE - 1))
    {
        total -= CORNER_BONUS;
    }

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
    if (board.hasMoves(side) == 0)
    {
        return nullptr;
    }
    vector<Move> moves;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Move move = Move(i, j);
            if (board.checkMove(&move, side))
            {
                moves.push_back(move);
            }
        }
    }

    /* Find best move by minimax. */
    int best = 0;
    int bestScore = INT_MIN;
    for (unsigned int i = 0; i < moves.size(); i++)
    {
        int moveScore = minimax(board, msLeft, getOtherSide(), 4, moves[i],
            INT_MIN, INT_MAX);
        if (bestScore < moveScore)
        {
            best = i;
            bestScore = moveScore;
        }
    }


        board.doMove(&moves[best], side);
        return new Move(moves[best]);
}

int Player::minimax(Board b, int msLeft, Side s, int depth, Move m, int alpha, int beta)
{
    
    /* Process move in question. */
    b.doMove(&m, otherSide(s));
    /* Find all possible moves. */
    if (!b.hasMoves(s))
    {
        if (b.isDone())
        {
            if (b.count(side) > b.count(getOtherSide()))
            {
                return WIN_VALUE;
            }
            return -WIN_VALUE;
        }
        return PASS_PENALTY;
    }

    vector<Move> moves;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Move move(i, j);
            if (b.checkMove(&move, s))
            {
                moves.push_back(move);
            }
        }
    }

    /* Base Case */
    if (depth == 1){
        int best = INT_MIN;
        if (side != s)
        {
            best = INT_MAX;
            for (unsigned int i = 0; i < moves.size(); i++)
            {
                
                int result = heuristic(moves[i], side, b);
                if (result < best)
                {
                    best = result;
                }
            }
            return best;
        }
        else
        {
            for (unsigned int i = 0; i < moves.size(); i++)
            {
                
                int result = heuristic(moves[i], side, b);
                if (result > best)
                {
                    best = result;
                }
            }
            return best;
        }
    }

    /* Find best move by minimax. */

    int best = minimax(b, msLeft, otherSide(s), depth - 1, moves[0],
        alpha, beta);
    if (s == side)
    {
        for (unsigned int i = 0; i < moves.size(); i++)
        {
            int result = minimax(b, msLeft, otherSide(s), depth - 1, moves[i],
                alpha, beta);
            if (result > best)
            {
                best = result;
            }
            if (alpha < best)
            {
                alpha = best;
            }
            if (beta <= alpha)
            {
                break;
            }

        }
        return best;
    }
    else
    {
        for (unsigned int i = 0; i < moves.size(); i++)
        {
            int result = minimax(b, msLeft, otherSide(s), depth - 1, moves[i],
                alpha, beta);
            if (result < best){
                best = result;
            }
            if (beta < best)
            {
                beta = best;
            }
            if (beta <= alpha)
            {
                break;
            }
        }
        return best;
    }

}

void Player::switchBoard(Board * b){
    board = *b;
}
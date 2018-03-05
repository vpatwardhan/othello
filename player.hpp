#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {
    Side side;
    Board board;

    /* Get the color of the opposite side. */
    inline Side getOtherSide() {
        return (Side)((int)(!(bool)(int)side));
    }

    /* Return how good a move is based on access to the corner and edge. */
    static int heuristic(Move move, Side s, Board b);

public:
    Player(Side side);
    ~Player();

    Move * Player::minimax(Board b, int msLeft, Side s, int depth);
    void switchBoard(Board * b);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Move * minimax(Move * opponentsMove, int msLeft, Side side);
    
};

#endif

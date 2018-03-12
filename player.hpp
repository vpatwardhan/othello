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
    static inline Side otherSide(Side side) {
        return (Side)((int)(!(bool)(int)side));
    }

    inline Side getOtherSide() {
        return otherSide(side);
    }

    /* Return how good a move is based on access to the corner and edge. */
    int heuristic(Move move, Side s, Board b);

public:
    Player(Side side);
    ~Player();

    Move * doMove(Move *opponentsMove, int msLeft);
    void switchBoard(Board * b);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    int minimax(Board b, int msLeft, Side s, int depth, Move m);
    
};

#endif

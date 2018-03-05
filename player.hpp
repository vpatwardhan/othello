#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {
    Side side;
    Board board;

    inline Side getOtherSide() {
        return (Side)((int)(!(bool)(int)side));
    }

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    void switchBoard(Board * b);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;

private:
    Move * minimax(Move * opponentsMove, int msLeft, Side side);
    
};

#endif

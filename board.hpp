#ifndef __BOARD_H__
#define __BOARD_H__

#include <bitset>
#include "common.hpp"
using namespace std;

class Board {

private:
    bitset<64> black;
    bitset<64> taken;

    bool occupied(int x, int y);
    
    void set(Side side, int x, int y);
    bool onBoard(int x, int y);

public:
    Board();
    ~Board();
    Board *copy();
    bool get(Side side, int x, int y);
    bool isDone();
    bool hasMoves(Side side);
    bool checkMove(Move *m, Side side);
    void doMove(Move *m, Side side);
    int count(Side side);
    int countBlack();
    int countWhite();

    inline bool isCorner(int x, int y)
    {
        return (x == 0 || x == 8) && (y == 0 || y == 8);
    }

    inline bool isEdge(int x, int y)
    {
        return (x == 0 || x == 8) || (y == 0 || y == 8);
    }

    void setBoard(char data[]);
};

#endif

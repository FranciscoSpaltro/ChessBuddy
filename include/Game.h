#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "piece.h"
#include "movement.h"

class Game {
private:
    Board board;
    PieceColor currentPlayer;

public:
    Game();
    bool play(const movement& m);
    void print() const;
    #ifdef TEST_MODE
        Board& getBoard() { return board; }
        const Board& getBoard() const { return board; }
    #endif
};


#endif
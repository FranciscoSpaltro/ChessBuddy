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
};


#endif
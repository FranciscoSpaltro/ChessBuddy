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
    const Board& getBoard() const { return board; } // TO CHANGE!
    Board& getBoard() { return board; }             // TO CHANGE!
    PieceColor getCurrentPlayer(void) const;

};


#endif
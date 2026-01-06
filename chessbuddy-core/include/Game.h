#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "piece.h"
#include "movement.h"

enum class GameResult {
    Ok,
    InvalidMove,
    WrongPlayer,
    CheckMate,
    StaleMate,
    Init,
    None
};

struct GameStatus {
    GameResult gr = GameResult::Init;
    MoveResult mr = MoveResult::None;
    int turnNumber = 0;
};

class Game {
private:
    Board board;
    PieceColor currentPlayer;
    GameStatus gameStatus;

public:
    Game();
    bool play(const movement& m);
    void print() const;
    const Board& getBoard() const { return board; } // TO CHANGE!
    Board& getBoard() { return board; }             // TO CHANGE!
    PieceColor getCurrentPlayer(void) const;
    std::string getGameMessage(void) const;
    int getTurnNumber(void) const;
    bool checkOrigin(const Position& pos);
};


#endif
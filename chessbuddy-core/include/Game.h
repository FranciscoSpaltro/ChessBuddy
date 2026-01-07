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
};

struct PromotionStatus {
    bool mode = false;
    PieceColor color;
};

class Game {
private:
    Board board;
    PieceColor currentPlayer;
    GameStatus gameStatus;
    PromotionStatus promotionStatus;
    int turnNumber = 0;

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
    bool isPromotionRequested(void);
    void makePromotion(PieceType piece);
    PieceColor getPromotionColor(void);
    bool isKingInCheck(void);
    bool isCheckMate(void);
    bool isStaleMate(void);
};


#endif
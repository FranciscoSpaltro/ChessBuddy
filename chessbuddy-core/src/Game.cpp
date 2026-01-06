#include "Game.h"

Game::Game(void) : currentPlayer(PieceColor::white) {}

bool Game::play(const movement& m){
    const Piece* p = board.getPiece(m.fromRow, m.fromColumn);
    if (!p){
        gameStatus = {GameResult::InvalidMove, MoveResult::EmptyOrigin}; // no hay pieza
        return false;
    }                 
        
    if(p->getColor() != currentPlayer){
        gameStatus = {GameResult::WrongPlayer, MoveResult::None};
        return false;
    }
        
    MoveResult mr = this -> board.move(m); 
    if(mr != MoveResult::Ok){
        gameStatus = {GameResult::InvalidMove, mr};
        return false;
    }

    this -> currentPlayer = (this -> currentPlayer == PieceColor::white ? PieceColor::black : PieceColor::white);

    gameStatus = {GameResult::Ok, MoveResult::Ok};
    gameStatus.turnNumber ++;

    return true;
}

PieceColor Game::getCurrentPlayer(void) const{
    return currentPlayer;
}

void Game::print() const {
    board.printBoard();
}

int Game::getTurnNumber(void) const{
    return gameStatus.turnNumber;    
}

std::string Game::getGameMessage(void) const{
    switch(gameStatus.gr){
        case GameResult::Ok:
            return "PLAY!";

        case GameResult::WrongPlayer:
            return "WRONG PLAYER!";

        case GameResult::CheckMate:
            return "CHECK MATE! - Game Finished";

        case GameResult::StaleMate:
            return "STALE MATE! - Game Finished";

        case GameResult::InvalidMove:{
            switch (gameStatus.mr){
                case MoveResult::EmptyOrigin:
                    return "SELECT A VALID PIECE!";

                case MoveResult::LeavesOnCheck:
                    return "YOUR KING WOULD BE IN CHECK!";
                    
                case MoveResult::InvalidMovement:
                    return "INVALID MOVEMENT!";

                default:
                    return "UNRECOGN. STATUS";
            }
        }

        case GameResult::Init:
            return "GOOD LUCK!";

        default:
            return "UNRECOGN. STATUS";
    }
        
}

bool Game::checkOrigin(const Position& pos){
    const Piece * p = board.getPiece(pos.row, pos.col);
    if(!p){
        gameStatus = {GameResult::InvalidMove, MoveResult::EmptyOrigin};
        return false;
    }

    if(p->getColor() != currentPlayer){
        gameStatus =  {GameResult::WrongPlayer, MoveResult::None};
        return false;
    }

    return true;
}
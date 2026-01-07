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
    
    if(mr == MoveResult::PromotionRequested){
        promotionStatus.color = currentPlayer;
        promotionStatus.mode = true;
        gameStatus = {GameResult::Ok, mr};
        this -> currentPlayer = (this -> currentPlayer == PieceColor::white ? PieceColor::black : PieceColor::white);
        turnNumber ++;
        return true;
    }
    else if(mr != MoveResult::Ok){
        gameStatus = {GameResult::InvalidMove, mr};
        return false;
    }

    this -> currentPlayer = (this -> currentPlayer == PieceColor::white ? PieceColor::black : PieceColor::white);

    if(board.isKingInCheck(currentPlayer)){
        gameStatus = {GameResult::Ok, MoveResult::KingInCheck};
    } else if(board.isCheckMate(currentPlayer)){
        gameStatus = {GameResult::CheckMate, MoveResult::None};
    } else if(board.isStalemate(currentPlayer)){
        gameStatus = {GameResult::StaleMate, MoveResult::None};
    } else {
        gameStatus = {GameResult::Ok, MoveResult::Ok};
    }

    turnNumber ++;

    return true;
}

bool Game::isKingInCheck(void){
    return gameStatus.gr == GameResult::Ok && gameStatus.mr == MoveResult::KingInCheck;
}

bool Game::isCheckMate(void){
    return gameStatus.gr == GameResult::CheckMate;
}

bool Game::isStaleMate(void){
    return gameStatus.gr == GameResult::StaleMate;
}

PieceColor Game::getCurrentPlayer(void) const{
    return currentPlayer;
}

void Game::print() const {
    board.printBoard();
}

int Game::getTurnNumber(void) const{
    return turnNumber;    
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

bool Game::isPromotionRequested(void){
    return promotionStatus.mode;
}

PieceColor Game::getPromotionColor(void){
    return promotionStatus.color;
}

void Game::makePromotion(PieceType chosenPiece){
    board.makePromotion(chosenPiece);
    promotionStatus.mode = false;
}

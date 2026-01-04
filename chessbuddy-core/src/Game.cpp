#include "Game.h"

Game::Game(void) : currentPlayer(PieceColor::white) {}

bool Game::play(const movement& m){
    const Piece* p = board.getPiece(m.fromRow, m.fromColumn);
    if (!p) return false;                 // no hay pieza
        
    if(p->getColor() != currentPlayer)
        return false;
        
    if(!(this -> board.move(m)))
        return false;

    this -> currentPlayer = (this -> currentPlayer == PieceColor::white ? PieceColor::black : PieceColor::white);
    return true;
}

void Game::print() const {
    this -> board.printBoard();
}


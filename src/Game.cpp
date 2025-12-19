#include "Game.h"

Game::Game(void) : currentPlayer(pieceColor::white) {}

bool Game::play(const movement& m){
    if(this -> board.getPiece(m.fromRow, m.fromColumn)->getColor() != currentPlayer)
        return false;
        
    if(!(this -> board.move(m)))
        return false;

    this -> currentPlayer = (this -> currentPlayer == pieceColor::white ? pieceColor::black : pieceColor::white);
    return true;
}

void Game::print() const {
    this -> board.printBoard();
}

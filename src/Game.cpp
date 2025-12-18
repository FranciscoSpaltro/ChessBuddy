#include "Game.h"

Game::Game(void) : currentPlayer(pieceColor::white) {}

bool Game::play(const movement& m){
    if(!(this -> board.move(m, this -> currentPlayer)))
        return false;

    this -> currentPlayer = (this -> currentPlayer == pieceColor::white ? pieceColor::black : pieceColor::white);
    return true;
}

void Game::print() const {
    this -> board.printBoard();
}

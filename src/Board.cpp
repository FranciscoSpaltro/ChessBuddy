#include "Board.h"
#include <iostream>

bool Board::checkEmpty(int row, int column) const{
    if (this -> board[index(row, column)].piece != pieceType::none)
        return false;
    return true;
}

int Board::index(int row, int column) const {
return row * 8 + column;
}

void Board::initialize(void){
    for(int i = 0; i < 8; i++){         // rows
        for(int j = 0; j < 8; j++){     // columns
            this -> board[index(i, j)] = {pieceType::none, pieceColor::none};
        }
    }

    this -> board[index(0, 0)] = {pieceType::rook, pieceColor::black};
    this -> board[index(0, 1)] = {pieceType::knight, pieceColor::black};
    this -> board[index(0, 2)] = {pieceType::bishop, pieceColor::black};
    this -> board[index(0, 3)] = {pieceType::queen, pieceColor::black};
    this -> board[index(0, 4)] = {pieceType::king, pieceColor::black};
    this -> board[index(0, 5)] = {pieceType::bishop, pieceColor::black};
    this -> board[index(0, 6)] = {pieceType::knight, pieceColor::black};
    this -> board[index(0, 7)] = {pieceType::rook, pieceColor::black};
    this -> board[index(1, 0)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 1)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 2)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 3)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 4)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 5)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 6)] = {pieceType::pawn, pieceColor::black};
    this -> board[index(1, 7)] = {pieceType::pawn, pieceColor::black};

    this -> board[index(6, 0)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 1)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 2)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 3)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 4)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 5)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 6)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(6, 7)] = {pieceType::pawn, pieceColor::white};
    this -> board[index(7, 0)] = {pieceType::rook, pieceColor::white};
    this -> board[index(7, 1)] = {pieceType::knight, pieceColor::white};
    this -> board[index(7, 2)] = {pieceType::bishop, pieceColor::white};
    this -> board[index(7, 3)] = {pieceType::king, pieceColor::white};
    this -> board[index(7, 4)] = {pieceType::queen, pieceColor::white};
    this -> board[index(7, 5)] = {pieceType::bishop, pieceColor::white};
    this -> board[index(7, 6)] = {pieceType::knight, pieceColor::white};
    this -> board[index(7, 7)] = {pieceType::rook, pieceColor::white};
}

Board::Board(void) {
    initialize();
};

piece Board::whatIsIn(int row, int column){
    return this -> board[index(row, column)];
}

bool Board::move(const movement& m, pieceColor player){
    if(!isValidMove(m, player)){
        return false;
    }

    this -> board[index(m.toRow, m.toColumn)] = this -> board[index(m.fromRow, m.fromColumn)];
    this -> board[index(m.fromRow, m.fromColumn)] = {pieceType::none, pieceColor::none};

    return true;
}

void Board::printBoard(void) const{
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            piece p = board[index(i, j)];

            std::cout << pieceNames[
                static_cast<int>(p.color)       // Convierte explicitamente el enum en int
            ][
                static_cast<int>(p.piece)
            ];

            if(j != 7)
                std::cout << " | ";
            else
                std::cout << std::endl;
        }
        std::cout << "---------------------------------------" << std::endl;
    }
}

bool Board::isValidMove(const movement& m, pieceColor player) const {
    // verifico origen vacio
    if(checkEmpty(m.fromRow, m.fromColumn))
        return false;

    piece p = this -> board[index(m.fromRow, m.fromColumn)];

    // verifico origen valido
    if(p.color != player)
        return false;
    
    // verifico destino vacio o pieza de otro color
    //if(this -> board[index(m.toRow, m.toColumn)].piece != pieceType::none || this -> board[index(m.toRow, m.toColumn)].color == p.color)
    //    return false;

    // verifico por pieza: movimiento hacia adelante + regla de la pieza
    // AGREGAR EXCEPCIÓN PRIMER MOVIMIENTO
    int dir = (player == pieceColor::black) ? +1 : -1;
    int deltaRow = m.toRow - m.fromRow;
    int deltaCol = m.toColumn - m.fromColumn;

    switch(p.piece){
        case pieceType::pawn:
            if(deltaRow != dir)                         // Avanza en sentido contrario
                return false;

            if(deltaCol == 0){                          // MOVIMIENTO DE AVANCE
                if(!checkEmpty(m.toRow, m.toColumn))    // Intenta avanzar a un lugar ocupado
                    return false;

                return true;
            
            } else if(abs(deltaCol) == 1){                                  // MOVIMIENTO DE CAPTURA
                if(checkEmpty(m.toRow, m.toColumn))                         // Captura en lugar vacio
                    return false;                                   
                if(board[index(m.toRow, m.toColumn)].color == player)       // Captura pieza propia
                    return false;

                return true;
            }

            return false;

    }

    return false;

}
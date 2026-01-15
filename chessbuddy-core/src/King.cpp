#include "King.h"
#include <stdlib.h>

King::King(PieceColor color) : Piece(color) {
    type = PieceType::King;
}

bool King::isValidMove(const Board& /*board*/, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza
    // La validacion de si el rey queda en jaque la hace Game
    // Tampoco implemento enroque aca

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(deltaRow == 0 && abs(deltaCol) == 2)     // Posible enroque
        return true;

    if (std::max(abs(deltaRow), abs(deltaCol)) != 1)
        return false;

    return true;
}

char King::symbol() const {
    return (getColor() == PieceColor::white) ? 'K' : 'k';
}

bool King::canJump() const {
    return false;
}

SpecialMove King::getSpecialMove(const movement& m) const {
    // ENROQUE: aun no se ha movido y se desplaza desde el origen 2 columnas de distancia en la misma fila
    if(hasMoved())
        return SpecialMove::None;

    if(m.fromRow == m.toRow && abs(m.toColumn - m.fromColumn) == 2)
        return SpecialMove::Castling;
    
    return SpecialMove::None;
}

std::vector<movement> King::pseudoLegalMoves(int r, int c, const Board& board) const {
    std::vector<movement> moves;
    PieceColor color = this->getColor();

    // combinacion rook + bishop
    static const int dirs[8][2] = {
        {0, +1},
        {0, -1},
        {+1, 0},
        {-1, 0},
        {+1, +1},
        {-1, -1},
        {+1, -1},
        {-1, +1}
    };

    for (const auto& d : dirs) {
        int nr = r + d[0];
        int nc = c + d[1];

        if (nr < 0 || nr > 7 || nc < 0 || nc > 7) continue;

        // si hay aliada, no
        if (!board.checkEmpty(nr, nc) && !board.isEnemyAt(nr, nc, color)) continue;

        // vacío o enemigo
        moves.push_back(movement{r, c, nr, nc});
    }

    // Castling (sin chequear ataques)
    if (!this->hasMoved()) {
        int homeRow = (color == PieceColor::white) ? 7 : 0;
        if (r == homeRow && c == 4) {
            // King side: rook en col 7, rey va a col 6
            {
                const Piece* rook = board.getPiece(homeRow, 7);
                if (rook && rook->getType() == PieceType::Rook && rook->getColor() == color && !rook->hasMoved()) {
                    // casillas entre rey y rook vacías (5 y 6)
                    if (board.checkEmpty(homeRow, 5) && board.checkEmpty(homeRow, 6)) {
                        moves.push_back(movement{r, c, homeRow, 6});
                    }
                }
            }

            // Queen side: rook en col 0, rey va a col 2
            {
                const Piece* rook = board.getPiece(homeRow, 0);
                if (rook && rook->getType() == PieceType::Rook && rook->getColor() == color && !rook->hasMoved()) {
                    // casillas entre rey y rook vacías (3,2,1)
                    if (board.checkEmpty(homeRow, 3) && board.checkEmpty(homeRow, 2) && board.checkEmpty(homeRow, 1)) {
                        moves.push_back(movement{r, c, homeRow, 2});
                    }
                }
            }
        }
    }

    return moves;
}
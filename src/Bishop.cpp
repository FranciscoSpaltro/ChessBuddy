#include "Bishop.h"
#include <stdlib.h>

Bishop::Bishop(PieceColor color) : Piece(color) {
    type = PieceType::Bishop;
}

bool Bishop::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(abs(deltaRow) != abs(deltaCol))  // Movimiento no diagonal
        return false;

    return true;
}

char Bishop::symbol() const {
    return (getColor() == PieceColor::white) ? 'B' : 'b';
}

bool Bishop::canJump() const {
    return false;
}

std::vector<movement> Bishop::pseudoLegalMoves(int r, int c, const Board& board) const {
    std::vector<movement> moves;
    PieceColor color = this->getColor();

    // Se mueve en todas las casillas diagonales hasta un obstaculo: si es el fin del tablero o una pieza enemiga, lo incluye; si es pieza propia, no
    static const int dirs[4][2] = {
        {+1, +1},
        {+1, -1},
        {-1, +1},
        {-1, -1}
    };

    for (const auto& d : dirs) {
        int dr = d[0];
        int dc = d[1];

        int i = r + dr;
        int j = c + dc;

        while (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
            if (board.checkEmpty(i, j)) {
                moves.push_back(movement{r, c, i, j});
            } else {
                if (board.isEnemyAt(i, j, color))
                    moves.push_back(movement{r, c, i, j});
                break; // choca con algo (enemigo o aliado)
            }

            i += dr;
            j += dc;
        }
    }

    return moves;
}

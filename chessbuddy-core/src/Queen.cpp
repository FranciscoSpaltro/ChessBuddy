#include "Queen.h"
#include <stdlib.h>

Queen::Queen(PieceColor color) : Piece(color) {
    type = PieceType::Queen;
}

bool Queen::isValidMove(const Board& /*board*/, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if((abs(deltaRow) != abs(deltaCol)) && (deltaRow != 0 && deltaCol != 0))  // Movimiento no puramente diagonal o puramente recto
        return false;

    return true;
}

char Queen::symbol() const {
    return (getColor() == PieceColor::white) ? 'Q' : 'q';
}

bool Queen::canJump() const {
    return false;
}

std::vector<movement> Queen::pseudoLegalMoves(int r, int c, const Board& board) const {
    std::vector<movement> moves;
    PieceColor color = this->getColor();

    // combinacion rook + bishop
    static const int dirs[8][2] = {
        {+1, +1},
        {+1, -1},
        {-1, +1},
        {-1, -1},
        {0, +1},
        {0, -1},
        {+1, 0},
        {-1, 0}
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
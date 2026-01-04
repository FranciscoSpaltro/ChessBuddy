#include "Knight.h"
#include <stdlib.h>

Knight::Knight(PieceColor color) : Piece(color) {
    type = PieceType::Knight;
}

bool Knight::isValidMove(const Board& board, const movement& move) const {
    // Las validaciones de vacio origen no corresponde a la pieza

    int deltaRow = move.toRow - move.fromRow;
    int deltaCol = move.toColumn - move.fromColumn;

    if(!((abs(deltaRow) == 2 && abs(deltaCol) == 1) || (abs(deltaRow) == 1 && abs(deltaCol) == 2)))  // Movimiento no caballo
        return false;

    return true;
}

char Knight::symbol() const {
    return (getColor() == PieceColor::white) ? 'N' : 'n';
}

bool Knight::canJump() const {
    return true;
}

std::vector<movement> Knight::pseudoLegalMoves(int r, int c, const Board& board) const {
    std::vector<movement> moves;
    PieceColor color = this->getColor();
    
    // 8 saltos del caballo
    static const int dr[8] = {-2, -2, -1, -1, +1, +1, +2, +2};
    static const int dc[8] = {-1, +1, -2, +2, -2, +2, -1, +1};

    for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // 1) fuera de tablero -> no
        if (nc > 7 || nc < 0 || nr > 7 || nr < 0) continue;

        // 2) si hay una pieza aliada -> no
        const Piece* target = board.getPiece(nr, nc);
        if (target && target->getColor() == color) continue;

        // 3) vacío o enemigo -> sí (captura incluida)
        moves.push_back(movement{r, c, nr, nc});
    }

    return moves;
}
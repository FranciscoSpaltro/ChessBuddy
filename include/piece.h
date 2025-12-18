#ifndef PIECE_H
#define PIECE_H

static const char* pieceNames[3][7] = {
    /* none  */ { "  ", "  ", "  ", "  ", "  ", "  ", "  " },
    /* black */ { "  ", "k ", "q ", "b ", "n ", "r ", "p " },
    /* white */ { "  ", "K ", "Q ", "B ", "N ", "R ", "P " }
};

enum class pieceType {
    none,
    king,       // rey 
    queen,      // reina 
    bishop,     // alfil
    knight,     // caballo
    rook,       // torre
    pawn        // peon
};

enum class pieceColor {
    none,
    black,
    white
};


typedef struct {
    pieceType piece;
    pieceColor color;
} piece;


#endif // PIECE_H
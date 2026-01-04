#ifndef MOVE_H
#define MOVE_H

struct movement {
    int fromRow;
    int fromColumn;
    int toRow;
    int toColumn;
};

inline bool operator==(const movement& a, const movement& b) {
    return a.fromRow == b.fromRow &&
           a.fromColumn == b.fromColumn &&
           a.toRow == b.toRow &&
           a.toColumn == b.toColumn;
}

#endif
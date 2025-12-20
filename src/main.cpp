#include <iostream>
#include "Game.h"

int main() {
    Game game;
    /*
    while (true) {
        game.print();

        std::cout << "\nMovimiento (fromRow fromCol toRow toCol), o -1 para salir:\n> ";

        int fr;
        std::cin >> fr;
        if (!std::cin || fr == -1)
            break;

        int fc, tr, tc;
        std::cin >> fc >> tr >> tc;

        movement m { fr, fc, tr, tc };

        if (!game.play(m)) {
            std::cout << "Movimiento invalido\n";
        }
    }
    */
    /* ENROQUE
    movement m1 {7, 6, 5, 7};
    movement m2 {1, 0, 2, 0};
    movement m3 {6, 6, 5, 6};
    movement m4 {2, 0, 3, 0};
    movement m5 {7, 5, 6, 6};
    movement m6 {3, 0, 4, 0};
    movement m7 {7, 4, 7, 6};
    game.play(m1);
    game.play(m2);
    game.play(m3);
    game.play(m4);
    game.play(m5);
    game.play(m6);
    game.play(m7);
    game.print();
    */

movement m1 {6, 0, 5, 0};
movement m2 {1, 1, 2, 1};

movement m3 {5, 0, 4, 0};
movement m4 {2, 1, 3, 1};

movement m5 {4, 0, 3, 1};
movement m6 {1, 7, 2, 7};

movement m7 {3, 1, 2, 1};
movement m8 {2, 7, 3, 7};

movement m9 {2, 1, 1, 1};
movement m10{0, 1, 2, 2};

movement m11{1, 1, 0, 1}; // ← promoción
    game.play(m1);
    game.play(m2);
    game.play(m3);
    game.play(m4);
    game.play(m5);
    game.play(m6);
    game.play(m7);
    game.play(m8);
    game.play(m9);
    game.play(m10);
    game.play(m11);

    game.print();

    return 0;
}
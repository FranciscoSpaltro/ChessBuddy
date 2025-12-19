#include <iostream>
#include "Game.h"

int main() {
    Game game;

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

    return 0;
}
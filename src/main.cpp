#include <iostream>
#include "Game.h"

int main(void){
    Game game;
    //game.print();

    movement movimiento1 = {6,1,5,1};
    game.play(movimiento1);
    //std::cout << std::endl << "NUEVO" << std::endl;
    game.print();
    movement movimiento2 = {1,1,2,1};
    std::cout << std::endl << std::endl << std::endl;
    game.play(movimiento2);
    game.print();
}
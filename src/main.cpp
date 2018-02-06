#include <stdio.h>

#include "../../RattletrapEngine/include/Game.h"
#include "../include/StageState.h"
#ifndef GAME_WIDTH
    #define GAME_WIDTH 1024
    #define GAME_HEIGTH 600
#endif // GAME_WIDTH
int main(int argc, char** argv){
    Game novoJogo("Jogo teste", GAME_WIDTH, GAME_HEIGTH);
    novoJogo.Push(new StageState());
    novoJogo.Run();
    return 0;
}

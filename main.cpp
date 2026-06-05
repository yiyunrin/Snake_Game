#include "raylib.h"
#include "Config.h"
#include "Game.h"

int main(){
    InitWindow(Config::screenWidth, Config::screenHeight, "Snake Game");
    SetTargetFPS(60);

    Game game;
    game.Run();

    CloseWindow();
    return 0;
}
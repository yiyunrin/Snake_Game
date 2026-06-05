#pragma once
#include "raylib.h"
#include "Config.h"
#include "Player.h"
#include "Obstacle.h"
#include "InputManager.h"

enum class GameState{
    MENU,
    PLAYING,
    GAMEOVER
};

class Game{
private:
    GameState currentState;
    Player player;
    Obstacle obstacle;
    int maxScore = 0;
    int score = 0;
    int frameCnt;
    float speed;

    void UpdateMenu();
    void UpdatePlaying();
    void UpdateGameOver();

    void DrawMenu();
    void DrawPlaying();
    void DrawBackground();
    void DrawGameOver();

    bool CheckEat(std::vector<std::vector<bool>> grid, Vector2 pos);
public:
    Game(): currentState(GameState::MENU), score(0), maxScore(0){}
    ~Game() = default;

    void Run(){
        while (!WindowShouldClose()){
            switch (currentState){
                case GameState::MENU:
                    UpdateMenu();
                    break;
                case GameState::PLAYING:
                    UpdatePlaying();
                    break;
                case GameState::GAMEOVER:
                    UpdateGameOver();
                    break;
                default:
                    break;
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            switch (currentState){
                case GameState::MENU:
                    DrawMenu();
                    break;
                case GameState::PLAYING:
                    DrawPlaying();
                    break;
                case GameState::GAMEOVER:
                    DrawGameOver();
                    break;
                default:
                    break;
            }
            EndDrawing();
        }
        
    }
};

void Game::UpdateMenu(){
    if(InputManager::IsActionPressed(GameAction::RESTART)) {
        currentState = GameState::PLAYING;
        score = 0;
        frameCnt = 0;
        speed = Config::initialSpeed;
        player.Reset();
        obstacle.Reset();
    }
}

void Game::UpdatePlaying(){
    player.HandleInput();
    frameCnt += 1;
    if(frameCnt < speed){
        return;
    }
    frameCnt = 0;
    if(!player.AddHead()){
        currentState = GameState::GAMEOVER;
        return;
    }
    if(!CheckEat(player.GetGrid(), obstacle.GetPos())){
        player.DeleteTail();
    }
    else{
        speed *= 0.98;
        score += 10;
        while(CheckEat(player.GetGrid(), obstacle.GetPos())){
            obstacle.Update();
        }
    }
}

void Game::UpdateGameOver(){
    if(InputManager::IsActionPressed(GameAction::RESTART)){
        currentState = GameState::PLAYING;
        score = 0;
        speed = Config::initialSpeed;
        frameCnt = 0;
        player.Reset();
        obstacle.Reset();
    }
}

void Game::DrawMenu(){
    int titleWidth = MeasureText("Snake Game", 40);
    DrawText("Snake Game", (Config::screenWidth - titleWidth) / 2, Config::screenHeight / 2 - 40, 40, DARKGRAY);
    int startWidth = MeasureText("Press SPACE to Start", 20);
    DrawText("Press SPACE to Start", (Config::screenWidth - startWidth) / 2, Config::screenHeight / 2 + 20, 20, LIGHTGRAY);
}

void Game::DrawBackground() {
    int totalGridWidth = Config::gridWidth * Config::gridSize;
    int totalGridHeight = Config::gridHeight * Config::gridSize;

    int startX = (Config::screenWidth - totalGridWidth) / 2;
    int startY = Config::screenHeight - 25 - totalGridHeight;

    DrawRectangle(startX, startY, totalGridWidth, totalGridHeight, RAYWHITE);

    for (int i = 0; i <= Config::gridWidth; i++) {
        int lineX = startX + i * Config::gridSize;
        DrawLine(lineX, startY, lineX, startY + totalGridHeight, LIGHTGRAY);
    }
    for (int i = 0; i <= Config::gridHeight; i++) {
        int lineY = startY + i * Config::gridSize;
        DrawLine(startX, lineY, startX + totalGridWidth, lineY, LIGHTGRAY);
    }

    DrawRectangleLines(startX, startY, totalGridWidth, totalGridHeight, DARKGRAY);
}

void Game::DrawPlaying(){
    DrawBackground();
    player.Draw();
    obstacle.Draw();
    DrawText(TextFormat("Max Score: %d", maxScore), 20, 20, 20, LIGHTGRAY);
    DrawText(TextFormat("Score: %d", score), Config::screenWidth * 0.7, 20, 20, LIGHTGRAY);
}

void Game::DrawGameOver(){
    DrawPlaying();
    
    int overWidth = MeasureText(Config::overText, Config::overSize);
    int overX = (Config::screenWidth - overWidth) / 2;
    int overY = Config::screenHeight / 2 - 60;
    DrawText(Config::overText, overX, overY, Config::overSize, RED);

    const char* finalScoreText = TextFormat("Score: %d", score);
    int finalScoreSize = 30;
    int finalScoreWidth = MeasureText(finalScoreText, finalScoreSize);
    int finalScoreX = (Config::screenWidth - finalScoreWidth) / 2;
    int finalScoreY = Config::screenHeight / 2 - 10; 
    DrawText(finalScoreText, finalScoreX, finalScoreY, finalScoreSize, DARKGRAY);

    int restartWidth = MeasureText(Config::restartText, Config::restartSize);
    int restartX = (Config::screenWidth - restartWidth) / 2;
    int restartY = Config::screenHeight / 2 + 30;
    DrawText(Config::restartText, restartX, restartY, Config::restartSize, DARKGRAY);
}

bool Game::CheckEat(std::vector<std::vector<bool>> grid, Vector2 pos){
    return grid[pos.x][pos.y];
}
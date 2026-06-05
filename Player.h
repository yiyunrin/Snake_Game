#pragma once
#include "raylib.h"
#include "Config.h"
#include "InputManager.h"
#include "queue"
#include "vector"

class Player{
private:
    std::queue<Vector2> snake;
    std::vector<std::vector<bool>> grid;
    int dir;
    int now_dir;
    Vector2 head;

    void ResetSnake(){
        for(int i = 2;i >= 0;i --){
            Vector2 now = {Config::startPos.x, Config::startPos.y + i};
            snake.push(now);
            grid[now.x][now.y] = true;
        }
        head = {Config::startPos.x, Config::startPos.y};
    }
    bool IsOut(int x, int y){
        if(x < 0 || x >= Config::gridWidth)
            return true;
        if(y < 0 || y >= Config::gridHeight)
            return true;
        return false;
    }
public:
    Player(){
        Reset();
    }
    ~Player() {
        
    }
    void Update(){

    }
    bool AddHead(){
        now_dir = dir;
        Vector2 next = {head.x + Config::direction[dir].x, head.y + Config::direction[dir].y};
        snake.push(next);
        if(IsOut(next.x, next.y) || grid[next.x][next.y])
            return false;
        head = next;
        grid[next.x][next.y] = true;
        return true;
    }
    void DeleteTail(){
        Vector2 tail = snake.front();
        snake.pop();
        grid[tail.x][tail.y] = false;
    }
    void Draw(){
        int totalGridWidth = Config::gridWidth * Config::gridSize;
        int totalGridHeight = Config::gridHeight * Config::gridSize;
        int startX = (Config::screenWidth - totalGridWidth) / 2;
        int startY = Config::screenHeight - 25 - totalGridHeight;

        Color bodyColor = {255, 204, 204, 255};
        Color headColor = {255, 182, 193, 255};

        for(int x = 0; x < Config::gridWidth; x ++){
            for(int y = 0; y < Config::gridHeight; y ++){
                if(grid[x][y]){
                    int drawX = startX + x * Config::gridSize;
                    int drawY = startY + y * Config::gridSize;
                    
                    if (x == (int)head.x && y == (int)head.y){
                        DrawRectangle(drawX, drawY, Config::gridSize, Config::gridSize, headColor);
                    }
                    else{
                        DrawRectangle(drawX, drawY, Config::gridSize, Config::gridSize, bodyColor);
                    }
                }
            }
        }
    }
    void Reset(){
        dir = 0;
        now_dir = dir;
        snake = std::queue<Vector2>();
        grid = std::vector<std::vector<bool>> (Config::gridWidth, std::vector<bool>(Config::gridHeight, false));
        ResetSnake();
    }
    void AddCell(Vector2 pos){
        snake.push(pos);
        grid[pos.x][pos.y] = true;
    }
    std::vector<std::vector<bool>> GetGrid(){
        return grid;
    }
    void HandleInput() {
        if(dir != now_dir)
            return;
        if (InputManager::IsActionPressed(GameAction::UP) && dir != 2) {
            dir = 0;
        } else if (InputManager::IsActionPressed(GameAction::RIGHT) && dir != 3) {
            dir = 1;
        } else if (InputManager::IsActionPressed(GameAction::DOWN) && dir != 0) {
            dir = 2;
        } else if (InputManager::IsActionPressed(GameAction::LEFT) && dir != 1) {
            dir = 3;
        }
    }
};
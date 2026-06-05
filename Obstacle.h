#pragma once
#include "raylib.h"
#include "Config.h"

class Obstacle{
private:
    Vector2 pos;
    Texture2D texture;
public:
    Obstacle(){
        texture = LoadTexture(Config::pipi_png);
        Reset();
    }
    ~Obstacle(){
        UnloadTexture(texture);
    }
    void Update(){
        Spawn();
    }
    void Draw(){
        int totalGridWidth = Config::gridWidth * Config::gridSize;
        int totalGridHeight = Config::gridHeight * Config::gridSize;
        int startX = (Config::screenWidth - totalGridWidth) / 2;
        int startY = Config::screenHeight - 25 - totalGridHeight;

        float drawX = startX + pos.x * Config::gridSize;
        float drawY = startY + pos.y * Config::gridSize;
        
        Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
        Rectangle dest = { drawX, drawY, (float)Config::gridSize, (float)Config::gridSize };
        Vector2 origin = { 0.0f, 0.0f };

        DrawTexturePro(texture, source, dest, origin, 0.0f, WHITE);
    }
    void Spawn(){
        int randX = GetRandomValue(0, Config::gridWidth - 1), randY = GetRandomValue(0, Config::gridHeight - 1);
        pos = {(float)randX, (float)randY};
    }
    void Reset(){
        Spawn();
    }
    Vector2 GetPos(){
        return pos;
    }
};


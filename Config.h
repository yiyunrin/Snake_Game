#pragma once
#include "vector"

namespace Config{
    const int screenWidth = 500;
    const int screenHeight = 675;

    const int gridWidth = 15;
    const int gridHeight = 20;
    const int gridSize = 30;

    inline constexpr const char* pipi_png = "pipidoll.png";

    // 上右下左
    const std::vector<Vector2> direction = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    const Vector2 startPos = {4, 13};
    const int snakeMaxSize = 301;
    const int initialSpeed = 20;

    const char* overText = "GAME OVER";
    const int overSize = 40;

    const char* restartText = "Press ENTER to Restart";
    const int restartSize = 20;
}
#pragma once
#include "raylib.h"

enum class GameAction{
    RESTART,
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class InputManager{
public:
    static bool IsActionPressed(GameAction action){
        switch (action){
            case GameAction::RESTART:
                return IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP);
            case GameAction::UP:
                return IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsGestureDetected(GESTURE_SWIPE_UP);
            case GameAction::RIGHT:
                return IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsGestureDetected(GESTURE_SWIPE_RIGHT);
            case GameAction::DOWN:
                return IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S) || IsGestureDetected(GESTURE_SWIPE_DOWN);
            case GameAction::LEFT:
                return IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsGestureDetected(GESTURE_SWIPE_LEFT);
            default:
                return false;
        }
    }
    
};
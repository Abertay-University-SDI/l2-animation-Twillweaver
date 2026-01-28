#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Sheep : public GameObject
{
public:
    Sheep();
    virtual ~Sheep() = default;

    void update(float dt) override;
    void handleInput(float dt) override;

private:
    // Animations for all directions
    Animation m_walkDown;
    Animation m_up;
    Animation m_upRight;
    Animation m_right;
    Animation m_downRight;

    Animation* m_currentAnimation; // pointer to currently active animation

    enum class Direction { UP, DOWN, LEFT, RIGHT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT, NONE };
    Direction m_direction = Direction::NONE;

    float m_speed = 300.0f;
    float m_inputBuffer = 0.f;

    const float INPUT_BUFFER_LENGTH = 0.1f;
    const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;

    bool m_gameOver = false;
};

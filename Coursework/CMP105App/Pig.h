#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Pig : public GameObject
{
public:
    Pig();
    virtual ~Pig() = default;

    void update(float dt) override;

    // Called from Level
    void checkDistanceAndUpdate(sf::Vector2f sheepPos);

private:
    // Animations
    Animation m_walkDown;
    Animation m_up;
    Animation m_upRight;
    Animation m_right;
    Animation m_downRight;

    Animation* m_currentAnimation;

    enum class Direction
    {
        UP, DOWN, LEFT, RIGHT,
        UP_RIGHT, DOWN_RIGHT,
        DOWN_LEFT, UP_LEFT,
        NONE
    };

    Direction m_direction = Direction::NONE;

    float m_speed = 100.f; // slower than sheep
    const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;
};

#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Rabbit : public GameObject
{
public:
    Rabbit();

    void update(float dt) override;
    void fleeFrom(sf::Vector2f sheepPos);

private:
    Animation m_walkDown;
    Animation m_up;
    Animation m_upRight;
    Animation m_right;
    Animation m_downRight;

    Animation* m_currentAnimation = nullptr;

    enum class Direction
    {
        UP, DOWN, LEFT, RIGHT,
        UP_RIGHT, DOWN_RIGHT,
        DOWN_LEFT, UP_LEFT,
        NONE
    };

    Direction m_direction = Direction::NONE;

    float m_speed = 450.f; // faster than sheep & pig
    const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;

    bool m_wallEscape = false; // true while running to the center

};

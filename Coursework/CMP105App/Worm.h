#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"

class Worm : public GameObject
{
public:
    Worm();

    void update(float dt) override;
    void start(float duration, float windowWidth, float windowHeight);
    bool isFinished() const;
    float getTimeLeft() const;

private:
    Animation m_wiggle;
    Animation* m_currentAnimation = nullptr;

    float m_timer = 0.f;
    float m_duration = 15.f;
    float m_speed = 0.f;

    bool m_finished = false;
    float m_windowWidth = 0.f;
};

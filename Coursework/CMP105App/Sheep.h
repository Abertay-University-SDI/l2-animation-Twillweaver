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
    Animation m_walkDown;
    Animation* m_currentAnimation;
};

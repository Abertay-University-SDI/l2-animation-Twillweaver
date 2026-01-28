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
    // We will add animation and movement logic here later
};

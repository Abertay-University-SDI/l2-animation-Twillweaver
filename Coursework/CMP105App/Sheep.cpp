#include "Sheep.h"

Sheep::Sheep()
{
    for (int i = 0; i < 4; i++)
    {
        sf::IntRect frame(
            sf::Vector2i(i * 64, 0),
            sf::Vector2i(64, 64)
        );
        m_walkDown.addFrame(frame);
    }

    m_walkDown.setLooping(true);
    m_walkDown.setFrameSpeed(1.f / 4.f);

    m_currentAnimation = &m_walkDown;

    // GameObject inherits sf::RectangleShape, so this is valid
    setTextureRect(m_currentAnimation->getCurrentFrame());
}


void Sheep::handleInput(float dt)
{
    // To be implemented in next tasks
}

void Sheep::update(float dt)
{
    m_currentAnimation->animate(dt);
    setTextureRect(m_currentAnimation->getCurrentFrame());
}


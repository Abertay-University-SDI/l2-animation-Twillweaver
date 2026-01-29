#include "Worm.h"
#include <algorithm>

Worm::Worm()
{
    // 6 frames, 384px wide, 64px tall
    for (int i = 0; i < 6; i++)
    {
        // **mirror Sheep style** using sf::Vector2i
        m_wiggle.addFrame(sf::IntRect(sf::Vector2i(i * 64, 0), sf::Vector2i(64, 64)));
    }

    m_wiggle.setLooping(true);
    m_wiggle.setFrameSpeed(1.f / 8.f); // nice wiggle speed

    m_currentAnimation = &m_wiggle;

    // set initial texture
    setTextureRect(m_currentAnimation->getCurrentFrame());
}

void Worm::start(float duration, float windowWidth, float windowHeight)
{
    m_duration = duration;
    m_timer = 0.f;
    m_finished = false;
    m_windowWidth = windowWidth;

    // Fully visible bottom-left
    setPosition(sf::Vector2f(0.f, windowHeight - getSize().y));

    // calculate speed to reach right edge exactly when timer ends
    float distance = windowWidth - getSize().x;
    m_speed = distance / duration;
}

void Worm::update(float dt)
{
    if (m_finished) return;

    m_timer += dt;

    // move worm horizontally
    move(sf::Vector2f(m_speed * dt, 0.f));

    // animate worm
    m_currentAnimation->animate(dt);
    setTextureRect(m_currentAnimation->getCurrentFrame());

    if (m_timer >= m_duration)
    {
        m_finished = true;

        // clamp exactly at the right edge
        setPosition(sf::Vector2f(m_windowWidth - getSize().x, getPosition().y));
    }
}

float Worm::getTimeLeft() const
{
    return std::max(0.f, m_duration - m_timer);
}

bool Worm::isFinished() const
{
    return m_finished;
}

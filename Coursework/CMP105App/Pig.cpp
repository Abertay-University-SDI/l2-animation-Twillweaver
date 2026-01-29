#include "Pig.h"
#include <cmath>

Pig::Pig()
{
    // DOWN
    for (int i = 0; i < 4; i++)
        m_walkDown.addFrame(sf::IntRect(sf::Vector2i(i * 64, 0), sf::Vector2i(64, 64)));
    m_walkDown.setLooping(true);
    m_walkDown.setFrameSpeed(1.f / 4.f);

    // UP
    for (int i = 4; i < 8; i++)
        m_up.addFrame(sf::IntRect(sf::Vector2i(i * 64, 0), sf::Vector2i(64, 64)));
    m_up.setLooping(true);
    m_up.setFrameSpeed(1.f / 4.f);

    // UP-RIGHT
    for (int i = 0; i < 4; i++)
        m_upRight.addFrame(sf::IntRect(sf::Vector2i(i * 64, 64), sf::Vector2i(64, 64)));
    m_upRight.setLooping(true);
    m_upRight.setFrameSpeed(1.f / 4.f);

    // RIGHT
    for (int i = 4; i < 8; i++)
        m_right.addFrame(sf::IntRect(sf::Vector2i(i * 64, 64), sf::Vector2i(64, 64)));
    m_right.setLooping(true);
    m_right.setFrameSpeed(1.f / 4.f);

    // DOWN-RIGHT
    for (int i = 0; i < 4; i++)
        m_downRight.addFrame(sf::IntRect(sf::Vector2i(i * 64, 128), sf::Vector2i(64, 64)));
    m_downRight.setLooping(true);
    m_downRight.setFrameSpeed(1.f / 4.f);

    m_currentAnimation = &m_walkDown;
    setTextureRect(m_currentAnimation->getCurrentFrame());
}

void Pig::checkDistanceAndUpdate(sf::Vector2f sheepPos)
{
    sf::Vector2f pigPos = getPosition();
    sf::Vector2f diff = sheepPos - pigPos;

    float dist = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    if (dist < 5.f)
    {
        m_direction = Direction::NONE;
        return;
    }

    // Normalised direction
    sf::Vector2f dir = diff / dist;

    const float threshold = 0.3f;

    if (dir.y < -threshold)
    {
        if (dir.x > threshold)       m_direction = Direction::UP_RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::UP_LEFT;
        else                         m_direction = Direction::UP;
    }
    else if (dir.y > threshold)
    {
        if (dir.x > threshold)       m_direction = Direction::DOWN_RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::DOWN_LEFT;
        else                         m_direction = Direction::DOWN;
    }
    else
    {
        if (dir.x > threshold)       m_direction = Direction::RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::LEFT;
        else                         m_direction = Direction::NONE;
    }
}


void Pig::update(float dt)
{
    if (m_direction == Direction::NONE) return;

    float diag = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
    float ortho = m_speed * dt;

    switch (m_direction)
    {
    case Direction::UP:
        m_currentAnimation = &m_up;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(0, -ortho));
        break;

    case Direction::UP_RIGHT:
        m_currentAnimation = &m_upRight;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(diag, -diag));
        break;

    case Direction::RIGHT:
        m_currentAnimation = &m_right;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(ortho, 0));
        break;

    case Direction::DOWN_RIGHT:
        m_currentAnimation = &m_downRight;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(diag, diag));
        break;

    case Direction::DOWN:
        m_currentAnimation = &m_walkDown;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(0, ortho));
        break;

    case Direction::DOWN_LEFT:
        m_currentAnimation = &m_downRight;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-diag, diag));
        break;

    case Direction::LEFT:
        m_currentAnimation = &m_right;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-ortho, 0));
        break;

    case Direction::UP_LEFT:
        m_currentAnimation = &m_upRight;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-diag, -diag));
        break;

    default:
        break;
    }

    m_currentAnimation->animate(dt);
    setTextureRect(m_currentAnimation->getCurrentFrame());
}


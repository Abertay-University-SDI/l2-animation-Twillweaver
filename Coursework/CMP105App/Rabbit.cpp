#include "Rabbit.h"
#include <cmath>

Rabbit::Rabbit()
{
    // DOWN (row 0, frames 1–2)
    m_walkDown.addFrame({ { 64, 0 }, { 64, 64 } });
    m_walkDown.addFrame({ { 128, 0 }, { 64, 64 } });
    m_walkDown.setLooping(true);
    m_walkDown.setFrameSpeed(1.f / 6.f);

    // UP (row 0, frames 3–4)
    m_up.addFrame({ { 192, 0 }, { 64, 64 } });
    m_up.addFrame({ { 256, 0 }, { 64, 64 } });
    m_up.setLooping(true);
    m_up.setFrameSpeed(1.f / 6.f);

    // RIGHT (row 0, frames 0, 5–6)
    m_right.addFrame({ { 0, 0 }, { 64, 64 } });
    m_right.addFrame({ { 320, 0 }, { 64, 64 } });
    m_right.addFrame({ { 384, 0 }, { 64, 64 } });
    m_right.setLooping(true);
    m_right.setFrameSpeed(1.f / 6.f);

    // UP-RIGHT (row 0 frame 7 + row 1 frame 0)
    m_upRight.addFrame({ { 448, 0 }, { 64, 64 } });
    m_upRight.addFrame({ { 0, 64 }, { 64, 64 } });
    m_upRight.setLooping(true);
    m_upRight.setFrameSpeed(1.f / 6.f);

    // DOWN-RIGHT (row 1 frames 1–2)
    m_downRight.addFrame({ { 64, 64 }, { 64, 64 } });
    m_downRight.addFrame({ { 128, 64 }, { 64, 64 } });
    m_downRight.setLooping(true);
    m_downRight.setFrameSpeed(1.f / 6.f);

    m_currentAnimation = &m_walkDown;
    setTextureRect(m_currentAnimation->getCurrentFrame());
}

void Rabbit::fleeFrom(sf::Vector2f sheepPos)
{
    if (!m_window) {
        m_direction = Direction::NONE;
        return;
    }

    sf::Vector2f rabbitPos = getPosition();
    sf::Vector2f size = getSize();
    sf::Vector2u win = m_window->getSize();
    sf::Vector2f center(win.x / 2.f, win.y / 2.f);

    const float margin = 10.f;

    // Check if rabbit is against the wall
    bool trapped =
        rabbitPos.x < margin ||
        rabbitPos.y < margin ||
        rabbitPos.x + size.x > win.x - margin ||
        rabbitPos.y + size.y > win.y - margin;

    sf::Vector2f diff;

    if (m_wallEscape)
    {
        // Still running to center
        diff = center - rabbitPos;

        // Stop wall escape if close enough
        if (std::abs(diff.x) < 2.f && std::abs(diff.y) < 2.f)
        {
            m_wallEscape = false;
            m_direction = Direction::NONE;
            return;
        }
    }
    else if (trapped)
    {
        // Just hit a wall, start wall escape
        m_wallEscape = true;
        diff = center - rabbitPos;
    }
    else
    {
        // Normal flee from sheep
        diff = rabbitPos - sheepPos;
        float distSq = diff.x * diff.x + diff.y * diff.y;

        if (distSq > 40000.f) {
            m_direction = Direction::NONE;
            return;
        }

        if (distSq < 1.f) {
            m_direction = Direction::NONE;
            return;
        }
    }

    // Gradual movement toward target
    float distSq = diff.x * diff.x + diff.y * diff.y;
    if (distSq < 1.f) distSq = 1.f;
    sf::Vector2f dir = diff / std::sqrt(distSq);

    const float threshold = 0.3f;

    // Set 8-direction movement
    if (dir.y < -threshold) {
        if (dir.x > threshold)       m_direction = Direction::UP_RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::UP_LEFT;
        else                         m_direction = Direction::UP;
    }
    else if (dir.y > threshold) {
        if (dir.x > threshold)       m_direction = Direction::DOWN_RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::DOWN_LEFT;
        else                         m_direction = Direction::DOWN;
    }
    else {
        if (dir.x > threshold)       m_direction = Direction::RIGHT;
        else if (dir.x < -threshold) m_direction = Direction::LEFT;
        else                         m_direction = Direction::NONE;
    }
}




void Rabbit::update(float dt)
{
    if (m_direction != Direction::NONE)
    {
        float diag = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
        float ortho = m_speed * dt;

        switch (m_direction)
        {
        case Direction::UP:
            m_currentAnimation = &m_up;
            m_currentAnimation->setFlipped(false);
            move(sf::Vector2f({ 0, -ortho }));
            break;

        case Direction::UP_RIGHT:
            m_currentAnimation = &m_upRight;
            m_currentAnimation->setFlipped(false);
            move(sf::Vector2f({ diag, -diag }));
            break;

        case Direction::RIGHT:
            m_currentAnimation = &m_right;
            m_currentAnimation->setFlipped(false);
            move(sf::Vector2f({ ortho, 0 }));
            break;

        case Direction::DOWN_RIGHT:
            m_currentAnimation = &m_downRight;
            m_currentAnimation->setFlipped(false);
            move(sf::Vector2f({ diag, diag }));
            break;

        case Direction::DOWN:
            m_currentAnimation = &m_walkDown;
            m_currentAnimation->setFlipped(false);
            move(sf::Vector2f({ 0, ortho }));
            break;

        case Direction::DOWN_LEFT:
            m_currentAnimation = &m_downRight;
            m_currentAnimation->setFlipped(true);
            move(sf::Vector2f({ -diag, diag }));
            break;

        case Direction::LEFT:
            m_currentAnimation = &m_right;
            m_currentAnimation->setFlipped(true);
            move(sf::Vector2f({ -ortho, 0 }));
            break;

        case Direction::UP_LEFT:
            m_currentAnimation = &m_upRight;
            m_currentAnimation->setFlipped(true);
            move(sf::Vector2f({ -diag, -diag }));
            break;

        default:
            break;
        }

        m_currentAnimation->animate(dt);
        setTextureRect(m_currentAnimation->getCurrentFrame());
    }

    // always clamp, even when not moving
    if (m_window)
    {
        sf::Vector2f pos = getPosition();
        sf::Vector2f size = getSize();
        sf::Vector2u win = m_window->getSize();

        pos.x = std::clamp(pos.x, 0.f, win.x - size.x);
        pos.y = std::clamp(pos.y, 0.f, win.y - size.y);

        setPosition(pos);
    }
}


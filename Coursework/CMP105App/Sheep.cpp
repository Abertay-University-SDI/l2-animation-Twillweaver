#include "Sheep.h"
#include <iostream>

Sheep::Sheep()
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

    // Set initial texture
    setTextureRect(m_currentAnimation->getCurrentFrame());
}


void Sheep::handleInput(float dt)
{
    // decrement and check the input buffer.
    m_inputBuffer -= dt;
    if (m_inputBuffer > 0)
    {
        return;
    }

    Direction last_dir = m_direction;

    if (m_input->isKeyDown(sf::Keyboard::Scancode::A))
    {
        if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
            m_direction = Direction::UP_LEFT;
        else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
            m_direction = Direction::DOWN_LEFT;
        else
            m_direction = Direction::LEFT;
    }
    else if (m_input->isKeyDown(sf::Keyboard::Scancode::D))
    {
        if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
            m_direction = Direction::UP_RIGHT;
        else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
            m_direction = Direction::DOWN_RIGHT;
        else
            m_direction = Direction::RIGHT;
    }
    else
    {
        if (m_input->isKeyDown(sf::Keyboard::Scancode::W))
            m_direction = Direction::UP;
        else if (m_input->isKeyDown(sf::Keyboard::Scancode::S))
            m_direction = Direction::DOWN;
    }
    
    if (m_input->isKeyDown(sf::Keyboard::Scancode::Space))
    {
        m_direction = Direction::NONE;
        m_currentAnimation->reset();
        return; // stop movement while paused
    }


    if (m_direction != last_dir)
        m_inputBuffer = INPUT_BUFFER_LENGTH;
}

void Sheep::update(float dt)
{
    if (m_direction == Direction::NONE) return;

    if (m_gameOver)
    {
        // freeze sheep, keep last frame
        setTextureRect(m_currentAnimation->getCurrentFrame());
        return;
    }

    // Animation speeds
    float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
    float orthog_speed = m_speed * dt;

    // Choose animation based on direction
    switch (m_direction)
    {
    case Direction::UP:
        m_currentAnimation = &m_up;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(0, -orthog_speed));
        break;

    case Direction::UP_RIGHT:
        m_currentAnimation = &m_upRight;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(diagonal_speed, -diagonal_speed));
        break;

    case Direction::RIGHT:
        m_currentAnimation = &m_right;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(orthog_speed, 0));
        break;

    case Direction::DOWN_RIGHT:
        m_currentAnimation = &m_downRight;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(diagonal_speed, diagonal_speed));
        break;

    case Direction::DOWN:
        m_currentAnimation = &m_walkDown;
        m_currentAnimation->setFlipped(false);
        move(sf::Vector2f(0, orthog_speed));
        break;

    case Direction::DOWN_LEFT:
        m_currentAnimation = &m_downRight;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-diagonal_speed, diagonal_speed));
        break;

    case Direction::LEFT:
        m_currentAnimation = &m_right;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-orthog_speed, 0));
        break;

    case Direction::UP_LEFT:
        m_currentAnimation = &m_upRight;
        m_currentAnimation->setFlipped(true);
        move(sf::Vector2f(-diagonal_speed, -diagonal_speed));
        break;

    default:
        break;
    }

    // Animate current frame
    m_currentAnimation->animate(dt);
    setTextureRect(m_currentAnimation->getCurrentFrame());

    // Boundary / Game Over check (half sprite inside wall)
    if (m_window)
    {
        sf::Vector2f pos = getPosition(); // top-left corner
        sf::Vector2f size = getSize();
        sf::Vector2u winSize = m_window->getSize();

        float halfWidth = size.x / 2.f;
        float halfHeight = size.y / 2.f;

        // center position
        float centerX = pos.x + halfWidth;
        float centerY = pos.y + halfHeight;

        if (centerX - halfWidth < 0 ||        // left half inside wall
            centerX + halfWidth > winSize.x ||// right half inside wall
            centerY - halfHeight < 0 ||       // top half inside wall
            centerY + halfHeight > winSize.y) // bottom half inside wall
        {
            m_gameOver = true;
            std::cout << "Game Over\n";
        }
    }
}


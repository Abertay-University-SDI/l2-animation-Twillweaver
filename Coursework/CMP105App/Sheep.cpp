#include "Sheep.h"
#include <iostream>

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

    if (m_direction != last_dir)
        m_inputBuffer = INPUT_BUFFER_LENGTH;
}

void Sheep::update(float dt)
{ 
    if (m_gameOver) return; // freeze sheep

    // animation
    m_currentAnimation->animate(dt);
    setTextureRect(m_currentAnimation->getCurrentFrame());

    float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
    float orthog_speed = m_speed * dt;

    switch (m_direction)
    {
    case Direction::UP:
        move({ 0, -orthog_speed });
        break;
    case Direction::UP_RIGHT:
        move({ diagonal_speed, -diagonal_speed });
        break;
    case Direction::RIGHT:
        move({ orthog_speed, 0 });
        break;
    case Direction::DOWN_RIGHT:
        move({ diagonal_speed, diagonal_speed });
        break;
    case Direction::DOWN:
        move({ 0, orthog_speed });
        break;
    case Direction::DOWN_LEFT:
        move({ -diagonal_speed, diagonal_speed });
        break;
    case Direction::LEFT:
        move({ -orthog_speed, 0 });
        break;
    case Direction::UP_LEFT:
        move({ -diagonal_speed, -diagonal_speed });
        break;
    default:
        break;
    }

    if (m_window)
    {
        sf::Vector2f pos = getPosition(); // top-left
        sf::Vector2f size = getSize();    // width & height
        sf::Vector2u winSize = m_window->getSize();

        if (pos.x + size.x / 2 > winSize.x || // right half inside wall
            pos.x + size.x / 2 < 0 ||        // left half inside wall
            pos.y + size.y / 2 > winSize.y || // bottom half inside wall
            pos.y + size.y / 2 < 0)           // top half inside wall
        {
            m_gameOver = true;
            std::cout << "Game Over\n";
        }
    }
}


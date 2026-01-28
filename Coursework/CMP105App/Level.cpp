#include "Level.h"
#include <SFML/Graphics.hpp>

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	m_snake.setRadius(20);
	m_snake.setPosition({ 50, 50 });
	m_snake.setFillColor(sf::Color::Green);

	// Load the texture
	if (!m_sheepTex.loadFromFile("gfx/sheep_sheet.png")) {
		// Handle error if the file isn't found
	}

	// Set up the Sheep object
	m_player.setTexture(&m_sheepTex);
	m_player.setSize(sf::Vector2f(64.f, 64.f));
	m_player.setPosition(sf::Vector2f(100.f, 100.f));

	sf::IntRect sheepFrame(
		sf::Vector2i(0, 0),
		sf::Vector2i(64, 64)
	);

	m_player.setTextureRect(sheepFrame);
}

// handle user input
void Level::handleInput(float dt)
{
	if (m_gameOver) return;

	// decrement and check the input buffer.
	m_inputBuffer -= dt;
	if (m_inputBuffer > 0)
	{
		// not long enough has passed since the last input change, so don't handle input
		return;
	}
	// grab this to detect changes per frame for later
	Direction last_dir = m_direction;

	// Set 8-directional movement based on WASD
	if (m_input.isKeyDown(sf::Keyboard::Scancode::A))
	{
		if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_LEFT;
		else if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_LEFT;
		else
			m_direction = Direction::LEFT;
	}
	else if (m_input.isKeyDown(sf::Keyboard::Scancode::D))
	{
		if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP_RIGHT;
		else if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN_RIGHT;
		else
			m_direction = Direction::RIGHT;
	}
	else
	{
		if (m_input.isKeyDown(sf::Keyboard::Scancode::W))
			m_direction = Direction::UP;
		else if (m_input.isKeyDown(sf::Keyboard::Scancode::S))
			m_direction = Direction::DOWN;
	}
	
	// set input buffer if needed, this makes diagonal movement easier
	if (m_direction != last_dir)
		m_inputBuffer = INPUT_BUFFER_LENGTH;
}

// Update game objects
void Level::update(float dt)
{
	if (m_gameOver) return;

	// for diagonal movement
	float diagonal_speed = m_speed * APPROX_ONE_OVER_ROOT_TWO * dt;
	float orthog_speed = m_speed * dt;	// orthogonal movement

	switch (m_direction)
	{
	case Direction::UP:
		m_snake.move({ 0, -orthog_speed });
		break;
	case Direction::UP_RIGHT:
		m_snake.move({ diagonal_speed, -diagonal_speed});
		break;
	case Direction::RIGHT:
		m_snake.move({ orthog_speed,0 });
		break;
	case Direction::DOWN_RIGHT:
		m_snake.move({ diagonal_speed, diagonal_speed });
		break;
	case Direction::DOWN:
		m_snake.move({ 0, orthog_speed });
		break;
	case Direction::DOWN_LEFT:
		m_snake.move({ -diagonal_speed, diagonal_speed });
		break;
	case Direction::LEFT:
		m_snake.move({ -orthog_speed,0 });
		break;
	case Direction::UP_LEFT:
		m_snake.move({ -diagonal_speed, -diagonal_speed });
		break;	
	}

	// check wall collision
	sf::Vector2f pos = m_snake.getPosition();
	float radius = m_snake.getRadius();

	if (pos.x < 0 || pos.x + radius > m_window.getSize().x || pos.y < 0 || pos.y + radius > m_window.getSize().y)
	{
		m_gameOver = true;
		std::cout << "Game over";
	}

}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_snake);  // The old snake circle
	m_window.draw(m_player); // Our new sheep!
	endDraw();
}


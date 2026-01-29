#include "Level.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Level::Level(sf::RenderWindow& hwnd, Input& in) :
	BaseLevel(hwnd, in)
{
	// Load the texture
	if (!m_sheepTex.loadFromFile("gfx/sheep_sheet.png")) {
		// Handle error if the file isn't found
	}

	// Set up the Sheep object
	m_player.setTexture(&m_sheepTex);
	m_player.setSize(sf::Vector2f(64.f, 64.f));
	m_player.setPosition(sf::Vector2f(100.f, 100.f));

	// give sheep access to input
	m_player.setInput(&m_input);
	// set boundary
	m_player.setWindow(&m_window);

	sf::IntRect sheepFrame(
		sf::Vector2i(0, 0),
		sf::Vector2i(64, 64)
	);

	// worm set-up
	m_player.setTextureRect(sheepFrame);

	if (!m_wormTex.loadFromFile("gfx/worm_sheet.png"))
	{
		std::cout << "Failed to load worm texture\n";
	}

	m_worm.setTexture(&m_wormTex);
	m_worm.setSize(sf::Vector2f(64.f, 64.f));
	m_worm.start(15.f, m_window.getSize().x, m_window.getSize().y);

	// pig set-up
	if (!m_pigTex.loadFromFile("gfx/pig_sheet.png"))
	{
		std::cout << "Failed to load pig texture\n";
	}

	m_pig.setTexture(&m_pigTex);
	m_pig.setSize(sf::Vector2f(64.f, 64.f));
	m_pig.setPosition(sf::Vector2f(400.f, 300.f));

}

// handle user input
void Level::handleInput(float dt)
{
	m_player.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	// If game already over, stop everything
	if (m_gameOver)
		return;

	// --- Update sheep ---
	m_player.update(dt);

	// Check if sheep hit a boundary → GAME OVER
	if (!m_player.isAlive())
	{
		m_gameOver = true;
		std::cout << "Game Over!\n";
		return; // Stop worm, timer, everything
	}

	// Update pig AI
	m_pig.checkDistanceAndUpdate(m_player.getPosition());
	m_pig.update(dt);


	// --- Update worm ---
	if (!m_gameOver)
	{
		m_worm.update(dt);

		// Countdown debug output (only while game running)
		int secondsLeft = static_cast<int>(std::ceil(m_worm.getTimeLeft()));
		if (secondsLeft >= 1 && secondsLeft != m_lastPrintedSecond)
		{
			m_lastPrintedSecond = secondsLeft;
			std::cout << "Time left: " << secondsLeft << std::endl;
		}

		// Worm timer finished → GAME OVER
		if (m_worm.isFinished())
		{
			m_gameOver = true;
			std::cout << "Time's up!\n";
			return; // Stop everything
		}
	}
}




// Render level
void Level::render()
{
	beginDraw();

	m_window.draw(m_player); // draw the sheep no matter what

	m_window.draw(m_pig); // draw the pig

	m_window.draw(m_worm);  //draw the worm

	endDraw();
}


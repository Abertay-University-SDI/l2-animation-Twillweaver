#include "Level.h"
#include <SFML/Graphics.hpp>

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

	m_player.setTextureRect(sheepFrame);
}

// handle user input
void Level::handleInput(float dt)
{
	m_player.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	if (m_player.isAlive())
		m_player.update(dt); // makes the animation run 
}

// Render level
void Level::render()
{
	beginDraw();
	m_window.draw(m_player); // draw the sheep no matter what
	endDraw();
}


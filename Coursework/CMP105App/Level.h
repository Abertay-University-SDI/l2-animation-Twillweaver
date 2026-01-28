#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Sheep.h"

class Level : BaseLevel {
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.

	// Default variables for level class.
	enum class Direction{ UP, DOWN, LEFT, RIGHT, UP_RIGHT, DOWN_RIGHT, DOWN_LEFT, UP_LEFT, NONE };
	Direction m_direction = Direction::NONE;
	sf::CircleShape m_snake;
	float m_speed = 300.0f;
	float m_inputBuffer = 0.f;
	bool m_gameOver = false;

	Sheep m_player;          // Our new Sheep object
	sf::Texture m_sheepTex;  // Texture for the sheep

	const float INPUT_BUFFER_LENGTH = 0.1f;
	const float APPROX_ONE_OVER_ROOT_TWO = 0.70710678f;	// 1 / sqrt(2)

};
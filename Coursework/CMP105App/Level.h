#pragma once

#include "Framework/BaseLevel.h"
#include "Framework/GameObject.h"
#include "Sheep.h"
#include "Worm.h"
#include "Pig.h"
#include "Rabbit.h"

class Level : public BaseLevel {
public:
	Level(sf::RenderWindow& window, Input& input);
	~Level() override = default;

	void handleInput(float dt) override;
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.

	Sheep m_player;          // Sheep object
	sf::Texture m_sheepTex;  // Texture for the sheep

	Worm m_worm; //worm object
	sf::Texture m_wormTex;  //worm texture

	Pig m_pig;  // pig object
	sf::Texture m_pigTex;  //pig texture

	Rabbit m_rabbit;  // Rabbit object
	sf::Texture m_rabbitTex;  // rabbit texture

	bool m_gameOver = false;  // game over flag

	int m_lastPrintedSecond = -1; // count-down timer for the worm
};
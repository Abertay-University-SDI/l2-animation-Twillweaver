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

	Sheep m_player;          // Our new Sheep object
	sf::Texture m_sheepTex;  // Texture for the sheep
};
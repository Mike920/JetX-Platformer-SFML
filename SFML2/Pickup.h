#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "AnimationManager.h"
#include "ResourceHolder.h"

class Pickup
{

protected:
	AnimationManager mAnimation;
	sf::Vector2f mSize;
	std::vector<sf::FloatRect> mObjects;

public:
	Pickup(void);
	~Pickup(void);
	void loadTexture(const sf::Texture& texture);

};


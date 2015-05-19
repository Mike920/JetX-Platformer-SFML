#pragma once
#include "Enemy.h"
#include <cstdlib>

class Bat : public Enemy
{
public:
	Bat(void);
	virtual ~Bat(void);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(sf::Time dt);
	virtual void loadTexture(const TextureHolder& textures);
};


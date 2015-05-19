#pragma once
#include "Enemy.h"
#include <cstdlib>

class Bug : public Enemy
{
public:
	Bug(void);
	virtual ~Bug(void);

	//virtual void initialize(tmx::MapLoader& map);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(sf::Time dt);
	virtual void loadTexture(const TextureHolder& textures);
};


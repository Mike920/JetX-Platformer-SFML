#pragma once
#include "Enemy.h"
#include "Player.h"
#include <cstdlib>

class Firebug : public Enemy
{
private:
	sf::FloatRect mAttackArea;
	sf::Vector2f mBasicVelocity;

	bool mIsAttacking;
public:
	Firebug();
	virtual ~Firebug(void);

	//virtual void initialize(tmx::MapLoader& map);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(sf::Time dt);
	virtual void loadTexture(const TextureHolder& textures);

	void setAttackArea(sf::FloatRect rect);
	void attackAreaCollision();
	
};


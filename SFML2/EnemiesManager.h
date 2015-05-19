#pragma once
#include "Enemy.h"
#include "Bug.h"
#include "Firebug.h"
#include "Bat.h"
//#include "Player.h"
#include <vector>

class EnemiesManager : public sf::Drawable
{
private:
	std::vector< Enemy* > mEnemiesContainer;
	
public:

	EnemiesManager(void);
	~EnemiesManager(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(sf::Time dt);
	void initialize(tmx::MapLoader& map);
	void loadTexture(const TextureHolder& textures);
	void setPlayer(Player& player);
	bool intersection(sf::FloatRect rect);
};


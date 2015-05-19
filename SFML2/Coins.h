#pragma once
#include "Pickup.h"
#include <tmx\MapLoader.h>


class Coins : public Pickup
{
private:
	int mPoints;
	int mMaxPoints;
public:
	Coins();
	~Coins(void);
	 void draw(sf::RenderTarget& target, sf::RenderStates states);
	 void update(sf::Time dt);

	void setAnimationPosition(sf::Vector2f pos);
	std::vector<sf::FloatRect>& getObjectsVector();
	void incrementPoints();
	int getPoints();
	int getMaxPoints();

	void initialize(tmx::MapLoader& map);
};
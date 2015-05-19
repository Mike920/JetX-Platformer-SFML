#pragma once
#include "Pickup.h"
#include <tmx\MapLoader.h>


class Star : public sf::Drawable
{
private:

	sf::Vector2f mSize;
	int mPoints;
	int mMaxPoints;
	sf::Sprite mSprite;
public:
	Star();
	~Star(void);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	sf::FloatRect getGlobalBounds();
	void loadTexture(const sf::Texture& texture);
	void initialize(tmx::MapLoader& map);
};
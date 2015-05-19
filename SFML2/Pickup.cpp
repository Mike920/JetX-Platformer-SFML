#include "Pickup.h"


Pickup::Pickup(void) : mAnimation()
{
}


Pickup::~Pickup(void)
{
}

void Pickup::loadTexture(const sf::Texture& texture)
{
	mAnimation.setTexture(texture);
}
#include "Star.h"


Star::Star()
{
	mSize = sf::Vector2f(60,56);

}

void Star::initialize(tmx::MapLoader& map)
{
	for(auto& layer : map.GetLayers())
		if(layer.name=="Star")
			for(auto& object : layer.objects)
				mSprite.setPosition(object.GetPosition().x,object.GetPosition().y-object.GetAABB().height);
	
}

void Star::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(mSprite,states);
}




sf::FloatRect Star::getGlobalBounds()
{
	return mSprite.getGlobalBounds();
}

Star::~Star(void)
{
}

void Star::loadTexture(const sf::Texture& texture)
{
	mSprite.setTexture(texture);
}
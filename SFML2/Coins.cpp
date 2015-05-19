#include "Coins.h"


Coins::Coins()
{
	mSize = sf::Vector2f(32,32);
	mPoints=0;

	
	Animation rotate(sf::seconds(1.0f));
	for(int i=0;i<10;i++)
		rotate.addFrame(sf::IntRect(mSize.x*i, 0, mSize.x,mSize.y));
	mAnimation.addAnimation("rotate",rotate);

	mAnimation.playAnimation("rotate");

}

void Coins::initialize(tmx::MapLoader& map)
{
	for(auto& layer : map.GetLayers())
		if(layer.name=="Coins")
			for(auto& object : layer.objects)
				mObjects.push_back(sf::FloatRect(object.GetPosition(),mSize));
	mMaxPoints=mObjects.size();
}

void Coins::draw(sf::RenderTarget& target, sf::RenderStates states) 
{
	
	//states.transform *= getTransform();
//	target.draw(mSprite,states); 
	for(auto& object : mObjects)
	{
		setAnimationPosition(sf::Vector2f(object.left,object.top));
		mAnimation.draw(target,states);
	}

}

void Coins::update(sf::Time dt)
{
	mAnimation.update(dt);
}
void Coins::setAnimationPosition(sf::Vector2f pos)
{
	mAnimation.setPosition(pos);
}

void Coins::incrementPoints()
{
	mPoints++;
}
int Coins::getPoints()
{
	return mPoints;
}
int Coins::getMaxPoints()
{
	return mMaxPoints;
}

std::vector<sf::FloatRect>& Coins::getObjectsVector()
{
	return mObjects;
}

Coins::~Coins(void)
{
}

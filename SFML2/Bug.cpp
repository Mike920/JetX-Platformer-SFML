#include "Bug.h"


Bug::Bug(void)
{
	int upMargin = 19;
	mSpriteSize = sf::Vector2f(48,48-upMargin);
	setVelocity((float)(( rand() % 30 ) + 40),100.f);
	Animation walk(sf::seconds(0.6f));
//	for(int i=0;i<10;i++)
	
	walk.addFrame(sf::IntRect(0, 0+upMargin, mSpriteSize.x,mSpriteSize.y));
	walk.addFrame(sf::IntRect(0, mSpriteSize.y+upMargin*2, mSpriteSize.x,mSpriteSize.y));
	walk.addFrame(sf::IntRect(mSpriteSize.x, mSpriteSize.y+upMargin*2, mSpriteSize.x,mSpriteSize.y));
	mAnimation.addAnimation("walk",walk);

	mAnimation.playAnimation("walk");

	if((rand() % 2))
		mIsMovingLeft=true;
	else
		mIsMovingRight=true;
}

Bug::~Bug(void)
{
}

void Bug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
//	target.draw(mSprite,states); 
	mAnimation.draw(target,states);
}

void Bug::update(sf::Time dt)
{
	mAnimation.update(dt);
	if(mIsMovingRight && mPosition.x<mMovementScope.right*32)
	{
		move(getVelocity().x*dt.asSeconds(),0);
		mPosition.x+=getVelocity().x*dt.asSeconds();
	}
	else
	{
		mIsMovingRight=false;
		mIsMovingLeft=true;
	}
	
	if(mIsMovingLeft && -mPosition.x < mMovementScope.left*32)
	{
		move(-getVelocity().x*dt.asSeconds(),0);
		mPosition.x-=getVelocity().x*dt.asSeconds();
	}
	else
	{
		mIsMovingRight=true;
		mIsMovingLeft=false;
	}

	if(mIsMovingLeft)
		mAnimation.reverseSprite(true);
	else if(mIsMovingRight)
		mAnimation.reverseSprite(false);
}

void Bug::loadTexture(const TextureHolder& textures)
{
	mAnimation.setTexture(textures.get(Textures::Bug));
}
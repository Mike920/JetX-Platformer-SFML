#include "Bat.h"


Bat::Bat(void)
{

	mSpriteSize = sf::Vector2f(40,40);
	setVelocity((float)(( rand() % 20 ) + 60),100.f);
	
	Animation fly(sf::seconds(0.6f));
	for(int i=0;i<8;i++)
		fly.addFrame(sf::IntRect(0, mSpriteSize.y*i, mSpriteSize.x,mSpriteSize.y));

	mAnimation.addAnimation("fly",fly);

	mAnimation.playAnimation("fly");

	if((rand() % 2))
		mIsMovingLeft=true;
	else
		mIsMovingRight=true;
}

Bat::~Bat(void)
{
}

void Bat::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	mAnimation.draw(target,states);
}

void Bat::update(sf::Time dt)
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

void Bat::loadTexture(const TextureHolder& textures)
{
	mAnimation.setTexture(textures.get(Textures::Bat));
}
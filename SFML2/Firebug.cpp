#include "Firebug.h"


Firebug::Firebug()
{

	int upMargin = 19;
	mSpriteSize = sf::Vector2f(48,48-upMargin);
	setVelocity((float)(( rand() % 10 ) + 35),100.f);
	mBasicVelocity = getVelocity();
	mIsAttacking=false;
	
	Animation roll(sf::seconds(0.5));
	for(int i=0;i<4;i++)
		roll.addFrame(sf::IntRect(mSpriteSize.x*i, mSpriteSize.y*2+upMargin*3, mSpriteSize.x,mSpriteSize.y));
	mAnimation.addAnimation("roll",roll);

	Animation walk(sf::seconds(0.6f));
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

Firebug::~Firebug(void)
{
}

void Firebug::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
//	target.draw(mSprite,states); 
	mAnimation.draw(target,states);
}

void Firebug::update(sf::Time dt)
{
	attackAreaCollision();

	mAnimation.update(dt);
	if(mIsMovingRight && mPosition.x<mMovementScope.right*32)
	{
		move(getVelocity().x*dt.asSeconds(),0);
		mPosition.x+=getVelocity().x*dt.asSeconds();
	}
	else
	{
		if(mIsMovingRight)
		{
			mAnimation.playAnimation("walk");
			setVelocity(mBasicVelocity);
			mIsAttacking=false;
		}
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
		if(mIsMovingLeft)
		{
			mAnimation.playAnimation("walk");
			setVelocity(mBasicVelocity);
			mIsAttacking=false;
		}
		mIsMovingRight=true;
		mIsMovingLeft=false;
	}

	if(mIsMovingLeft)
		mAnimation.reverseSprite(true);
	else if(mIsMovingRight)
		mAnimation.reverseSprite(false);
}

void Firebug::loadTexture(const TextureHolder& textures)
{
	mAnimation.setTexture(textures.get(Textures::Firebug));
}

void Firebug::attackAreaCollision()
{
	if(!mIsAttacking)
	{
		if(mAttackArea.intersects( mPlayer->getAABB() ))
			if(getPosition().x > mPlayer->getAABB().left)
			{
				mIsMovingLeft=true;
				mIsMovingRight=false;
				setVelocity(mBasicVelocity.x*3.f,0);
				mAnimation.playAnimation("roll");
				mIsAttacking=true;
			}
			else
			{
				mIsMovingLeft=false;
				mIsMovingRight=true;
				setVelocity(mBasicVelocity.x*3.f,0);
				mAnimation.playAnimation("roll");
				mIsAttacking=true;
			}
	}
}

void Firebug::setAttackArea(sf::FloatRect rect)
{
	mAttackArea=rect;
}
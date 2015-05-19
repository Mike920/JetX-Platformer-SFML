#include "Enemy.h"


Enemy::Enemy(void)
	: mPosition(0,0)
{
	
	mIsMovingLeft=false;
	mIsMovingRight=false;
}


Enemy::~Enemy(void)
{
}



void Enemy::setMovementScope(MovementScope scope)
{
	mMovementScope=scope; 
}

sf::Vector2f Enemy::getSpriteSize()
{
	return mSpriteSize;
}

sf::FloatRect Enemy::getGlobalBounds()
{
	return sf::FloatRect(getPosition(), mSpriteSize);
}

void Enemy::setPlayer(Player& player)
{
	mPlayer = &player;
}
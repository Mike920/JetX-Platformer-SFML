#include "Entity.h"

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity=velocity;
}
void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x=vx;
	mVelocity.y=vy;
}
sf::Vector2f Entity::getVelocity() const
{
	return mVelocity;
}

void Entity::update(sf::Time dt)
{
	move(mVelocity*dt.asSeconds());
}

sf::Transform Entity::getWorldTransform() const
{
	return getTransform();
}

sf::Vector2f Entity::getWorldPosition() const
{
	return getWorldTransform()*sf::Vector2f(); 
}
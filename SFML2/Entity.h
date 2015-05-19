#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
private:
	sf::Vector2f mVelocity;
	const float mGravity;
public:
	Entity()
		: mGravity(5.f) {}
	virtual ~Entity(){};
	void setVelocity(sf::Vector2f velocity);
	void setVelocity(float vx, float vy);
	float getGravity()	{ return mGravity;}
	sf::Vector2f getVelocity() const;
	virtual void update(sf::Time dt)=0;

	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;

//	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};


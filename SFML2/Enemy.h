#pragma once

#include "Entity.h"
#include "AnimationManager.h"
#include "ResourceHolder.h"
#include <tmx\MapLoader.h>

//Forward declaration
class Player;

class Enemy : public Entity
{
private:
	
public:
	struct MovementScope
	{
		int left;
		int right;
		int up;
		int down;
	};

protected:
	
	Player* mPlayer;
	sf::Vector2f mSpriteSize;
	AnimationManager mAnimation;
//	sf::FloatRect mUnit;
	MovementScope mMovementScope;
	sf::Vector2f mPosition;
	bool mIsMovingLeft;
	bool mIsMovingRight;


public:
	Enemy(void);
	virtual ~Enemy(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const =0;
	virtual void update(sf::Time dt)=0;
	virtual void loadTexture(const TextureHolder& textures)=0;

	void setMovementScope(MovementScope scope);
	void setPlayer(Player& player);
	sf::Vector2f getSpriteSize();
	sf::FloatRect getGlobalBounds();


	//virtual void initialize(tmx::MapLoader& map);
};


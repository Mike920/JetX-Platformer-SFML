#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include <tmx\MapLoader.h>
//#include <sstream>
#include <string>
#include <stdexcept>
#include "AnimationManager.h"
#include "Coins.h"
#include "EnemiesManager.h"
#include "Star.h"

//Forward decl
class EnemiesManager;

class Player :
	public Entity
{
private:
	struct CollisionPoints
	{
		sf::Vector2f up[2];
		sf::Vector2f down[2];
		sf::Vector2f left[3];
		sf::Vector2f right[3];
	};

	AnimationManager mAnimation;
	sf::Sprite mSprite;
	const sf::Vector2i mSpriteSize;
	sf::Vector2f mMovement;
	tmx::MapLoader* mMap;
	Coins* mCoins;
	Star* mStar;
	EnemiesManager* mEnemyManager;
	CollisionPoints mCollPoints;
	//Collision points margin
	bool mPlayerDead;
	bool mLevelCompleted;

	int mCollMarg;

	int mleftMargin;
	int mRightMargin;
	int mTopMargin;
	int mBottomMargin;

	bool mIsJumping;
	bool mIsMovingLeft;
	bool mIsMovingRight;

	bool mCollisionLeft;
	bool mCollisionRight;
	bool mCollisionUp;
	bool mCollisionDown;

	float mFrictionStart;
	float mFrictionStop;
	float mFrictionVertical;
	sf::Font mFont;
//	std::stringstream ss; 

	void collisionDetection(sf::FloatRect& playerRect);
	void pickupCollisionDetection(sf::FloatRect& playerRect);
public:
	//Player(const TextureHolder& textures);
	Player(){};
	Player(tmx::MapLoader& map, Coins& coins, EnemiesManager& enemyManager, Star& star);
	~Player(void);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void loadTexture(const TextureHolder& textures);
	void update(sf::Time dt);
	void handleRealtimeInput(sf::Time dt);
	sf::Vector2f getPlayerPosition();
	sf::FloatRect getAABB();
	
	bool isLevelCompleted();
	bool isPlayerDead();

};


#pragma once

#include "ResourceHolder.h"
#include "Entity.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tmx\MapLoader.h>
#include "Player.h"
#include "Coins.h"
#include "Star.h"
#include "EnemiesManager.h"
//#include "Game.h"
#include <array>

//class Game;

class World
{
private:
	sf::RenderWindow& mWindow;
	sf::View	mWorldView;
	TextureHolder mTextures;
	std::array<Entity*,10> mEntities;
	Player mPlayer;
	Coins mCoins;
	Star mStar;

	EnemiesManager mEnemiesManager;
	sf::Sprite mBackground;
	tmx::MapLoader mMap;
	string mMapName;

	sf::FloatRect	mWorldBounds;	//size of whole map
	sf::Vector2f	mSpawnPosition;

public:
	World(sf::RenderWindow& window, string mapName);
	void update(sf::Time dt);
	void draw();
	void handleEvent(sf::Event e);

	bool isLevelCompleted();
	bool isPlayerDead();
	int getPoints();
	int getMaxPoints();
	
private:
	enum Layer
		{
			Background,
			Midground,
			LayerCount
		};
	void loadTextures();
	void builtScene();
};


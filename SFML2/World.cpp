#include "World.h"

World::World(sf::RenderWindow& window, string mapName)
	: mWindow(window)
	, mWorldView(window.getDefaultView())
	, mWorldBounds(0.f,0.f,mWorldView.getSize().x, mWorldView.getSize().y)
	//, mSpawnPosition(mWorldView.getSize().x/2.f,mWorldView.getSize().y/2.f)
	, mSpawnPosition(mWindow.getSize().x/2,mWindow.getSize().y/2)
	
	, mBackground()
	, mMap("Media/Maps")
	, mCoins()
	, mEnemiesManager()
	, mStar()
	, mPlayer(mMap,mCoins, mEnemiesManager, mStar)
	, mMapName(mapName)
{
	
	loadTextures();
	builtScene();
	mEnemiesManager.setPlayer(mPlayer);
	//mWorldView.setCenter(mSpawnPosition);
}

void World::loadTextures()
{
	mTextures.load(Textures::Player,"Media/Sprites/jetx.png");
//	mTextures.load(Textures::Background1,"Media/bg1.png");
	mTextures.load(Textures::Background2,"Media/bg2.png");
	mTextures.load(Textures::Coin,"Media/Pickups/coin.png");
	mTextures.load(Textures::Bug,"Media/Sprites/bug.png");
	mTextures.load(Textures::Firebug,"Media/Sprites/firebug.png");
	mTextures.load(Textures::Bat,"Media/Sprites/bat.png");
	mTextures.get(Textures::Bat).setSmooth(true);
	mTextures.load(Textures::Star,"Media/Pickups/star.png");
	mMap.Load(mMapName);
	
	////
	mTextures.load(Textures::Background1,"Media/sky.png");
}

void World::builtScene()
{
	for(auto& layer : mMap.GetLayers())
		if(layer.name=="Entities")
			for(auto& object : layer.objects)
				if(object.GetName()=="Player")
				{
					
					mSpawnPosition = sf::Vector2f(object.GetPosition().x,object.GetPosition().y+object.GetAABB().height);
					break;
				}

	mCoins.initialize(mMap);
	mCoins.loadTexture(mTextures.get(Textures::Coin));

	mStar.initialize(mMap);
	mStar.loadTexture(mTextures.get(Textures::Star));
	//mWorldView.setCenter(mWorldView.getSize().x/2,mWorldView.getSize().y/2);

	mWorldView.move(-mWorldView.getSize().x/2,0.f);
	mPlayer.loadTexture(mTextures);
	mPlayer.setPosition(mSpawnPosition);
	mPlayer.setVelocity(10.0f,330.0f);

	mEnemiesManager.initialize(mMap);
	mEnemiesManager.loadTexture(mTextures);
	//mTextures.get(Textures::Background1).setSmooth(true);
	//mTextures.get(Textures::Background1).setRepeated(true);
	mBackground.setTexture(mTextures.get(Textures::Background1));

	

	//mBackground.setScale(2.1,1.6);
	//mBackground.setScale(768.0f/mBackground.getLocalBounds().height,768.0f/mBackground.getLocalBounds().height);
	mBackground.setScale(1344.0f/mBackground.getLocalBounds().width,768.0f/mBackground.getLocalBounds().height);

}

void World::draw()
{
	mWindow.setView(mWorldView);
	//mWindow.draw(mBackground);
	
	mWindow.draw(mMap);
	mCoins.draw(mWindow,sf::RenderStates::Default);
	mWindow.draw(mStar);
	mWindow.draw(mEnemiesManager);
	mWindow.draw(mPlayer);
	for(auto& layer : mMap.GetLayers())
		if(layer.name=="Foreground")
			mWindow.draw(layer);
			
	mWindow.setView(mWindow.getDefaultView());
	sf::RectangleShape rect(sf::Vector2f(1344, 768));
	rect.setFillColor(sf::Color(12,21,137,130));
	//mWindow.draw(rect);
}

void World::update(sf::Time dt)
{
	mPlayer.handleRealtimeInput(dt);

	mPlayer.update(dt);
	mCoins.update(dt);
	mEnemiesManager.update(dt);

	/*static sf::Vector2f previousPlayerPos(0,0);
	sf::Vector2f playerPosChange =mPlayer.getPlayerPosition()-previousPlayerPos;
	previousPlayerPos=mPlayer.getPlayerPosition();
	mWorldView.move(playerPosChange.x,0);*/
	sf::Vector2f center=mWorldView.getCenter();
	mWorldView.setCenter(mPlayer.getPosition().x,mWorldView.getCenter().y);
	if(mWorldView.getCenter().x < mWorldView.getSize().x/2)
		mWorldView.setCenter(mWorldView.getSize().x/2, mWorldView.getCenter().y);
	if(mWorldView.getCenter().x+mWorldView.getSize().x/2 > mMap.GetMapSize().x)
		mWorldView.setCenter(center.x,mWorldView.getCenter().y);
}

void World::handleEvent(sf::Event e)
{

}

bool World::isLevelCompleted()
{ return mPlayer.isLevelCompleted();}
bool World::isPlayerDead()
{ return mPlayer.isPlayerDead(); }
int World::getPoints()
{
	return mCoins.getPoints();
}

int World::getMaxPoints()
{
	return mCoins.getMaxPoints();
}
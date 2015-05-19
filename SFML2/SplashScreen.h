#pragma once
#include "GameState.h"
#include "ResourceHolder.h"

class SplashScreen :
	public GameState
{
private:
	sf::RenderWindow& mWindow;
	TextureHolder mTextures;
	sf::Sprite mSprite;
public:
	SplashScreen(sf::RenderWindow& window);
	~SplashScreen(void);

	virtual void update(sf::Time dt){};
	virtual void draw();
	virtual void handleEvent(sf::Event e);
};


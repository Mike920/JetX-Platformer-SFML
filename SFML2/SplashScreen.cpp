#include "SplashScreen.h"
#include "Game.h"

SplashScreen::SplashScreen(sf::RenderWindow& window)
	: mWindow(window)
{
	mTextures.load(Textures::SplashScreen,"Media/Textures/splashscreen.png");
	mSprite.setTexture(mTextures.get(Textures::SplashScreen));
//	mSprite.setPosition(mWindow.getSize().x/2,mWindow.getSize().y/2);
	//mSprite.move(-mSprite.getLocalBounds().left/2,-mSprite.getLocalBounds().top/2);
}


SplashScreen::~SplashScreen(void)
{
}

void SplashScreen::draw()
{
//	mWindow.clear(sf::Color::Black);
	mWindow.draw(mSprite);
}

void SplashScreen::handleEvent(sf::Event e)
{
	if(e.type == sf::Event::KeyPressed)
		Game::changeState(GameStates::Menu);
}
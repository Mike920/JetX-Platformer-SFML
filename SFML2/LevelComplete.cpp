#include "LevelComplete.h"


LevelComplete::LevelComplete(sf::RenderWindow& window, PlayingState& playing)
	: mWindow(window)
	, mPlayingState(playing)
{

	levelcomplete.loadFromFile("Media/Textures/levelcomplete.png");

		mSprite.setTexture(levelcomplete);

	mSprite.setOrigin(mSprite.getLocalBounds().width/2,mSprite.getLocalBounds().height/2);
	mSprite.setPosition(mWindow.getDefaultView().getCenter());
}


LevelComplete::~LevelComplete(void)
{
}

void LevelComplete::draw()
{
	mWindow.draw(mSprite);
}
void LevelComplete::handleEvent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		if(mPlayingState.getCurrentLvl()>4)
			Game::changeState(GameStates::Menu);
		else
			mPlayingState.nextlvl();
	}
}
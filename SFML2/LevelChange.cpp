#include "LevelChange.h"


LevelChange::LevelChange(sf::RenderWindow& window, PlayingState& playing)
	: mWindow(window)
	, mPlayingState(playing)
{
	tryagain.loadFromFile("Media/Textures/tryagain.png");
	
		mSprite.setTexture(tryagain);


	mSprite.setOrigin(mSprite.getLocalBounds().width/2,mSprite.getLocalBounds().height/2);
	mSprite.setPosition(mWindow.getDefaultView().getCenter());
}


LevelChange::~LevelChange(void)
{
}

void LevelChange::draw()
{
	mWindow.draw(mSprite);
}
void LevelChange::handleEvent(sf::Event e)
{
	if (e.type == sf::Event::KeyPressed)
		mPlayingState.changeLevel(mPlayingState.getCurrentLvl());
	
}
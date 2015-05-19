#include "PlayingState.h"


PlayingState::PlayingState(sf::RenderWindow& window)
	: mWindow(window)
{

	mCurrentLvl=0;
	mLevel=NULL;

	mLevels.push_back("level1.tmx");
	mLevels.push_back("level2.tmx");
	mLevels.push_back("level3.tmx");
	mLevels.push_back("level4.tmx");
	
	font.loadFromFile("Media/Fonts/apple.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.move(30,30);
}


PlayingState::~PlayingState(void)
{
	if(mLevel!=NULL)
		delete mLevel;
}

void PlayingState::changeLevel(int level)
{
	if(mLevel!=NULL)
		delete mLevel;
	mLevel = new  World(mWindow,mLevels[level-1]);
	mCurrentLvl=level;
	Game::changeState(GameStates::Playing);

}

void PlayingState::nextlvl()
{
	
  if((mCurrentLvl+1)>mLevels.size())
		{
			Game::changeState(GameStates::Menu);
			return;
	}
	if(mLevel!=NULL)
		delete mLevel;
	mCurrentLvl++;
	mLevel = new  World(mWindow,mLevels[mCurrentLvl-1]);

	Game::changeState(GameStates::Playing);

}

int PlayingState::getCurrentLvl()
{ return mCurrentLvl;}

void PlayingState::update(sf::Time dt)
{
	mLevel->update(dt);

	if(mLevel->isLevelCompleted())
		Game::changeState(GameStates::LevelComplete);
	if(mLevel->isPlayerDead())
	{
		time += dt;
		if(time>sf::seconds(2.0))
		{
			time=sf::Time();
			Game::changeState(GameStates::LevelChange);
		}
	}
	ss.str("");
	ss<<"Coins: "<<mLevel->getPoints()<<"/"<<mLevel->getMaxPoints();
	text.setString(ss.str());

}

void PlayingState::draw()
{
	mLevel->draw();
	mWindow.draw(text);
}
void PlayingState::handleEvent(sf::Event e)
{
	mLevel->handleEvent(e);

	if (e.type == sf::Event::KeyPressed)
	{
		if (e.key.code == sf::Keyboard::Escape)
			Game::changeState(GameStates::Paused);
	}
}
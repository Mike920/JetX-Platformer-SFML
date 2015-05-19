#pragma once
#include "GameState.h"
#include "World.h"
#include <tmx\MapLoader.h>
#include <vector>
#include "Game.h"
#include <sstream>

class World;

class PlayingState : public GameState
{
private:
	stringstream ss;
	sf::Font font;
	sf::Text text;
	World* mLevel;
	vector<string> mLevels;
	int mCurrentLvl;
	sf::RenderWindow& mWindow;
	sf::Time time;
public:
	PlayingState(sf::RenderWindow& window);
	virtual ~PlayingState(void);

	virtual void update(sf::Time dt);
	virtual void draw();
	virtual void handleEvent(sf::Event e);

	void changeLevel(int level);
	void nextlvl();
	int getCurrentLvl();
};


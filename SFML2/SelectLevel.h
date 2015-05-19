#pragma once
#include "GameState.h"
#include "PlayingState.h"
#include "Game.h"
#include <sstream>

class PlayingState;

class SelectLevel : public GameState
{
private:
	PlayingState& mPlayingState;
	sf::RenderWindow& mWindow;
	sf::Font mFont;
	std::vector<sf::Text> mOptions;
	int mOptionIndex;
public:
	SelectLevel(sf::RenderWindow& window, PlayingState& playing);
	~SelectLevel(void);

	virtual void update(sf::Time dt);
	virtual void draw();
	virtual void handleEvent(sf::Event e);

	void updateText();
};


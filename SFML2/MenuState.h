#pragma once
#include "GameState.h"
#include "PlayingState.h"
#include "Game.h"

class PlayingState;

class MenuState : public GameState
{
private:
	PlayingState& mPlayingState;
	sf::RenderWindow& mWindow;
	sf::Font mFont;
	std::vector<sf::Text> mOptions;
	int mOptionIndex;
public:
	MenuState(sf::RenderWindow& window, PlayingState& playing);
	~MenuState(void);

	virtual void update(sf::Time dt);
	virtual void draw();
	virtual void handleEvent(sf::Event e);

	void updateText();
};


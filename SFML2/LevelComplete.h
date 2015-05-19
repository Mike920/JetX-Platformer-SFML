#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "PlayingState.h"

class LevelComplete :
	public GameState
{
private:
	sf::RenderWindow& mWindow;
	PlayingState& mPlayingState;
	sf::Texture levelcomplete;
	sf::Sprite mSprite;
	bool defeat;
public:
	LevelComplete(sf::RenderWindow& window, PlayingState& playing);
	~LevelComplete(void);

	virtual void update(sf::Time dt){};
	virtual void draw();
	virtual void handleEvent(sf::Event e);
};


#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "PlayingState.h"

class LevelChange :
	public GameState
{
private:
	sf::RenderWindow& mWindow;
	PlayingState& mPlayingState;
	sf::Texture tryagain;

	sf::Sprite mSprite;
	bool defeat;
public:
	LevelChange(sf::RenderWindow& window, PlayingState& playing);
	~LevelChange(void);

	virtual void update(sf::Time dt){};
	virtual void draw();
	virtual void handleEvent(sf::Event e);
};


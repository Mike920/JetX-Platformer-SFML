#pragma once
#include <SFML\System\Time.hpp>
#include <SFML\Window\Event.hpp>
#include <SFML\System.hpp>
//#include "Game.h"

//class Game;

class GameState
{

public:
	GameState(void);
	virtual ~GameState(void);

	virtual void update(sf::Time dt)=0;
	virtual void draw()=0;
	virtual void handleEvent(sf::Event e)=0;
};


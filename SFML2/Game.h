#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "ResourceHolder.h"
#include "World.h"
#include "HelperClass.h"
#include "GameState.h"
#include "PlayingState.h"
#include "SplashScreen.h"
#include "MenuState.h"
#include "SelectLevel.h"
#include "PauseState.h"
#include "LevelComplete.h"
#include "LevelChange.h"
#include <map>

class World;

class GameState;

 enum class GameStates
{
	Menu, Paused, Playing, Exit, SplashScreen, SelectLevel, LevelChange, Defeat, LevelComplete
};

class Game 
{
public:
	Game();
	void Run();
	static void changeState(GameStates state); 
	
private:
	sf::RenderWindow mWindow;
//	World	mWorld;

	map<GameStates,unique_ptr<GameState>> mStates;
	
	static GameStates currentState;
	static const sf::Time TimePerFrame;
	sf::Font mFont;
	sf::Text debugInfo;

	void processInput();
	void update(sf::Time deltaTime);
	void render(void);
	

	void DrawMap();
};


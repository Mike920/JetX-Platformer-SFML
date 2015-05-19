#include "Game.h"


const sf::Time Game::TimePerFrame=sf::seconds(1.f/60.f);
GameStates Game::currentState=GameStates::SplashScreen; //GameStates::SplashScreen;


Game::Game()
	: mWindow(sf::VideoMode(1344,768),"Simple App",sf::Style::Fullscreen)
//	, mWorld(mWindow)

{
	mWindow.setKeyRepeatEnabled(false);

	unique_ptr<PlayingState> playerSt(new PlayingState(mWindow));
	//playerSt->changeLevel("level1.tmx");
	unique_ptr<MenuState> menu(new MenuState(mWindow,*playerSt.get()));
	mStates[GameStates::Menu]=move(menu);
	unique_ptr<SelectLevel> lev(new SelectLevel(mWindow,*playerSt.get()));
	unique_ptr<LevelComplete> comp(new LevelComplete(mWindow,*playerSt.get()));
	mStates[GameStates::LevelComplete]=move(comp);
	unique_ptr<LevelChange> chng(new LevelChange(mWindow,*playerSt.get()));
	mStates[GameStates::LevelChange]=move(chng);
	mStates[GameStates::SelectLevel]=move(lev);
	mStates[GameStates::Playing]=move(playerSt);
	unique_ptr<SplashScreen> splash(new SplashScreen(mWindow));
	mStates[GameStates::SplashScreen]=move(splash);
	unique_ptr<PauseState> pause(new PauseState(mWindow));
	mStates[GameStates::Paused]=move(pause);





	mFont.loadFromFile("Media/Fonts/Raleway.ttf");
	debugInfo.setFont(mFont);
	debugInfo.setCharacterSize(20);
	debugInfo.setPosition(0,200);
}


void Game::Run()
{
	sf::Clock clock;
	sf::Clock FPSclock;
	int FPS=0; int UPS=0;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while(mWindow.isOpen())
	{
		//Time that has elapsed between the last frame
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate+=elapsedTime;
		while(timeSinceLastUpdate>TimePerFrame)
		{
			timeSinceLastUpdate-=TimePerFrame;

			processInput();
			update(TimePerFrame);
			UPS++;
		}
		render();
		FPS++;
		if(FPSclock.getElapsedTime().asSeconds()>=1)
		{
			FPSclock.restart();
			debugInfo.setString("FPS: "+HelperClass::IntToString(FPS)+"\nUPS: "+HelperClass::IntToString(UPS));
			FPS=0; UPS=0;
		}
	}
}

void Game::render(void)
{
	mWindow.clear(sf::Color(85,180,255));
	//////////////////////////////////
	mStates[currentState]->draw();
	//mWorld.draw();

	mWindow.setView(mWindow.getDefaultView());
	//mWindow.draw(debugInfo);
	/////////////////////////////////
	mWindow.display();
}

void Game::processInput()
{
	sf::Event event;
	while(mWindow.pollEvent(event))
	{
		mStates[currentState]->handleEvent(event);
		//mWorld.handleEvent(event);

		if(event.type==sf::Event::Closed)
			mWindow.close();
	}

}


void Game::update(sf::Time elapsedTime)
{
	mStates[currentState]->update(elapsedTime);
	//mWorld.update(elapsedTime);
}

void Game::changeState(GameStates state) 
{
	currentState=state;
}
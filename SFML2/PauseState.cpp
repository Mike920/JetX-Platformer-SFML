#include "PauseState.h"


PauseState::PauseState(sf::RenderWindow& window)
	: mWindow(window)
	, mOptionIndex(0)
	
{
	mFont.loadFromFile("Media/Fonts/grobold.ttf");

	sf::Text play;
	play.setFont(mFont);
	play.setString("Resume");
	play.setCharacterSize(50);
	play.setOrigin(play.getLocalBounds().width/2,play.getLocalBounds().height/2);
	play.setPosition(mWindow.getDefaultView().getCenter());
	mOptions.push_back(play);

	sf::Text exit;
	exit.setFont(mFont);
	exit.setString("Return to menu");
	exit.setCharacterSize(50);
	exit.setOrigin(exit.getLocalBounds().width/2,exit.getLocalBounds().height/2);
	exit.setPosition(mWindow.getDefaultView().getCenter());
	exit.move(0,exit.getLocalBounds().height+20);
	mOptions.push_back(exit);

	updateText();
}

PauseState::~PauseState(void){}


void PauseState::update(sf::Time dt){}

void PauseState::updateText()
{
	for(auto& text : mOptions)
		text.setColor(sf::Color::White);

	mOptions[mOptionIndex].setColor(sf::Color::Blue);
}

void PauseState::draw()
{
	mWindow.setView(mWindow.getDefaultView());

	for(auto& text : mOptions)
		mWindow.draw(text);
}

void PauseState::handleEvent(sf::Event e)
{
	if (e.type != sf::Event::KeyPressed)
		return;

	if (e.key.code == sf::Keyboard::Up)
{
    if (mOptionIndex > 0)
        mOptionIndex--;
    else
        mOptionIndex = mOptions.size() - 1;
    updateText();
}
else if (e.key.code == sf::Keyboard::Down)
{
    if (mOptionIndex < mOptions.size() - 1)
        mOptionIndex++;
    else
        mOptionIndex = 0;
    updateText();
}

if (e.key.code == sf::Keyboard::Escape)
	Game::changeState(GameStates::Playing);

if (e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Space)
{
    if (mOptions[mOptionIndex].getString() == "Resume")
    {
		Game::changeState(GameStates::Playing);
    }
	else if (mOptions[mOptionIndex].getString() == "Return to menu")
    {
		Game::changeState(GameStates::Menu);
    }
}

}
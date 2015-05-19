#include "SelectLevel.h"


SelectLevel::SelectLevel(sf::RenderWindow& window, PlayingState& playing)
	: mPlayingState(playing)
	, mWindow(window)
	, mOptionIndex(0)
	
{
	mFont.loadFromFile("Media/Fonts/grobold.ttf");

	for(int i=0;i<4;i++)
	{
		std::stringstream ss;
		ss<<"Level "<<(i+1);
		sf::Text play;
		play.setFont(mFont);
		play.setString(ss.str());
		play.setCharacterSize(50);
		play.setOrigin(play.getLocalBounds().width/2,play.getLocalBounds().height/2);
		play.setPosition(mWindow.getDefaultView().getCenter().x,mWindow.getDefaultView().getCenter().y/2);
		play.move(0,play.getLocalBounds().height*i+20);
		mOptions.push_back(play);
	}
	updateText();
}

SelectLevel::~SelectLevel(void){}


void SelectLevel::update(sf::Time dt){}

void SelectLevel::updateText()
{
	for(auto& text : mOptions)
		text.setColor(sf::Color::White);

	mOptions[mOptionIndex].setColor(sf::Color::Blue);
}

void SelectLevel::draw()
{
	mWindow.setView(mWindow.getDefaultView());

	for(auto& text : mOptions)
		mWindow.draw(text);
}

void SelectLevel::handleEvent(sf::Event e)
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
	Game::changeState(GameStates::Menu);

if (e.key.code == sf::Keyboard::Return || e.key.code == sf::Keyboard::Space)
{

    if (mOptions[mOptionIndex].getString() == "Level 1")
    {
		mPlayingState.changeLevel(1);
    }
	else  if (mOptions[mOptionIndex].getString() == "Level 2")
    {
		mPlayingState.changeLevel(2);
    }
	else  if (mOptions[mOptionIndex].getString() == "Level 3")
    {
		mPlayingState.changeLevel(3);
    }
	else  if (mOptions[mOptionIndex].getString() == "Level 4")
    {
		mPlayingState.changeLevel(4);
    }

}

}
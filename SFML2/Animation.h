#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

class Animation
{
private:

	sf::Time mMaxDuration;
	sf::Clock mCurrentTime;
	std::vector<sf::IntRect> mFrames;

	bool mIsRepeatable;
	
	int mleftMargin;
	int mRightMargin;
	int mTopMargin;
	int mBottomMargin;

public:
	Animation(){};
	Animation(sf::Time duration) : mMaxDuration(duration), mleftMargin(0),mRightMargin(0),mTopMargin(0), mBottomMargin(0), mIsRepeatable(true) {};
	~Animation(void);

	void setMargins(int leftMargin,int RightMargin,int TopMargin,int BottomMargin);
	int getMargin(std::string);
	void addFrame(sf::IntRect frameRect);
	int getFramesCount();
	void isRepeatable(bool repeat);
	bool isRepeatable();
	sf::Time getMaxDuration();
	sf::IntRect& getFrameRect(int number);
	sf::IntRect& getFrameRectNoMargin(int number);
};


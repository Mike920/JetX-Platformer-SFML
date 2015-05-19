#include "Animation.h"

Animation::~Animation(void)
{
}

void Animation::addFrame(sf::IntRect frameRect)
{
	frameRect.left+=mleftMargin;
	frameRect.top+=mTopMargin;
	frameRect.width-=(mRightMargin+mleftMargin);
	frameRect.height-=(mBottomMargin+mTopMargin);
	mFrames.push_back(frameRect);
}



void Animation::setMargins(int leftMargin,int RightMargin,int TopMargin,int BottomMargin)
{
	mleftMargin=leftMargin;
	mRightMargin=RightMargin;
	mTopMargin=TopMargin;
	mBottomMargin=BottomMargin;
}

int Animation::getFramesCount()
{
	return mFrames.size();
}

sf::Time Animation::getMaxDuration()
{
	return mMaxDuration;
}

sf::IntRect& Animation::getFrameRect(int number)
{
	return mFrames[number];
}

sf::IntRect& Animation::getFrameRectNoMargin(int number)
{
	sf::IntRect frameRect =mFrames[number];
	frameRect.left-=mleftMargin;
	frameRect.top-=mTopMargin;
	frameRect.width+=(mRightMargin+mleftMargin);
	frameRect.height+=(mBottomMargin+mTopMargin);

	return frameRect;
}

int Animation::getMargin(std::string side)
{
	if(side=="left")
		return mleftMargin;
	else if (side=="right")
		return mRightMargin;
	else if(side=="top")
		return mTopMargin;
	else if(side=="bottom")
		return mBottomMargin;

}

void Animation::isRepeatable(bool repeat)
{
	mIsRepeatable=repeat;
}
bool Animation::isRepeatable()
{
	return mIsRepeatable;
}
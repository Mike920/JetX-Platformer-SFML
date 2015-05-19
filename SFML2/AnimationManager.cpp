#include "AnimationManager.h"


AnimationManager::AnimationManager(void)
	: mStopped(false)
	, mReversed(false)
	, mSprite()
{
	//mSprite.setOrigin(0,mSprite.getLocalBounds().height);
}


AnimationManager::~AnimationManager(void)
{
}

void AnimationManager::setTexture(const sf::Texture& texture)
{
	//mTexture=&texture;
	mSprite.setTexture(texture);
}

void AnimationManager::addAnimation(std::string name, Animation animation)
{
	mAnimations[name]=animation;
}

void AnimationManager::playAnimation(std::string name)
{
	mStopped=false;
	if(mCurrentAnimation!=name)
	{
		mMaxDuration=mAnimations[name].getMaxDuration();
		mOneFrameDuration=mAnimations[name].getMaxDuration().asSeconds()/mAnimations[name].getFramesCount();
		mCurrentFrame=1;
		mCurrentAnimation=name;
		mElapsedTime=sf::Time();

	}

}

void AnimationManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	target.draw(mSprite,states);
}

void AnimationManager::update(sf::Time dt)
{
	if(!mStopped)
	{
		mElapsedTime+=dt;
		if(mElapsedTime.asSeconds() > mOneFrameDuration*mCurrentFrame)
			if( mCurrentFrame+1 >mAnimations[mCurrentAnimation].getFramesCount() )
			{
				if(mAnimations[mCurrentAnimation].isRepeatable())
				{
					mCurrentFrame=1;
					mElapsedTime=sf::Time();
				}

			}
			else
				mCurrentFrame++;
	}
	if(mCurrentAnimation=="jump" || mCurrentAnimation=="fall")
		mReversed=!mReversed;

	if(!mReversed)
		mSprite.setTextureRect(mAnimations[mCurrentAnimation].getFrameRect(mCurrentFrame-1));
	else
	{

		sf::IntRect r=mAnimations[mCurrentAnimation].getFrameRectNoMargin(mCurrentFrame-1);
		Animation* a=&mAnimations[mCurrentAnimation];
		mSprite.setTextureRect(sf::IntRect(
			r.left + r.width - a->getMargin("left")
			,r.top - a->getMargin("top")
			,-r.width + a->getMargin("right") + a->getMargin("left")
			,r.height -( a->getMargin("top") + a->getMargin("bottom")) ));
	}
	
	if(mCurrentAnimation=="jump" || mCurrentAnimation=="fall")
		mReversed=!mReversed;

}

void AnimationManager::stopAnimation()
{
	mCurrentFrame=1;
	mStopped=true;
}
void AnimationManager::reverseSprite(bool r)
{
	mReversed=r;
}

sf::FloatRect AnimationManager::getLocalBounds()
{
	return mSprite.getLocalBounds();
}

sf::FloatRect AnimationManager::getGlobalBounds()
{
	return mSprite.getGlobalBounds();
}

std::string AnimationManager::getCurrentAnimation()
{
	return mCurrentAnimation;
}

void AnimationManager::setPosition(sf::Vector2f pos)
{
	mSprite.setPosition(pos);
}

sf::Sprite& AnimationManager::getSprite()
{
	return mSprite;
}
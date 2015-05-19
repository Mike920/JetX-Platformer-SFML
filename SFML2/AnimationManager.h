#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include <map>
#include <string>

class AnimationManager
{
private:
	sf::Sprite mSprite;

	std::string mCurrentAnimation;

	sf::Time mElapsedTime;
	sf::Time mMaxDuration;
	float mOneFrameDuration;
	int mCurrentFrame;

	bool mReversed;
	bool mStopped;


	std::map<std::string,Animation> mAnimations;

public:
	AnimationManager(void);
	~AnimationManager(void);

	void update(sf::Time dt);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	sf::FloatRect getLocalBounds();
	sf::FloatRect getGlobalBounds();
	void setPosition(sf::Vector2f pos);
	std::string getCurrentAnimation();

	void addAnimation(std::string name, Animation animation);
	void playAnimation(std::string name);
	void reverseSprite(bool r);
	void stopAnimation();

	void setTexture(const sf::Texture& texture);

	sf::Sprite& getSprite();


};


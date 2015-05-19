#include "Player.h"



Player::Player(tmx::MapLoader& map, Coins& coins, EnemiesManager& enemyManager, Star& star)
	: mSpriteSize(48,48)
	, mIsJumping(false)
	, mFrictionStart(0.95)
	, mFrictionStop(0.8)
	, mFrictionVertical(5)
	, mIsMovingLeft(false)
	, mIsMovingRight(false)
	, mCollisionLeft(false)
	, mCollisionRight(false)
	, mCollisionUp(false)
	, mCollisionDown(false)
	, mPlayerDead(false)
	, mLevelCompleted(false)
	, mCollMarg(6)
	, mAnimation()
{
	mMap=&map;
	mCoins = &coins;
	mEnemyManager = &enemyManager;
	mStar = &star;
	mFont.loadFromFile("Media/Fonts/Raleway.ttf");
	
	mleftMargin = 8;
	mRightMargin = 8;
	mTopMargin = 0;
	mBottomMargin = 5;

	Animation right(sf::seconds(1.0f));
	right.setMargins(mleftMargin,mRightMargin,mTopMargin,mBottomMargin);
	for(int i=0;i<7;i++)
		right.addFrame(sf::IntRect(mSpriteSize.y*i, mSpriteSize.y*5, mSpriteSize.x,mSpriteSize.y));
	mAnimation.addAnimation("right",right);

	Animation stay(sf::seconds(3.0f));
	stay.setMargins(mleftMargin,mRightMargin,mTopMargin,mBottomMargin);
	for(int i=0;i<4;i++)
		stay.addFrame(sf::IntRect(mSpriteSize.y*i, mSpriteSize.y*2, mSpriteSize.x,mSpriteSize.y));
	mAnimation.addAnimation("stay",stay);

	Animation jump(sf::seconds(1.0f));
	jump.setMargins(mleftMargin,mRightMargin,mTopMargin,mBottomMargin);
	for(int i=0;i<6;i++)
		jump.addFrame(sf::IntRect(mSpriteSize.y*i, mSpriteSize.y*7, mSpriteSize.x,mSpriteSize.y));
	jump.isRepeatable(false);
	mAnimation.addAnimation("jump",jump);

	Animation fall(sf::seconds(1.0f));
	fall.setMargins(mleftMargin,mRightMargin,mTopMargin,mBottomMargin);
	for(int i=3;i<6;i++)
		fall.addFrame(sf::IntRect(mSpriteSize.y*i, mSpriteSize.y*7, mSpriteSize.x,mSpriteSize.y));
	fall.isRepeatable(false);
	mAnimation.addAnimation("fall",fall);

	Animation dead(sf::seconds(1.0f));
	dead.setMargins(mleftMargin,mRightMargin,mTopMargin,mBottomMargin+7);
	for(int i=0;i<3;i++)
		dead.addFrame(sf::IntRect(mSpriteSize.y*i, mSpriteSize.y*8, mSpriteSize.x,mSpriteSize.y));
	
	mAnimation.addAnimation("dead",dead);

	mAnimation.playAnimation("stay");


}
Player::~Player(void)
{
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
	
	states.transform *= getTransform();

	mAnimation.draw(target,states);

}

void Player::loadTexture(const TextureHolder& textures)
{
	mAnimation.setTexture(textures.get(Textures::Player));

	setOrigin(0,mSpriteSize.y);


}

void Player::handleRealtimeInput(sf::Time dt)
{
	if (mPlayerDead)
		return;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mAnimation.reverseSprite(true);
		//if(mAnimation.getCurrentAnimation()!="jump")
		if(!mIsJumping)
			mAnimation.playAnimation("right");
		mIsMovingLeft=true;
		mMovement.x-=getVelocity().x;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mAnimation.reverseSprite(false);
		//if(mAnimation.getCurrentAnimation()!="jump")
		if(!mIsJumping)
			mAnimation.playAnimation("right");
		mIsMovingRight=true;
		mMovement.x+=getVelocity().x;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&!mIsJumping)
	{
		mIsJumping=true;
		mAnimation.playAnimation("jump");
		mMovement.y-=getVelocity().y;
	}


}

void Player::update(sf::Time dt)
{


	if(mIsMovingLeft || mIsMovingRight || mIsJumping)
		mMovement.x*=mFrictionStart;
	else
		mMovement.x*=mFrictionStop;

	if(mIsJumping)
		mMovement.y+=mFrictionVertical;

 
	
	sf::FloatRect playerRect = getTransform().transformRect(mAnimation.getGlobalBounds());
	playerRect.left+=mMovement.x*dt.asSeconds();
	playerRect.top+=mMovement.y*dt.asSeconds();

	// Update player's collision points
	mCollPoints.up[0]=sf::Vector2f(playerRect.left+mCollMarg,playerRect.top);
	mCollPoints.up[1]=sf::Vector2f(playerRect.left+playerRect.width-mCollMarg,playerRect.top);
	mCollPoints.down[0]=sf::Vector2f(playerRect.left+mCollMarg,playerRect.top+playerRect.height);
	mCollPoints.down[1]=sf::Vector2f(playerRect.left+playerRect.width-mCollMarg,playerRect.top+playerRect.height);
	mCollPoints.left[0]=sf::Vector2f(playerRect.left,playerRect.top+mCollMarg);
	mCollPoints.left[1]=sf::Vector2f(playerRect.left,playerRect.top+playerRect.height-mCollMarg);
	mCollPoints.left[2]=sf::Vector2f(playerRect.left,playerRect.top+playerRect.height/2);
	mCollPoints.right[0]=sf::Vector2f(playerRect.left+playerRect.width,playerRect.top+mCollMarg);
	mCollPoints.right[1]=sf::Vector2f(playerRect.left+playerRect.width,playerRect.top+playerRect.height-mCollMarg);
	mCollPoints.right[2]=sf::Vector2f(playerRect.left+playerRect.width,playerRect.top+playerRect.height/2);

	//Collision detection
	collisionDetection(playerRect);
	pickupCollisionDetection(playerRect);



	if(mCollisionRight)
		if(mMovement.x>0)
			mMovement.x*=-0.1f;
			
	if(mCollisionLeft)
		if(mMovement.x<0)
			mMovement.x*=-0.1f;

	if(mCollisionUp)
		if(mMovement.y<0)
			mMovement.y*=-0.1f;

	if(mCollisionDown)
	{
		if(!(mIsMovingLeft || mIsMovingRight || mPlayerDead))
			mAnimation.playAnimation("stay");
		if(mMovement.y>0)
		//	mMovement.y*=-0.1f;
			mMovement.y=0;

		mIsJumping=false;
	}
	else
	{
		/*if(mAnimation.getCurrentAnimation()!="jump")
			mAnimation.playAnimation("fall");*/
		mIsJumping=true;
		mMovement.y+=getGravity();
	}


	
	mAnimation.update(dt);

	move(mMovement*dt.asSeconds());

	if(mEnemyManager->intersection(getAABB()))
	{
			mPlayerDead=true;
			mAnimation.playAnimation("dead");
	}

	if(mStar->getGlobalBounds().intersects(getAABB()))
		mLevelCompleted=true;

	//ss.str("");
	//ss << "Left: "<<(int)mCollisionLeft<< "\nRight: "<<(int)mCollisionRight<<"\nUp: "<<(int)mCollisionUp<<"\nDown: "<<(int)mCollisionDown;// put float into string buffer
	
	//Reset variables

	mIsMovingLeft=false;
	mIsMovingRight=false;

	mCollisionDown=false;
	mCollisionLeft=false;
	mCollisionRight=false;
	mCollisionUp=false; 
	
}

void Player::collisionDetection(sf::FloatRect& playerRect)
{
	for(auto& layer : mMap->GetLayers())
		if(layer.name=="Collision")
			for(auto& object : layer.objects)
			{
				sf::FloatRect rect = object.GetAABB();
				
				// If colliding
				if(!( playerRect.left > rect.left+rect.width || playerRect.left+playerRect.width < rect.left || 
					  playerRect.top > rect.top+rect.height  || playerRect.top+playerRect.height < rect.top ))
				{
					if( rect.contains(mCollPoints.right[0]) || rect.contains(mCollPoints.right[1]) || rect.contains(mCollPoints.right[2]))
						mCollisionRight=true;
					else if 
						( rect.contains(mCollPoints.left[0]) || rect.contains(mCollPoints.left[1]) || rect.contains(mCollPoints.left[2]))
						mCollisionLeft=true;

					if( rect.contains(mCollPoints.up[0]) || rect.contains(mCollPoints.up[1]))
						mCollisionUp=true;
					else if
						( rect.contains(mCollPoints.down[0]) || rect.contains(mCollPoints.down[1]))
					  mCollisionDown=true;

				}
			}
		else if (layer.name=="Springboard")
		{
				for(auto& object : layer.objects)
					if( object.Contains(mCollPoints.down[0]) || object.Contains(mCollPoints.down[1]) )
					{
						mIsJumping=true;
						mAnimation.playAnimation("jump");
						mMovement.y-=getVelocity().y*2.3;
					}
		}
		
		if (playerRect.top>767)
			mPlayerDead=true;


}

void Player::pickupCollisionDetection(sf::FloatRect& playerRect)
{
	for(int i=0; i<mCoins->getObjectsVector().size();i++)
		if(mCoins->getObjectsVector()[i].intersects(playerRect))
		{
			mCoins->incrementPoints();
			mCoins->getObjectsVector().erase(mCoins->getObjectsVector().begin()+i);
		}
		
}

sf::Vector2f Player::getPlayerPosition()
{
	sf::FloatRect f= getTransform().transformRect(mAnimation.getGlobalBounds());
	return sf::Vector2f(f.left+f.width/2,f.top+f.height/2);
}

sf::FloatRect Player::getAABB()
{
	return sf::FloatRect(getPosition().x, getPosition().y-mAnimation.getLocalBounds().height, mAnimation.getLocalBounds().width, mAnimation.getLocalBounds().height);
}


bool Player::isLevelCompleted()
{ return mLevelCompleted;}
bool Player::isPlayerDead()
{ return mPlayerDead; }
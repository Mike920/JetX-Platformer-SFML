#include "EnemiesManager.h"


EnemiesManager::EnemiesManager(void)
{
}


EnemiesManager::~EnemiesManager(void)
{
	for(auto& enemy : mEnemiesContainer)
		delete enemy;
}

void EnemiesManager::initialize(tmx::MapLoader& map)
{
	for(auto& layer : map.GetLayers())
		if(layer.name=="Bugs")
			for(auto& object : layer.objects)
			{
				Bug* bug = new Bug();
				// We use the lower-left corner coords of the object on the tilemap to set the enemy position
				sf::Vector2f pos(object.GetPosition().x, object.GetPosition().y+object.GetAABB().height - bug->getSpriteSize().y);
				bug->setPosition(pos); 
				Enemy::MovementScope mscope;
				try{
				mscope.left = std::stoi(object.GetPropertyString("left")); 
				mscope.right = std::stoi(object.GetPropertyString("right")); 
				}
				catch (std::exception& e)
				{
					std::cout << "\nEXCEPTION ( Bug properties not set corectly): " << e.what() << std::endl;
				}
				bug->setMovementScope(mscope);
				mEnemiesContainer.push_back(bug);
			}
		else if(layer.name=="Firebugs")
			for(auto& object : layer.objects)
			{
				Firebug* bug = new Firebug();
				// We use the lower-left corner coords of the object on the tilemap to set the enemy position
				sf::Vector2f pos(object.GetPosition().x, object.GetPosition().y+object.GetAABB().height - bug->getSpriteSize().y);
				bug->setPosition(pos); 
				Enemy::MovementScope mscope;
				try{
				mscope.left = std::stoi(object.GetPropertyString("left")); 
				mscope.right = std::stoi(object.GetPropertyString("right")); 
				}
				catch (std::exception& e)
				{
					std::cout << "\nEXCEPTION ( Bug properties not set corectly): " << e.what() << std::endl;
				}
				bug->setMovementScope(mscope);
				//mAttackArea= sf::FloatRect(getPosition().x-mMovementScope.left*32,getPosition().y-15,(mMovementScope.left+mMovementScope.right)*32,mSpriteSize.y+15);
				bug->setAttackArea(sf::FloatRect(pos.x-mscope.left*32,pos.y-15,(mscope.left+mscope.right)*32,bug->getSpriteSize().y+15));
				
				mEnemiesContainer.push_back(bug);
			}
		else if(layer.name=="Bats")
			for(auto& object : layer.objects)
			{
				Bat* bat = new Bat();
				// We use the lower-left corner coords of the object on the tilemap to set the enemy position
				sf::Vector2f pos(object.GetPosition().x, object.GetPosition().y+object.GetAABB().height - bat->getSpriteSize().y);
				bat->setPosition(pos); 
				Enemy::MovementScope mscope;
				try{
				mscope.left = std::stoi(object.GetPropertyString("left")); 
				mscope.right = std::stoi(object.GetPropertyString("right")); 
				}
				catch (std::exception& e)
				{
					std::cout << "\nEXCEPTION ( Bug properties not set corectly): " << e.what() << std::endl;
				}
				bat->setMovementScope(mscope);
				mEnemiesContainer.push_back(bat);
			}
}

void EnemiesManager::loadTexture(const TextureHolder& textures)
{
	for(auto& enemy : mEnemiesContainer)
		enemy->loadTexture(textures);
}

void EnemiesManager::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for(auto& enemy : mEnemiesContainer)
		enemy->draw(target,states); 
}

void EnemiesManager::update(sf::Time dt)
{
	for(auto& enemy : mEnemiesContainer)
		enemy->update(dt);
}

bool EnemiesManager::intersection(sf::FloatRect rect)
{
	for(auto& enemy : mEnemiesContainer)
		if(enemy->getGlobalBounds().intersects(rect))
			return true;
		
	return false;
}

void EnemiesManager::setPlayer(Player& player)
{
	for(auto& enemy : mEnemiesContainer)
		enemy->setPlayer(player);
}
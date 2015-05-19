#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <memory>
#include <string>
#include <cassert>

using namespace std;

 enum class Textures
{
	Background1, Background2, Airplane, Missile, Player, Coin, Bug, Bat, Firebug, SplashScreen, Star
};

 template <typename Resource, typename Identifier>
class ResourceHolder
{
private:
	map<Identifier, unique_ptr<Resource>> mResourceMap;
public:

	
	void load(Identifier id,const string& filename)
	{
		unique_ptr<Resource> resource(new Resource());
		if (!resource->loadFromFile(filename))
			throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
		mResourceMap[id]=move(resource);
	}

	Resource& get(Identifier id)
	{
		//return *mResourceMap[id];
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());
		return *found->second;
	}

	const Resource& get(Identifier id) const
	{
		//return *mResourceMap[id];
		
		auto found = mResourceMap.find(id);
		assert(found != mResourceMap.end());
		return *found->second;
	}
};

typedef ResourceHolder<sf::Texture,Textures> TextureHolder;

/*
template <typename Resource, typename Identifier>
ResourceHolder<Resource,Identifier>::ResourceHolder(){}

template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
	unique_ptr<Resource> resource(new Resource());
	if (!resource->loadFromFile(filename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
	mResourceMap[id]=move(resource);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
	return *mResourceMap[id];
}
*/
#include <map>
#include "GameObject.h"

static std::map<unsigned int, GameObject*> objectCache;

bool GameObject::ContainsId(unsigned int id)
{
	return (objectCache.find(id) != objectCache.end());
}

GameObject* GameObject::GetObjectWithId(unsigned int id)
{
	if(!ContainsId(id))
		throw new std::exception("Attempt to reference null game object.");

	return objectCache[id];
}

bool GameObject::DeleteObject(unsigned int id)
{
	if(ContainsId(id))
	{
		delete objectCache[id];
		objectCache.erase(id);
		return true;
	}

	return false;
}

unsigned int GameObject::getAvailableId()
{
	unsigned int nextID = 0;

	while(ContainsId(nextID))
		nextID++;

	return nextID;
}

GameObject::GameObject()
{
	uniqueID = getAvailableId();
	objectCache[uniqueID] = this;
}

GameObject::GameObject(unsigned int newId)
{
	bool exists = ContainsId(newId);
	if(exists)
	{
		DeleteObject(newId);
	}
	uniqueID = newId;
	objectCache[newId] = this;
}

GameObject::~GameObject()
{

}

unsigned int GameObject::GetUniqueId()
{
	return uniqueID;
}
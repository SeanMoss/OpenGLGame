#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#define _USE_DEBUG_ 1

class GameObject
{
private:
	static unsigned int getAvailableId();

public:
	static GameObject* GetObjectWithId(unsigned int id);
	static bool ContainsId(unsigned int id);
	static bool DeleteObject(unsigned int id);

private:
	unsigned int uniqueID;

public:
	GameObject();
	GameObject(unsigned int useId);
	virtual ~GameObject();

	unsigned int GetUniqueId();
};

#endif
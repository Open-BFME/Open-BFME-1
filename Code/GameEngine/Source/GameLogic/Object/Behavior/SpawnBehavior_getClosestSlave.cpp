// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;
typedef float Real;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_pad000[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class Object
{
public:
	char m_pad000[0x38];
	Coord3D m_position;
};

class SpawnBehavior
{
public:
	virtual Object *getClosestSlave(const Coord3D *pos);

private:
	char m_pad004[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

Object *SpawnBehavior::getClosestSlave(const Coord3D *pos)
{
	Object *closest = 0;
	Real closestDistance;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin();
		it != m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			Real dx = obj->m_position.x - pos->x;
			Real dy = obj->m_position.y - pos->y;
			Real distance = dx;
			distance *= dx;
			distance += dy * dy;
			if (!closest || closestDistance > distance)
			{
				closest = obj;
				closestDistance = distance;
			}
		}
	}
	return closest;
}

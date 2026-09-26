// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef bool Bool;
typedef int ObjectID;

enum AbleToAttackType { ATTACK_TYPE_DUMMY };
enum CommandSourceType { COMMAND_SOURCE_DUMMY };
enum CanAttackResult
{
	ATTACKRESULT_NOT_POSSIBLE = 0,
	ATTACKRESULT_INVALID_SHOT = 1,
	ATTACKRESULT_POSSIBLE = 2,
	ATTACKRESULT_POSSIBLE_AFTER_MOVING = 3
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
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource) const;
};

// The vtable entry is the SpawnBehaviorInterface secondary slot at object+0x20.
// Its this pointer therefore addresses the secondary subobject, while the real
// SpawnBehavior::m_spawnIDs sentinel is at secondary-this+0x28 (object+0x48).
class SpawnBehavior
{
public:
	virtual CanAttackResult getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource);

private:
	char m_pad004[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

// ?getCanAnySlavesAttackSpecificTarget@SpawnBehavior@@UAE?AW4CanAttackResult@@W4AbleToAttackType@@PBVObject@@W4CommandSourceType@@@Z
CanAttackResult SpawnBehavior::getCanAnySlavesAttackSpecificTarget(AbleToAttackType attackType,
	const Object *target, CommandSourceType commandSource)
{
	Bool invalidShot = false;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
	{
		Object *obj = TheGameLogic->findObjectByID(*it);
		if (obj)
		{
			CanAttackResult result = obj->getAbleToAttackSpecificObject(attackType, target, commandSource);

			switch (result)
			{
				case ATTACKRESULT_POSSIBLE:
				case ATTACKRESULT_POSSIBLE_AFTER_MOVING:
					return result;

				case ATTACKRESULT_NOT_POSSIBLE:
					break;

				case ATTACKRESULT_INVALID_SHOT:
					invalidShot = true;
					break;

				default:
					break;
			}
		}
	}
	if (invalidShot)
		return ATTACKRESULT_INVALID_SHOT;
	return ATTACKRESULT_NOT_POSSIBLE;
}

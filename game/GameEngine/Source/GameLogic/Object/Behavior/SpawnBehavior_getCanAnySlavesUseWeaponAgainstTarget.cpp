// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef int ObjectID;

enum AbleToAttackType { ATTACK_TYPE_DUMMY };
enum CommandSourceType { COMMAND_SOURCE_DUMMY };
enum WeaponSlotType { WEAPON_SLOT_DUMMY };
enum CanAttackResult { ATTACK_RESULT_DUMMY };

struct Coord3D;
class Object;

struct ObjectLookupNode
{
	ObjectLookupNode *next;
	ObjectID id;
	Object *object;
};

class GameLogic
{
public:
	char m_pad000[0xB0];
	unsigned int m_mapSize;
	ObjectLookupNode **m_bucketStart;
	ObjectLookupNode **m_bucketFinish;
};

#define TheGameLogic (*(GameLogic **)0x012F0898)

__forceinline unsigned int getBucketCount(GameLogic *gameLogic)
{
	ObjectLookupNode **bucketStart = gameLogic->m_bucketStart;
	ObjectLookupNode **bucketFinish = gameLogic->m_bucketFinish;
	return static_cast<unsigned int>(bucketFinish - bucketStart);
}

class Object
{
public:
	CanAttackResult getAbleToAttackSpecificObject(AbleToAttackType attackType,
		const Object *target, CommandSourceType commandSource, WeaponSlotType slot) const;
};

class SpawnBehavior
{
public:
	virtual CanAttackResult getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType,
		const Object *victim, const Coord3D *pos, CommandSourceType commandSource);

private:
	char m_pad004[0x24];
	_STL::list<ObjectID> m_spawnIDs;
};

CanAttackResult SpawnBehavior::getCanAnySlavesUseWeaponAgainstTarget(AbleToAttackType attackType,
	const Object *victim, const Coord3D *pos, CommandSourceType commandSource)
{
	bool found = false;
	for (_STL::list<ObjectID>::iterator it = m_spawnIDs.begin(); it != m_spawnIDs.end(); ++it)
	{
		ObjectID id = *it;
		if (!id)
			continue;

		unsigned int bucketCount = getBucketCount(TheGameLogic);
		unsigned int bucketIndex = id % bucketCount;
		ObjectLookupNode *object = TheGameLogic->m_bucketStart[bucketIndex];
		while (object && object->id != id)
			object = object->next;
		ObjectLookupNode *match = object;
		if (match)
		{
			Object *obj = match->object;
			if (!obj)
				continue;
			CanAttackResult result = obj->getAbleToAttackSpecificObject(
				attackType, victim, static_cast<CommandSourceType>(reinterpret_cast<unsigned int>(pos)),
				static_cast<WeaponSlotType>(commandSource));
			switch (result)
			{
				case static_cast<CanAttackResult>(3):
				case static_cast<CanAttackResult>(2):
					return result;
				case static_cast<CanAttackResult>(0):
					break;
				case static_cast<CanAttackResult>(1):
					found = true;
					break;
				default:
					break;
			}
		}
	}
	if (found)
		return static_cast<CanAttackResult>(1);

	return static_cast<CanAttackResult>(0);
}

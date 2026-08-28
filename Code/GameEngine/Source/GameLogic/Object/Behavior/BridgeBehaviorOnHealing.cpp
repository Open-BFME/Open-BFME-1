// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// BFME's BridgeBehavior healing propagation uses the old GameLogic object hash.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
enum KindOfType { KINDOF_BRIDGE_TOWER = 24 };
enum BodyDamageType { BODY_RUBBLE = 3 };
enum PathfindLayerEnum {};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class DamageInfo;

class BodyModuleInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual Real getMaxHealth() const;
	virtual void unused07();
	virtual BodyDamageType getDamageState() const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	bool isKindOf(KindOfType type) const
	{
		return (m_kindOf[(UnsignedInt)type >> 5] &
			(1 << ((UnsignedInt)type & 31))) != 0;
	}

	unsigned char m_unreconstructed08[0xC8 - 0x08];
	UnsignedInt m_kindOf[3];
};

class Object
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void attemptDamage(DamageInfo *damageInfo);
	virtual void unused14();
	virtual void unused15();
	virtual void attemptHealing(Real amount, Object *source);

	bool isBridgeTower() const
	{
		const ThingTemplate *finalTemplate = m_template;
		if (finalTemplate && finalTemplate->m_nextOverride)
			finalTemplate = (const ThingTemplate *)finalTemplate->m_nextOverride->getFinalOverride();
		return finalTemplate->isKindOf(KINDOF_BRIDGE_TOWER);
	}

	BodyModuleInterface *getBodyModule() const { return m_body; }
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_position; }

private:
	ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x38 - 0x08];
	Coord3D m_position;
	unsigned char m_unreconstructed44[0x74 - 0x44];
	ObjectID m_id;
	unsigned char m_unreconstructed78[0x200 - 0x78];
	BodyModuleInterface *m_body;
};

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);

	__forceinline Object *findObjectByIDInline(ObjectID id)
	{
		if (id == INVALID_ID)
			return 0;

		ObjectPtrHash::iterator it = m_objHash.find((int)id);
		if (it == m_objHash.end())
			return 0;

		return (*it).second;
	}

private:
	unsigned char m_unreconstructed00[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheGameLogic;

class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, Object *tower);
	virtual ObjectID getTowerID(int towerType);
};

class BridgeScaffoldBehaviorInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

void __stlp_deallocate_small(void *node, UnsignedInt bytes);

template <class T>
class BridgeScaffoldAllocator : public _STL::allocator<T>
{
public:
	template <class U> struct rebind { typedef BridgeScaffoldAllocator<U> other; };

	BridgeScaffoldAllocator() {}
	template <class U> BridgeScaffoldAllocator(const BridgeScaffoldAllocator<U> &) {}

	void deallocate(T *node, UnsignedInt count) const
	{
		__stlp_deallocate_small(node, count * sizeof(T));
	}
};

template <class T, class U>
BridgeScaffoldAllocator<U> &__stl_alloc_rebind(
	BridgeScaffoldAllocator<T> &allocator, const U *)
{
	return (BridgeScaffoldAllocator<U> &)allocator;
}

typedef _STL::list<ObjectID, BridgeScaffoldAllocator<ObjectID> > BridgeScaffoldList;

class Bridge
{
public:
	PathfindLayerEnum getLayer() const { return m_layer; }

private:
	unsigned char m_unreconstructed00[0x88];
	PathfindLayerEnum m_layer;
};

class TerrainLogic
{
public:
	virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17(); virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21(); virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25(); virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29(); virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33(); virtual void unused34(); virtual void unused35();
	virtual void unused36(); virtual void unused37();
	virtual Bridge *findBridgeAt(const Coord3D *position);
};

class Pathfinder
{
public:
	void friend_changeBridgeState(PathfindLayerEnum layer, bool open);
};

class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_unreconstructed00[0x0C];
	Pathfinder *m_pathfinder;
};

extern TerrainLogic *TheTerrainLogic;
extern AI *TheAI;

class DamageInfo
{
public:
	DamageInfo();

	unsigned char m_unreconstructed00[0x08];
	ObjectID m_sourceID;
	void *m_sourceTemplate;
	int m_damageType;
	int m_damageFXOverride;
	int m_deathType;
	Real m_amount;
	unsigned char m_unreconstructed20[0x5C - 0x20];
};

class BridgeBehavior
{
public:
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onDamage(DamageInfo *damageInfo);
	virtual bool isScaffoldInMotion();
	virtual void removeScaffolding();
	Object *getObject() const
	{
		return *(Object **)((unsigned char *)this - 0x1C);
	}

private:
	unsigned char m_unreconstructed04[0x45D - 0x04];
	bool m_scaffoldPresent;
	unsigned char m_unreconstructed45E[0x460 - 0x45E];
	BridgeScaffoldList m_scaffoldObjectIDList;
};

// ?onHealing@BridgeBehavior@@UAEXPAVDamageInfo@@@Z
void BridgeBehavior::onHealing(DamageInfo *damageInfo)
{
	Real healingPercentage = damageInfo->m_amount / getObject()->getBodyModule()->getMaxHealth();
	Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);

	if (source == 0 || !source->isBridgeTower())
	{
		for (int i = 0; i < 4; ++i)
		{
			BridgeBehaviorInterface *bridge =
				(BridgeBehaviorInterface *)((unsigned char *)this - 4);
			Object *tower = TheGameLogic->findObjectByIDInline(bridge->getTowerID(i));
			if (tower)
			{
				BodyModuleInterface *towerBody = tower->getBodyModule();
				tower->attemptHealing(healingPercentage * towerBody->getMaxHealth(), getObject());
			}
		}
	}
}

// ?isScaffoldInMotion@BridgeBehavior@@UAE_NXZ
bool BridgeBehavior::isScaffoldInMotion()
{
	for (BridgeScaffoldList::iterator it = m_scaffoldObjectIDList.begin();
		it != m_scaffoldObjectIDList.end(); ++it)
	{
		Object *object = TheGameLogic->findObjectByIDInline(*it);
		if (object == 0)
			continue;

		BridgeScaffoldBehaviorInterface *scaffold =
			BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
		if (scaffold && scaffold->getCurrentMotion() != 0)
			return true;
	}

	return false;
}

// ?removeScaffolding@BridgeBehavior@@UAEXXZ
void BridgeBehavior::removeScaffolding()
{
	if (!m_scaffoldPresent)
		return;

	for (BridgeScaffoldList::iterator it = m_scaffoldObjectIDList.begin();
		it != m_scaffoldObjectIDList.end(); ++it)
	{
		Object *object = TheGameLogic->findObjectByID(*it);
		if (object == 0)
			continue;

		BridgeScaffoldBehaviorInterface *scaffold =
			BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
		scaffold->reverseMotion();
	}

	m_scaffoldObjectIDList.clear();
	m_scaffoldPresent = false;

	Object *object = *(Object **)((unsigned char *)this - 0x18);
	if (object->getBodyModule()->getDamageState() != BODY_RUBBLE)
	{
		Bridge *bridge = TheTerrainLogic->findBridgeAt(object->getPosition());
		if (bridge)
			TheAI->pathfinder()->friend_changeBridgeState(bridge->getLayer(), true);
	}
}

// ?onDamage@BridgeBehavior@@UAEXPAVDamageInfo@@@Z
void BridgeBehavior::onDamage(DamageInfo *damageInfo)
{
	Real damagePercentage = damageInfo->m_amount / getObject()->getBodyModule()->getMaxHealth();
	Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);

	if (source == 0 || !source->isBridgeTower())
	{
		for (int i = 0; i < 4; ++i)
		{
			BridgeBehaviorInterface *bridge =
				(BridgeBehaviorInterface *)((unsigned char *)this - 4);
			Object *tower = TheGameLogic->findObjectByIDInline(bridge->getTowerID(i));
			if (tower)
			{
				BodyModuleInterface *towerBody = tower->getBodyModule();
				DamageInfo towerDamage;
				towerDamage.m_amount = damagePercentage * towerBody->getMaxHealth();
				towerDamage.m_sourceID = getObject()->getID();
				towerDamage.m_damageType = damageInfo->m_damageType;
				towerDamage.m_deathType = damageInfo->m_deathType;
				tower->attemptDamage(&towerDamage);
			}
		}
	}
}

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

private:
	ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x74 - 0x08];
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
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

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
	Object *getObject() const
	{
		return *(Object **)((unsigned char *)this - 0x1C);
	}

private:
	unsigned char m_unreconstructed04[0x460 - 0x04];
	_STL::list<ObjectID> m_scaffoldObjectIDList;
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
	for (_STL::list<ObjectID>::iterator it = m_scaffoldObjectIDList.begin();
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

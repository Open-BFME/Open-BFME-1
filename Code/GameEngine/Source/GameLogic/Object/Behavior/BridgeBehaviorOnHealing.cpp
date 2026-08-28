// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// BFME's BridgeBehavior healing propagation uses the old GameLogic object hash.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
enum KindOfType { KINDOF_BRIDGE_TOWER = 24 };

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
	virtual void unused13();
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

private:
	ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x200 - 0x08];
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

class DamageInfo
{
public:
	unsigned char m_unreconstructed00[0x08];
	ObjectID m_sourceID;
	unsigned char m_unreconstructed0C[0x1C - 0x0C];
	Real m_amount;
};

class BridgeBehavior
{
public:
	virtual void onHealing(DamageInfo *damageInfo);
	Object *getObject() const
	{
		return *(Object **)((unsigned char *)this - 0x1C);
	}
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

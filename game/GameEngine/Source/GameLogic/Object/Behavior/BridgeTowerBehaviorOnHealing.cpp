// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// Readable reconstruction of ?onHealing@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z.
//
// The retail entry is the second slot of BridgeTowerBehavior's DamageModule
// interface vtable at 0x010A2A68.  Its incoming ECX is therefore the +0x18
// secondary interface, not the primary module address.  The local views below
// preserve that ABI and the BFME Object/BehaviorModule offsets without changing
// the shared headers.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef float Real;
typedef unsigned int UnsignedInt;
typedef unsigned char Byte;

enum ObjectID { INVALID_ID = 0 };
enum KindOfType
{
	KINDOF_BRIDGE = 22,
	KINDOF_BRIDGE_TOWER = 24
};
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };
enum BodyDamageType { BODY_RUBBLE = 3 };

class DamageInfo;
class BodyModuleInterface;
class BehaviorModule;
class BridgeBehaviorInterface;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModuleInterface
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
	virtual void unused0A();
	virtual BridgeBehaviorInterface *getBridgeBehaviorInterface();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, class Object *tower);
	virtual ObjectID getTowerID(int towerType);
};

// This is the BFME +0x200 body pointer and the object virtual layout used by
// the target's getMaxHealth and attemptHealing calls.
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

	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface *const *)((const unsigned char *)this + 0x200);
	}

	BehaviorModule **getBehaviorModules() const
	{
		return *(BehaviorModule ***)((const unsigned char *)this + 0x1F0);
	}

	bool isKindOf(KindOfType type) const
	{
		const ThingTemplate *finalTemplate = m_template;
		if (finalTemplate && finalTemplate->m_nextOverride)
			finalTemplate = (const ThingTemplate *)finalTemplate->m_nextOverride->getFinalOverride();
		return finalTemplate->isKindOf(type);
	}

	ObjectID getID() const { return m_id; }

private:
	ThingTemplate *m_template;
	unsigned char m_unreconstructed08[0x38 - 0x08];
	unsigned char m_unreconstructed38[0x74 - 0x38];
	ObjectID m_id;
	unsigned char m_unreconstructed78[0x200 - 0x78];
	BodyModuleInterface *m_body;
};

typedef _STL::hash_map<int, Object *, _STL::hash<int>, _STL::equal_to<int> > ObjectPtrHash;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
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

// BridgeTowerBehavior's incoming pointer is the DamageModuleInterface
// subobject at module+0x18.  The BridgeTower interface is the preceding
// subobject at module+0x10, and the owning Object is module+0x08.
class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge);
	virtual ObjectID getBridgeID();
	virtual void setTowerType(int type);
};

class BridgeTowerBehavior
{
public:
	virtual void onDamage(DamageInfo *damageInfo);
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onBodyDamageStateChange(const DamageInfo *damageInfo,
		BodyDamageType oldState, BodyDamageType newState);

	Object *getObject() const
	{
		return *(Object *const *)((const unsigned char *)this - 0x10);
	}
};

// ?onHealing@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z
void BridgeTowerBehavior::onHealing(DamageInfo *damageInfo)
{
	BridgeTowerBehaviorInterface *towerInterface =
		(BridgeTowerBehaviorInterface *)((unsigned char *)this - 0x08);
	Object *bridge = TheGameLogic->findObjectByID(towerInterface->getBridgeID());
	if (bridge == NULL)
		return;

	BodyModuleInterface *body = getObject()->getBodyModule();
	Real healingPercentage = damageInfo->m_amount / body->getMaxHealth();

	BehaviorModule **bmi;
	BridgeBehaviorInterface *bridgeInterface = NULL;
	for (bmi = bridge->getBehaviorModules(); *bmi; ++bmi)
	{
		BehaviorModuleInterface *moduleInterface =
			(BehaviorModuleInterface *)((unsigned char *)*bmi + 0x0C);
		bridgeInterface = moduleInterface->getBridgeBehaviorInterface();
		if (bridgeInterface)
			break;
	}

	if (bridgeInterface)
	{
		Object *source = TheGameLogic->findObjectByID(damageInfo->m_sourceID);
		if (source == NULL ||
			(source->isKindOf(KINDOF_BRIDGE) == false &&
			 source->isKindOf(KINDOF_BRIDGE_TOWER) == false))
		{
			for (int i = 0; i < 4; ++i)
			{
				Object *tower = TheGameLogic->findObjectByIDInline(
					bridgeInterface->getTowerID(i));
				if (tower && tower != getObject())
				{
					BodyModuleInterface *towerBody = tower->getBodyModule();
					tower->attemptHealing(
						healingPercentage * towerBody->getMaxHealth(), getObject());
				}
			}

			BodyModuleInterface *bridgeBody = bridge->getBodyModule();
			bridge->attemptHealing(
				healingPercentage * bridgeBody->getMaxHealth(), getObject());
		}
	}
}

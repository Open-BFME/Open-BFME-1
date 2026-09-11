// ?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z
// partial score=0.99 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// Readable reconstruction of ?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z.

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
enum BridgeTowerType { BRIDGE_TOWER_0, BRIDGE_TOWER_1, BRIDGE_TOWER_2, BRIDGE_TOWER_3 };

class DamageInfo;
class BodyModuleInterface;
class BehaviorModule;
class BridgeBehaviorInterface;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class Snapshot
{
public:
	virtual void unusedSnapshot();
};

class DamageInfoInput : public Snapshot
{
public:
	ObjectID m_sourceID;
	void *m_sourceTemplate;
	int m_damageType;
	int m_damageFXOverride;
	int m_deathType;
	Real m_amount;
	unsigned char m_unreconstructed1C[0x20 - 0x1C];
};

class DamageInfo : public Snapshot
{
public:
	DamageInfo();

	DamageInfoInput in;
	unsigned char m_unreconstructed24[0x5C - 0x24];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
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

class BehaviorModule
{
public:
	BridgeBehaviorInterface *getBridgeBehaviorInterface()
	{
		return ((BehaviorModuleInterface *)((unsigned char *)this + 0x0C))
			->getBridgeBehaviorInterface();
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, class Object *tower);
	virtual ObjectID getTowerID(BridgeTowerType towerType);
};

// This is the BFME +0x200 body pointer and the object virtual layout used by
// the target's getMaxHealth and attemptDamage calls.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
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

	ObjectID getBridgeID()
	{
		BridgeTowerBehaviorInterface *towerInterface =
			(BridgeTowerBehaviorInterface *)((unsigned char *)this - 0x08);
		return towerInterface->getBridgeID();
	}

	Object *getObject() const
	{
		return *(Object *const *)((const unsigned char *)this - 0x10);
	}
};

// ?onDamage@BridgeTowerBehavior@@UAEXPAVDamageInfo@@@Z
void BridgeTowerBehavior::onDamage(DamageInfo *damageInfo)
{
	Object *bridge = TheGameLogic->findObjectByID(getBridgeID());
	if (bridge == NULL)
		return;

	BodyModuleInterface *body = getObject()->getBodyModule();
	Real damagePercentage = damageInfo->in.m_amount / body->getMaxHealth();

	BehaviorModule **bmi;
	BridgeBehaviorInterface *bridgeInterface = NULL;
	for (bmi = bridge->getBehaviorModules(); *bmi; ++bmi)
	{
		bridgeInterface = (*bmi)->getBridgeBehaviorInterface();
		if (bridgeInterface)
			break;
	}

	if (bridgeInterface)
	{
		Object *source = TheGameLogic->findObjectByID(damageInfo->in.m_sourceID);
		if (source == NULL ||
			(source->isKindOf(KINDOF_BRIDGE) == false &&
				source->isKindOf(KINDOF_BRIDGE_TOWER) == false))
		{
			for (int i = 0; i < 4; ++i)
			{
				Object *tower = TheGameLogic->findObjectByIDInline(
					bridgeInterface->getTowerID((BridgeTowerType)i));
				if (tower && tower != getObject())
				{
					BodyModuleInterface *towerBody = tower->getBodyModule();
					DamageInfo towerDamage;

					towerDamage.in.m_amount =
						damagePercentage * towerBody->getMaxHealth();
					towerDamage.in.m_sourceID = getObject()->getID();
					towerDamage.in.m_damageType = damageInfo->in.m_damageType;
					towerDamage.in.m_deathType = damageInfo->in.m_deathType;
					tower->attemptDamage(&towerDamage);
				}
			}

			BodyModuleInterface *bridgeBody = bridge->getBodyModule();
			DamageInfo bridgeDamage;

			bridgeDamage.in.m_amount =
				damagePercentage * bridgeBody->getMaxHealth();
			bridgeDamage.in.m_sourceID = getObject()->getID();
			bridgeDamage.in.m_damageType = damageInfo->in.m_damageType;
			bridgeDamage.in.m_deathType = damageInfo->in.m_deathType;
			bridge->attemptDamage(&bridgeDamage);
		}
	}
}

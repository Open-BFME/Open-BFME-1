// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// stlport
// readable body of ?isScaffoldInMotion@BridgeBehavior@@UAE_NXZ: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?onDamage@BridgeBehavior@@UAEXPAVDamageInfo@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?onDie@BridgeBehavior@@UAEXPBVDamageInfo@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?onHealing@BridgeBehavior@@UAEXPAVDamageInfo@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?removeScaffolding@BridgeBehavior@@UAEXXZ: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?setScaffoldData@BridgeBehavior@@IAEXPAVObject@@PAM1PBUCoord3D@@22@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// readable body of ?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z: Code/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp
// BFME's BridgeBehavior healing propagation uses the old GameLogic object hash.

#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <math.h>
#include <hash_map>
#include <list>

typedef float Real;
typedef unsigned int UnsignedInt;
enum ObjectID { INVALID_ID = 0 };
enum KindOfType { KINDOF_BRIDGE_TOWER = 24 };
enum BodyDamageType { BODY_RUBBLE = 3 };
enum PathfindLayerEnum {};
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real length() const { return (Real)sqrt(x * x + y * y + z * z); }

	Real x;
	Real y;
	Real z;
};

class DamageInfo;
class Xfer;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	void setOrientation(Real angle);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule
{
protected:
	virtual void xfer(Xfer *xfer);
};

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
	virtual void unused07();
	virtual BodyDamageType getDamageState() const;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
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
	void kill(DamageType damageType, DeathType deathType);
	void setPosition(const Coord3D *position);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	UnsignedInt getFrame() const
	{
		return *(const UnsignedInt *)((const unsigned char *)this + 0x3C);
	}

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower(int towerType, Object *tower);
	virtual ObjectID getTowerID(int towerType);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h
class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3D *sunkenPosition,
		const Coord3D *risePosition, const Coord3D *buildPosition);
	virtual void setMotion(int motion);
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
	virtual void setLateralSpeed(Real speed);
	virtual void setVerticalSpeed(Real speed);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeScaffoldBehavior.h
class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};

void __stlp_deallocate_small(void *node, UnsignedInt bytes);
namespace _STL { void *nodeAllocate(UnsignedInt bytes); }

template <class T>
class BridgeScaffoldAllocator : public _STL::allocator<T>
{
public:
	template <class U> struct rebind { typedef BridgeScaffoldAllocator<U> other; };

	BridgeScaffoldAllocator() {}
	template <class U> BridgeScaffoldAllocator(const BridgeScaffoldAllocator<U> &) {}

	T *allocate(UnsignedInt count, const void * = 0) const
	{
		return (T *)_STL::nodeAllocate(count * sizeof(T));
	}

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	PathfindLayerEnum getLayer() const { return m_layer; }
	void setBridgeObjectID(ObjectID id)
	{
		*(ObjectID *)((unsigned char *)this + 0x60) = id;
	}
	void setTowerObjectID(ObjectID id, UnsignedInt tower)
	{
		((ObjectID *)((unsigned char *)this + 0x64))[tower] = id;
	}

private:
	unsigned char m_unreconstructed00[0x88];
	PathfindLayerEnum m_layer;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void friend_changeBridgeState(PathfindLayerEnum layer, bool open);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
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

struct XferVersion
{
	XferVersion(unsigned char value) : current(value), minimum(value) {}

	unsigned char current;
	unsigned char minimum;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	virtual void unused00();
	virtual bool isLoading() const;
	virtual bool isStoring() const;
	virtual void unused03();
	virtual bool isLightCRC() const;
	virtual void unused05(); virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void xferVersion(XferVersion *version);
	virtual void unused11(); virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15(); virtual void unused16();
	virtual void unused17(); virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21(); virtual void unused22();
	virtual void unused23(); virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27(); virtual void unused28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void unused30();
	virtual void xferUnsignedShort(unsigned short *value);
	virtual void unused32(); virtual void unused33(); virtual void unused34();
	virtual void xferBool(bool *value);
};

void friend_xferObjectID(Xfer *xfer, ObjectID *id);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehavior : public UpdateModule
{
public:
	virtual void onHealing(DamageInfo *damageInfo);
	virtual void onDamage(DamageInfo *damageInfo);
	virtual bool isScaffoldInMotion();
	virtual void removeScaffolding();
	virtual void onDie(const DamageInfo *damageInfo);

protected:
	virtual void xfer(Xfer *xfer);
	void handleObjectsOnBridgeOnDie();
	void setScaffoldData(Object *object, Real *angle, Real *sunkenHeight,
		const Coord3D *risePosition, const Coord3D *buildPosition,
		const Coord3D *bridgeCenter);

public:
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

// ?xfer@BridgeBehavior@@MAEXPAVXfer@@@Z
void BridgeBehavior::xfer(Xfer *xfer)
{
	UpdateModule::xfer(xfer);
	if (xfer->isLightCRC())
		return;

	unsigned char *behavior = (unsigned char *)this;
	Object *object = *(Object **)(behavior + 0x08);
	XferVersion version(1);
	xfer->xferVersion(&version);

	if (xfer->isLoading())
	{
		Bridge *bridge = TheTerrainLogic->findBridgeAt(object->getPosition());
		bridge->setBridgeObjectID(object->getID());
	}

	ObjectID *towerID = (ObjectID *)(behavior + 0x2C);
	for (int i = 0; i < 4; ++i, ++towerID)
		friend_xferObjectID(xfer, towerID);

	if (xfer->isLoading())
	{
		Bridge *bridge = TheTerrainLogic->findBridgeAt(object->getPosition());
		bridge->setTowerObjectID(*(ObjectID *)(behavior + 0x2C), 0);
		bridge->setTowerObjectID(*(ObjectID *)(behavior + 0x30), 1);
		bridge->setTowerObjectID(*(ObjectID *)(behavior + 0x34), 2);
		bridge->setTowerObjectID(*(ObjectID *)(behavior + 0x38), 3);
	}

	xfer->xferBool((bool *)(behavior + 0x47D));
	BridgeScaffoldList *scaffoldIDs = (BridgeScaffoldList *)(behavior + 0x480);
	unsigned short scaffoldCount = 0;
	scaffoldCount = (unsigned short)scaffoldIDs->size();
	xfer->xferUnsignedShort(&scaffoldCount);

	ObjectID scaffoldID;
	if (xfer->isStoring())
	{
		for (BridgeScaffoldList::iterator it = scaffoldIDs->begin();
			it != scaffoldIDs->end(); ++it)
		{
			scaffoldID = *it;
			friend_xferObjectID(xfer, &scaffoldID);
		}
	}
	else
	{
		for (UnsignedInt i = 0; i < scaffoldCount; ++i)
		{
			friend_xferObjectID(xfer, &scaffoldID);
			scaffoldIDs->push_back(scaffoldID);
		}
	}

	xfer->xferUnsignedInt((UnsignedInt *)(behavior + 0x484));
	xfer->xferBool((bool *)(behavior + 0x47C));
}

// ?onDie@BridgeBehavior@@UAEXPBVDamageInfo@@@Z
void BridgeBehavior::onDie(const DamageInfo *)
{
	int i = 0;
	BridgeBehaviorInterface *bridge =
		(BridgeBehaviorInterface *)((unsigned char *)this - 0x08);
	for (; i < 4; ++i)
	{
		Object *tower = TheGameLogic->findObjectByIDInline(bridge->getTowerID(i));
		if (tower)
			tower->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}

	BridgeBehavior *primary = (BridgeBehavior *)((unsigned char *)this - 0x28);
	primary->handleObjectsOnBridgeOnDie();
	*(UnsignedInt *)((unsigned char *)this + 0x45C) = TheGameLogic->getFrame();
}

// ?setScaffoldData@BridgeBehavior@@IAEXPAVObject@@PAM1PBUCoord3D@@22@Z
void BridgeBehavior::setScaffoldData(Object *object, Real *angle, Real *sunkenHeight,
	const Coord3D *risePosition, const Coord3D *buildPosition,
	const Coord3D *bridgeCenter)
{
	if (object == 0 || angle == 0 || risePosition == 0 || buildPosition == 0)
		return;

	const unsigned char *moduleData = *(const unsigned char **)
		((const unsigned char *)this + 0x04);
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);

	Real fudge = 8.0f;
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - fudge;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion(1);
	((Thing *)object)->setOrientation(*angle);

	Real lateralSpeed = *(const Real *)(moduleData + 0x08);
	Coord3D buildToCenter;
	Coord3D riseToCenter;
	buildToCenter.x = buildPosition->x - risePosition->x;
	buildToCenter.y = buildPosition->y - risePosition->y;
	buildToCenter.z = buildPosition->z - risePosition->z;
	riseToCenter.x = bridgeCenter->x - risePosition->x;
	riseToCenter.y = bridgeCenter->y - risePosition->y;
	riseToCenter.z = bridgeCenter->z - risePosition->z;
	Real buildDistance = buildToCenter.length();
	Real riseDistance = riseToCenter.length();
	scaffold->setLateralSpeed(
		lateralSpeed * (buildDistance / riseDistance));
	Real verticalSpeed = *(const Real *)(moduleData + 0x0C);
	scaffold->setVerticalSpeed(verticalSpeed);
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

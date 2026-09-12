// ?createTower@Bridge@@QAEPAVObject@@PAUCoord3D@@W4BridgeTowerType@@PBVThingTemplate@@PAV2@@Z
// partial score=0.26 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc
// readable body of ?createTower@Bridge@@QAEPAVObject@@PAUCoord3D@@W4BridgeTowerType@@PBVThingTemplate@@PAV2@@Z: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp
// Open-BFME5: de-lift MASM dump to real C++; TU-local shim classes at the
// retail offsets, following the PartitionFilterPlayerAffiliation_allow_Thunk model.

struct Coord3D;
class ThingTemplate;
class Team;
class Object;

enum BridgeTowerType
{
	BRIDGE_TOWER_FROM_LEFT = 0,
	BRIDGE_TOWER_FROM_RIGHT,
	BRIDGE_TOWER_TO_LEFT,
	BRIDGE_TOWER_TO_RIGHT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ObjectStatusTypes.h
// retail passes this by hidden reference to a caller-constructed, zeroed temporary (3 dwords).
class ObjectStatusMaskType
{
public:
	ObjectStatusMaskType() : m_w0(0), m_w1(0), m_w2(0) { }

private:
	unsigned int m_w0;
	unsigned int m_w1;
	unsigned int m_w2;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
// retail's call site pushes a trailing zero after the status mask; the ZH
// header does not show a 4th parameter, so BFME's fork added one here.
class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, ObjectStatusMaskType statusMask, int extraFlag = 0);
};

// ?TheThingFactory@@3PAVThingFactory@@A
extern ThingFactory *TheThingFactory;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
// Only the two slots createTower actually calls are named; everything ahead
// of them in BodyModuleInterface's real declaration order is a dummy virtual
// so setIndestructible/isIndestructible land on retail's vtable slots 33/34
// (offsets 0x84/0x88).
class BodyModuleInterface
{
public:
	virtual void bmi00() = 0;
	virtual void bmi01() = 0;
	virtual void bmi02() = 0;
	virtual void bmi03() = 0;
	virtual void bmi04() = 0;
	virtual void bmi05() = 0;
	virtual void bmi06() = 0;
	virtual void bmi07() = 0;
	virtual void bmi08() = 0;
	virtual void bmi09() = 0;
	virtual void bmi10() = 0;
	virtual void bmi11() = 0;
	virtual void bmi12() = 0;
	virtual void bmi13() = 0;
	virtual void bmi14() = 0;
	virtual void bmi15() = 0;
	virtual void bmi16() = 0;
	virtual void bmi17() = 0;
	virtual void bmi18() = 0;
	virtual void bmi19() = 0;
	virtual void bmi20() = 0;
	virtual void bmi21() = 0;
	virtual void bmi22() = 0;
	virtual void bmi23() = 0;
	virtual void bmi24() = 0;
	virtual void bmi25() = 0;
	virtual void bmi26() = 0;
	virtual void bmi27() = 0;
	virtual void bmi28() = 0;
	virtual void bmi29() = 0;
	virtual void bmi30() = 0;
	virtual void bmi31() = 0;
	virtual void bmi32() = 0;
	virtual void setIndestructible(bool indestructible) = 0;	///< slot 33, retail +0x84
	virtual bool isIndestructible(void) const = 0;				///< slot 34, retail +0x88
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;	///< slot 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h
class BridgeTowerBehaviorInterface
{
public:
	virtual void setBridge(Object *bridge) = 0;			///< slot 0
	virtual void btbi_getBridgeID() = 0;					///< slot 1 (unused)
	virtual void setTowerType(BridgeTowerType type) = 0;	///< slot 2
};

class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *obj);
};

class BridgeTowerBehavior
{
public:
	static BridgeTowerBehaviorInterface *getBridgeTowerBehaviorInterfaceFromObject(Object *obj);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h (Thing base)
class Thing
{
public:
	float getOrientation(void) const { return m_angle; }
	void setOrientation(float angle);						///< pinned at 0x0003999A5 (setOrientation@Thing)

protected:
	unsigned char m_unreconstructed_00[0x44];
	float m_angle;											///< retail this+0x44
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Team *getTeam(void) const { return m_team; }
	BodyModuleInterface *getBodyModule(void) const { return m_body; }
	void setPosition(const Coord3D *pos);					///< pinned at 0x0003A1A7 (setPosition@Object)

private:
	unsigned char m_unreconstructed_48[0x200 - 0x48];
	BodyModuleInterface *m_body;							///< retail this+0x200
	unsigned char m_unreconstructed_204[0x23C - 0x204];
	Team *m_team;											///< retail this+0x23C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	Object *createTower(Coord3D *worldPos, BridgeTowerType towerType, const ThingTemplate *towerTemplate, Object *bridge);
};

static const float PI = 3.1415926535897932384626433832795f;

// ?createTower@Bridge@@QAEPAVObject@@PAUCoord3D@@W4BridgeTowerType@@PBVThingTemplate@@PAV2@@Z
Object *Bridge::createTower(Coord3D *worldPos, BridgeTowerType towerType, const ThingTemplate *towerTemplate, Object *bridge)
{
	if (towerTemplate == 0 || bridge == 0)
		return 0;

	Team *team = bridge->getTeam();
	Object *tower = TheThingFactory->newObject(towerTemplate, team, ObjectStatusMaskType());

	float angle = 0;
	switch (towerType)
	{
		case BRIDGE_TOWER_FROM_LEFT:
			angle = bridge->getOrientation() + PI;
			break;

		case BRIDGE_TOWER_FROM_RIGHT:
			angle = bridge->getOrientation() + PI;
			break;

		case BRIDGE_TOWER_TO_LEFT:
			angle = bridge->getOrientation();
			break;

		case BRIDGE_TOWER_TO_RIGHT:
			angle = bridge->getOrientation();
			break;

		default:
			return 0;
	}

	tower->setPosition(worldPos);
	tower->setOrientation(angle);

	BridgeBehaviorInterface *bridgeInterface = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridge);
	if (bridgeInterface)
		bridgeInterface->setTower(towerType, tower);

	BridgeTowerBehaviorInterface *bridgeTowerInterface = BridgeTowerBehavior::getBridgeTowerBehaviorInterfaceFromObject(tower);
	if (bridgeTowerInterface)
	{
		bridgeTowerInterface->setBridge(bridge);
		bridgeTowerInterface->setTowerType(towerType);
	}

	BodyModuleInterface *bridgeBody = bridge->getBodyModule();
	if (bridgeBody->isIndestructible())
	{
		BodyModuleInterface *towerBody = tower->getBodyModule();
		towerBody->setIndestructible(true);
	}

	return tower;
}

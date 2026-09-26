// ?createTower@Bridge@@QAEPAVObject@@PAUCoord3D@@W4BridgeTowerType@@PBVThingTemplate@@PAV2@@Z
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <bitset>
// Bridge::createTower, retail 0x001A9730: 265 executable bytes ending ret 16,
// followed by three alignment bytes and a 16-byte switch table. The complete
// 284-byte compiler section also matches retail. The Object-based Bridge
// constructor and Zero Hour TerrainLogic.cpp independently identify this body.
// Started from the old bank: the missing lever is newObject's real
// BitFlags<86> const-reference ABI and native STLport bitset construction.
// Callees: ThingFactory::newObject; Thing position/orientation setters;
// BridgeBehavior and BridgeTowerBehavior interface lookup helpers.

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ObjectStatusTypes.h
// Retail passes a const reference to a zeroed 86-bit mask (three words).
template<int N>
class BitFlags { std::bitset<N> m_bits; };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingFactory.h
// retail's call site pushes a trailing zero after the status mask; the ZH
// header does not show a 4th parameter, so BFME's fork added one here.
typedef BitFlags<86> ObjectStatusMaskType;

class ThingFactory
{
public:
	Object *newObject(const ThingTemplate *tmplate, Team *team, const ObjectStatusMaskType &statusMask, unsigned int extraFlag = 0);
};

// ?TheThingFactory@@3PAVThingFactory@@A
extern ThingFactory *TheThingFactory;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void setTower(BridgeTowerType towerType, Object *tower) = 0;	///< slot 0
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeTowerBehavior.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h (Thing base)
class Thing
{
public:
	void setPosition(const Coord3D *pos);
	float getOrientation(void) const { return m_cachedAngle; }
	void setOrientation(float angle);						///< ILT 0x000399A5 -> 0x00132E40

protected:
	unsigned char m_unreconstructed_00[0x44];
	float m_cachedAngle;											///< retail this+0x44
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	Team *getTeam(void) const { return m_team; }
	BodyModuleInterface *getBodyModule(void) const { return m_body; }
	
private:
	unsigned char m_unreconstructed_48[0x200 - 0x48];
	BodyModuleInterface *m_body;							///< retail this+0x200
	unsigned char m_unreconstructed_204[0x23C - 0x204];
	Team *m_team;											///< retail this+0x23C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
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

	Object *tower = TheThingFactory->newObject(towerTemplate, bridge->getTeam(), ObjectStatusMaskType());

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

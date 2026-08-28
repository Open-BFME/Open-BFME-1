// cl: /DNDEBUG /DWIN32 /MD /EHsc
// readable body of ?updateDamageState@Bridge@@QAEXXZ: Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp

typedef bool Bool;
typedef float Real;

enum ObjectID { INVALID_ID = 0 };
enum BodyDamageType { BODY_RUBBLE = 3 };
enum DamageType { DAMAGE_FALLING = 11 };
enum DeathType { DEATH_SPLATTED = 11 };
enum PathfindLayerEnum {};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfoInput
{
	unsigned char m_unmodelled_00[8];
	ObjectID m_sourceID;
	unsigned char m_unmodelled_0C[4];
	DamageType m_damageType;
	unsigned char m_unmodelled_14[4];
	DeathType m_deathType;
	Real m_amount;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
struct DamageInfo
{
	DamageInfo();
	DamageInfoInput in;
	unsigned char m_unmodelled_20[0x5C - 0x20];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
{
public:
	virtual void anchor00();
	virtual void anchor04();
	virtual void anchor08();
	virtual void anchor0C();
	virtual void anchor10();
	virtual void anchor14();
	virtual void anchor18();
	virtual void anchor1C();
	virtual BodyDamageType getDamageState();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	virtual void anchor00();
	virtual void anchor04();
	virtual void anchor08();
	virtual void anchor0C();
	virtual void anchor10();
	virtual void anchor14();
	virtual void anchor18();
	virtual void anchor1C();
	virtual void anchor20();
	virtual void anchor24();
	virtual void anchor28();
	virtual void anchor2C();
	virtual void anchor30();
	virtual void attemptDamage(DamageInfo *damageInfo);

	ObjectID getID() const { return m_id; }
	Object *getNextObject() const { return m_nextObject; }
	int getLayer() const;
	BodyModuleInterface *getBodyModule() const { return m_body; }

private:
	unsigned char m_unmodelled_004[0x74 - 4];
	ObjectID m_id;
	unsigned char m_unmodelled_078[0x88 - 0x78];
	Object *m_nextObject;
	unsigned char m_unmodelled_08C[0x200 - 0x8C];
	BodyModuleInterface *m_body;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
	Object *getFirstObject();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void changeBridgeState(PathfindLayerEnum layer, Bool open);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	Pathfinder *pathfinder() const { return m_pathfinder; }

private:
	unsigned char m_unmodelled_000[0x0C];
	Pathfinder *m_pathfinder;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class TerrainLogic
{
public:
	virtual void anchor00(); virtual void anchor04(); virtual void anchor08(); virtual void anchor0C();
	virtual void anchor10(); virtual void anchor14(); virtual void anchor18(); virtual void anchor1C();
	virtual void anchor20(); virtual void anchor24(); virtual void anchor28(); virtual void anchor2C();
	virtual void anchor30(); virtual void anchor34(); virtual void anchor38(); virtual void anchor3C();
	virtual void anchor40(); virtual void anchor44(); virtual void anchor48(); virtual void anchor4C();
	virtual void anchor50(); virtual void anchor54(); virtual void anchor58(); virtual void anchor5C();
	virtual void anchor60(); virtual void anchor64(); virtual void anchor68(); virtual void anchor6C();
	virtual void anchor70(); virtual void anchor74(); virtual void anchor78(); virtual void anchor7C();
	virtual void anchor80(); virtual void anchor84(); virtual void anchor88(); virtual void anchor8C();
	virtual void anchor90(); virtual void anchor94(); virtual void anchor98(); virtual void anchor9C();
	virtual Bool objectInteractsWithBridgeLayer(Object *object, int layer, Bool considerBridgeHealth);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehaviorInterface
{
public:
	virtual void anchor00();
	virtual void anchor04();
	virtual void anchor08();
	virtual void anchor0C();
	virtual void anchor10();
	virtual Bool isScaffoldPresent() const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BridgeBehavior.h
class BridgeBehavior
{
public:
	static BridgeBehaviorInterface *getBridgeBehaviorInterfaceFromObject(Object *object);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	void updateDamageState();

private:
	unsigned char m_unmodelled_000[0x5C];
	BodyDamageType m_curDamageState;
	ObjectID m_bridgeObjectID;
	unsigned char m_unmodelled_064[0x74 - 0x64];
	Bool m_damageStateChanged;
	unsigned char m_unmodelled_075[0x88 - 0x75];
	PathfindLayerEnum m_layer;
};

extern GameLogic *TheGameLogic;
extern AI *TheAI;
extern TerrainLogic *TheTerrainLogic;

// ?updateDamageState@Bridge@@QAEXXZ
void Bridge::updateDamageState()
{
	m_damageStateChanged = false;
	if (m_bridgeObjectID == INVALID_ID)
		return;
	Object *bridge = TheGameLogic->findObjectByID(m_bridgeObjectID);
	if (bridge) {
		BodyDamageType damageState = bridge->getBodyModule()->getDamageState();
		BodyDamageType curState = m_curDamageState;
		if (damageState != curState) {
			m_curDamageState = damageState;
			if (damageState == BODY_RUBBLE) {
				TheAI->pathfinder()->changeBridgeState(m_layer, false);
				m_damageStateChanged = true;
				for (Object *object = TheGameLogic->getFirstObject(); object; object = object->getNextObject()) {
					if (object->getLayer() == m_layer) {
						const Bool considerBridgeHealth = false;
						if (TheTerrainLogic->objectInteractsWithBridgeLayer(object, object->getLayer(), considerBridgeHealth)) {
							DamageInfo damageInfo;
							damageInfo.in.m_damageType = DAMAGE_FALLING;
							damageInfo.in.m_deathType = DEATH_SPLATTED;
							damageInfo.in.m_sourceID = object->getID();
							damageInfo.in.m_amount = 999999.0f;
							object->attemptDamage(&damageInfo);
						}
					}
				}
			}
			if (curState == BODY_RUBBLE) {
				BridgeBehaviorInterface *behavior = BridgeBehavior::getBridgeBehaviorInterfaceFromObject(bridge);
				if (behavior == 0 || !behavior->isScaffoldPresent())
					TheAI->pathfinder()->changeBridgeState(m_layer, true);
				m_damageStateChanged = true;
			}
		}
	} else {
		m_bridgeObjectID = INVALID_ID;
	}
}

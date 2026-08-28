// cl: /DNDEBUG /MD /EHsc
// readable body of ?guardSupplyCenter@AIPlayer@@QAEXPAVTeam@@H@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp

typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void zero() { x = y = z = 0.0f; }
	void normalize();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region2D
{
	Coord2D lo;
	Coord2D hi;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Geometry.h
class GeometryInfo
{
public:
	Real getBoundingCircleRadius() const { return m_boundingCircleRadius; }
private:
	Real m_boundingCircleRadius;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
private:
	unsigned char m_unreconstructed_000[0x38];
	Coord3D m_position;
	unsigned char m_unreconstructed_044[0xbc - 0x44];
	GeometryInfo m_geometryInfo;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AIGroup
{
public:
	enum GuardMode { GUARDMODE_NORMAL };
	enum CommandSourceType { CMD_FROM_SCRIPT = 1 };
	void groupGuardPosition(const Coord3D *position, GuardMode mode,
		CommandSourceType commandSource);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AI
{
public:
	AIGroup *createGroup();
};

extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }
private:
	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;
};

#define BFME_VIRTUAL_SLOT(n) virtual void slot##n();
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	BFME_VIRTUAL_SLOT(00) BFME_VIRTUAL_SLOT(04) BFME_VIRTUAL_SLOT(08)
	BFME_VIRTUAL_SLOT(0C) BFME_VIRTUAL_SLOT(10) BFME_VIRTUAL_SLOT(14)
	BFME_VIRTUAL_SLOT(18) BFME_VIRTUAL_SLOT(1C) BFME_VIRTUAL_SLOT(20)
	BFME_VIRTUAL_SLOT(24) BFME_VIRTUAL_SLOT(28) BFME_VIRTUAL_SLOT(2C)
	BFME_VIRTUAL_SLOT(30) BFME_VIRTUAL_SLOT(34) BFME_VIRTUAL_SLOT(38)
	BFME_VIRTUAL_SLOT(3C) BFME_VIRTUAL_SLOT(40) BFME_VIRTUAL_SLOT(44)
	virtual Player *getSkirmishEnemyPlayer();
};
#undef BFME_VIRTUAL_SLOT

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	void guardSupplyCenter(Team *team, Int minSupplies);
	Bool isSupplySourceAttacked();
	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);
protected:
	Object *findSupplyCenter(Int minSupplies);
private:
	unsigned char m_unreconstructed_000[0x6c];
	Int m_supplySourceAttackCheckFrame;
	Int m_attackedSupplyCenter;
};

void AIPlayer::guardSupplyCenter(Team *team, Int minSupplies)
{
	m_supplySourceAttackCheckFrame = 0;
	Object *warehouse = 0;
	if (isSupplySourceAttacked())
		warehouse = TheGameLogic->findObjectByID(m_attackedSupplyCenter);
	if (!warehouse)
		warehouse = findSupplyCenter(minSupplies);
	if (warehouse)
	{
		AIGroup *theGroup = TheAI->createGroup();
		if (!theGroup)
			return;
		team->getTeamAsAIGroup(theGroup);
		const Coord3D *warehousePosition = warehouse->getPosition();
		Coord3D location;
		location.x = warehousePosition->x;
		location.y = warehousePosition->y;
		location.z = warehousePosition->z;
		Region2D bounds;
		Int enemyNdx = TheScriptEngine->getSkirmishEnemyPlayer()->getPlayerIndex();
		getPlayerStructureBounds(&bounds, enemyNdx);
		Coord3D offset;
		offset.zero();
		offset.x = location.x - (bounds.lo.x + bounds.hi.x) * 0.5f;
		offset.y = location.y - (bounds.lo.y + bounds.hi.y) * 0.5f;
		offset.normalize();
		Real radius = warehouse->getGeometryInfo().getBoundingCircleRadius() * 0.8f;
		location.x -= offset.x * radius;
		location.y -= offset.y * radius;
		theGroup->groupGuardPosition(&location, AIGroup::GUARDMODE_NORMAL,
			AIGroup::CMD_FROM_SCRIPT);
	}
}

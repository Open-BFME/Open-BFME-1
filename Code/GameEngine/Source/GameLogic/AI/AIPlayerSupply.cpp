// cl: /DNDEBUG /MD /EHsc
// readable body of ?checkForSupplyCenter@AIPlayer@@IAEXPAVBuildListInfo@@PAVObject@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
// readable body of ?guardSupplyCenter@AIPlayer@@QAEXPAVTeam@@H@Z: Code/GameEngine/Source/GameLogic/AI/AIPlayer.cpp
//
// Open-BFME: the two AIPlayer members that deal with supply centres.
//
//   ?checkForSupplyCenter@  0x00162410, 259 bytes
//   ?guardSupplyCenter@     0x001668C0, 269 bytes
//
// One marks a supply centre when it is built, the other defends one that is
// already there. checkForSupplyCenter is called with a finished building: if it
// carries a SupplyCenterDockUpdate module it flags the build-list entry as a
// supply building and writes the gatherer counts, choosing the desired count
// from the AI side-info list by side name and difficulty. guardSupplyCenter
// picks the warehouse to defend -- the one under attack if there is one,
// otherwise the nearest with enough supplies -- turns the team into an AIGroup
// and posts it on the side of the warehouse AWAY from the enemy's structure
// bounds, one bounding radius times 0.8 back along that direction.
//
// Three classes were declared twice and each pair was a different slice:
//
//   Player  -- the player index at +0x24 in one, the side string at +0x28 in
//              the other, neither knowing about the other's field.
//   AI      -- the data pointer at +0x14 in one, createGroup() in the other.
//   Object  -- findUpdateModule in one, the position at +0x38 and the geometry
//              at +0xBC in the other.
//
// AIPlayer itself came in two slices that agree and do not overlap: the player
// at +0x0C and the difficulty at +0x2C, against the supply-attack check frame at
// +0x6C and the attacked centre's id at +0x70. The player at +0x0C is the same
// field AIPlayerDozer.cpp reaches, and the AI data pointer at +0x14 is the same
// one AIGroupAttackMoveOrder.cpp reaches.
//
// guardSupplyCenter is also the caller that confirms AIGroup::groupGuardPosition's
// enums really are nested in AIGroup: it spells them AIGroup::GUARDMODE_NORMAL
// and AIGroup::CMD_FROM_SCRIPT at the call site, which is the other side of the
// `W4GuardMode@1@` decoration AIGroupForwardedOrders.cpp had to reproduce.
//
// One deliberate oddity is kept verbatim: checkForSupplyCenter reads the player
// pointer back through a `void *volatile` at this+0x0c rather than through
// m_player, because VC7 otherwise folds the loop's address calculation into a
// shorter form than retail's.

typedef bool Bool;
typedef int Int;
typedef float Real;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum GameDifficulty { DIFFICULTY_EASY, DIFFICULTY_NORMAL, DIFFICULTY_HARD };

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	Int compare(const AsciiString &other) const;
	Bool operator==(const AsciiString &other) const { return compare(other) == 0; }
private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
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
	class OCLUpdate *findUpdateModule(NameKeyType key);
	const Coord3D *getPosition() const { return &m_position; }
	const GeometryInfo &getGeometryInfo() const { return m_geometryInfo; }
private:
	unsigned char m_unreconstructed_000[0x38];
	Coord3D m_position;					// +0x38
	unsigned char m_unreconstructed_044[0xbc - 0x44];
	GeometryInfo m_geometryInfo;				// +0xBC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	Object *findObjectByID(Int id);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/SidesList.h
class BuildListInfo
{
public:
	void setSupplyBuilding(Bool value) { m_supplyBuilding = value; }
	void setDesiredGatherers(Int value) { m_desiredGatherers = value; }
	void setCurrentGatherers(Int value) { m_currentGatherers = value; }
private:
	unsigned char m_unreconstructed_000[0x7c];
	Bool m_supplyBuilding;					// +0x7C
	unsigned char m_unreconstructed_07d[3];
	Int m_desiredGatherers;					// +0x80
	Int m_currentGatherers;					// +0x84
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	Int getPlayerIndex() const { return m_playerIndex; }

	unsigned char m_unreconstructed_000[0x24];
	Int m_playerIndex;					// +0x24
	AsciiString m_side;					// +0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AISideInfo
{
public:
	void *m_vtable;
	AsciiString m_side;
	Int m_easy;
	Int m_normal;
	Int m_hard;
	unsigned char m_unreconstructed_014[0x1bc - 0x14];
	AISideInfo *m_next;					// +0x1BC
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class TAiData
{
public:
	unsigned char m_pad00[4];
	float m_structureSeconds;
	float m_teamSeconds;
	int m_resourcesWealthy;
	int m_resourcesPoor;
	unsigned int m_forceIdleFramesCount;
	float m_structuresWealthyMod;
	float m_teamWealthyMod;
	float m_structuresPoorMod;
	float m_teamPoorMod;
	float m_teamResourcesToBuild;
	float m_guardInnerModifierAI;
	float m_guardOuterModifierAI;
	float m_guardInnerModifierHuman;
	float m_guardOuterModifierHuman;
	unsigned int m_guardChaseUnitFrames;
	unsigned int m_guardEnemyScanRate;
	unsigned int m_guardEnemyReturnScanRate;
	float m_wallHeight;
	float m_alertRangeModifier;
	float m_aggressiveRangeModifier;
	float m_attackPriorityDistanceModifier;
	float m_skirmishGroupFudgeValue;
	float m_maxRecruitDistance;
	float m_repulsedDistance;
	unsigned char m_enableRepulsors;
	unsigned char m_forceSkirmishAI;
	unsigned char m_rotateSkirmishBases;
	unsigned char m_attackUsesLineOfSight;
	unsigned char m_attackIgnoreInsignificantBuildings;
	unsigned char m_pad69[3];
	float m_minDistanceForGroup;
	unsigned char m_pad70[4];
	float m_minClumpDensity;
	int m_infantryPathfindDiameter;
	int m_vehiclePathfindDiameter;
	int m_rebuildDelaySeconds;
	float m_supplyCenterSafeRadius;
	float m_aiDozerBoredRadiusModifier;
	unsigned char m_aiCrushesInfantry;
	unsigned char m_pad8d[0xEC - 0x8d];
	AISideInfo *m_sideInfo;					// +0xEC
};

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
	TAiData *getAiData() const { return m_aiData; }
	AIGroup *createGroup();
private:
	unsigned char m_unreconstructed_000[0x14];
	TAiData *m_aiData;					// +0x14
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

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameLogic *TheGameLogic;
extern ScriptEngine *TheScriptEngine;
extern AI *TheAI;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPlayer.h
class AIPlayer
{
public:
	void guardSupplyCenter(Team *team, Int minSupplies);
	Bool isSupplySourceAttacked();
	static void getPlayerStructureBounds(Region2D *bounds, Int playerIndex);

protected:
	void checkForSupplyCenter(BuildListInfo *info, Object *bldg);
	Object *findSupplyCenter(Int minSupplies);

private:
	unsigned char m_unreconstructed_000[0x0c];
	Player *m_player;					// +0x0C
	unsigned char m_unreconstructed_010[0x2c - 0x10];
	GameDifficulty m_difficulty;				// +0x2C
	unsigned char m_unreconstructed_030[0x6c - 0x30];
	Int m_supplySourceAttackCheckFrame;			// +0x6C
	Int m_attackedSupplyCenter;				// +0x70
};

void AIPlayer::checkForSupplyCenter(BuildListInfo *info, Object *bldg)
{
	if (info)
	{
		if (bldg)
		{
			static const NameKeyType key_centerUpdate =
				TheNameKeyGenerator->nameToKey("SupplyCenterDockUpdate");
			OCLUpdate *centerModule = bldg->findUpdateModule(key_centerUpdate);
			if (centerModule)
			{
				info->setSupplyBuilding(true);
				Int desiredGatherers = 0;
				const AISideInfo *resInfo = TheAI->getAiData()->m_sideInfo;
				if (resInfo)
				{
					// VC7 otherwise folds this into a shorter non-retail address calculation.
					void *playerStorage = *reinterpret_cast<void *volatile *>(
						reinterpret_cast<char *>(this) + 0x0c);
					const AsciiString *side = reinterpret_cast<const AsciiString *>(
						reinterpret_cast<char *>(playerStorage) + 0x28);
					do
					{
						if (resInfo->m_side == *side)
						{
							GameDifficulty difficulty = m_difficulty;
							if (difficulty == DIFFICULTY_EASY)
								desiredGatherers = resInfo->m_easy;
							if (difficulty == DIFFICULTY_NORMAL)
								desiredGatherers = resInfo->m_normal;
							if (difficulty == DIFFICULTY_HARD)
								desiredGatherers = resInfo->m_hard;
						}
						resInfo = resInfo->m_next;
					} while (resInfo);
				}

				info->setSupplyBuilding(true);
				info->setCurrentGatherers(-1);
				info->setDesiredGatherers(desiredGatherers + 1);
			}
		}
	}
}

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

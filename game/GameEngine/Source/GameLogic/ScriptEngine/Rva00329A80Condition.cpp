// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/Common/Thing /Igame/GameEngine/Source/Common /Igame/GameEngine/Source/GameLogic /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// RVA 00329A80: dispatcher-proven unit/filtered-object path query.
// The semantic condition and kind bit119 names remain unproven. Native
// filter temporary lifetime matches 00329C20; this is a member with RET8,
// not a free cdecl function. Both positions use canonical Object+38.
#define ASCIISTRING_H
#include "ascii_string.h"
#define __THING_H_
#define __KINDOF_H_
#include "PreRTS.h"
#include "Common/BitFlags.h"

enum KindOfType { RVA00329A80_KIND_BIT_119 = 119 };
typedef BitFlags<192> KindOfMaskType;
typedef bool Bool;
typedef unsigned short PlayerMaskType;
enum DistanceCalculationType { FROM_CENTER_2D = 0 };

#define BFME_HAVE_COORD3D
#define OBJECT_TU_MEMBERS \
	const Coord3D *getPosition(void) const { return &m_cachedPos; }
#include "object.h"

class Parameter
{
public:
	const AsciiString &getString(void) const
	{
		return *(const AsciiString *)((const char *)this + 0x10);
	}
};

class Player;
class PlayerList
{
public:
	Player *getPlayerFromMask(PlayerMaskType mask);
};

class PartitionFilter
{
public:
	PartitionFilter() : m_next(0) {}
	virtual ~PartitionFilter() {}
	virtual Bool allow(Object *object) = 0;
	PartitionFilter *link(PartitionFilter *next);
	PartitionFilter *m_next;
};

class PartitionFilterPlayer : public PartitionFilter
{
public:
	PartitionFilterPlayer(const Player *player, Bool match)
		: m_player(player), m_match(match) {}
	virtual ~PartitionFilterPlayer() {}
	virtual Bool allow(Object *object);
private:
	const Player *m_player;
	Bool m_match;
};

class PartitionFilterAcceptByKindOf : public PartitionFilter
{
public:
	PartitionFilterAcceptByKindOf(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear);
	virtual ~PartitionFilterAcceptByKindOf() {}
	virtual Bool allow(Object *object);
private:
	KindOfMaskType m_mustBeSet;
	KindOfMaskType m_mustBeClear;
};

class PartitionManager
{
public:
	Object *getClosestObject(const Coord3D *position, float maxDistance,
		DistanceCalculationType calculation, PartitionFilter *filter);
};

class Pathfinder
{
public:
	Bool slowDoesPathExist(Object *object, const Coord3D *from,
		const Coord3D *to, ObjectID blocker);
};

class AI
{
public:
	Pathfinder *pathfinder(void)
	{
		return *(Pathfinder **)((char *)this + 0x0c);
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual Object *getUnitNamed(Parameter *) = 0;
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern PartitionManager *ThePartitionManager;
extern AI *TheAI;

class ScriptConditions { protected: Bool evaluateRva00329A80(Parameter*,Parameter*); };
Bool ScriptConditions::evaluateRva00329A80(Parameter *unitParm, Parameter *playerParm)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitParm);
	if (!unit) return false;

	PlayerMaskType mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(playerParm->getString(), 0);
	Player *player = ThePlayerList->getPlayerFromMask(mask);
	if (player) return false;

	Object *candidate;
	{
		PartitionFilterPlayer playerFilter(0, true);
		KindOfMaskType mustBeSet(KindOfMaskType::kInit,
			RVA00329A80_KIND_BIT_119);
		candidate = ThePartitionManager->getClosestObject(unit->getPosition(),
			1000000.0f, FROM_CENTER_2D,
			PartitionFilterAcceptByKindOf(mustBeSet, KINDOFMASK_NONE)
				.link(&playerFilter));
	}
	if (!candidate) return false;

	return TheAI->pathfinder()->slowDoesPathExist(
		unit, unit->getPosition(), candidate->getPosition(), (ObjectID)0);
}

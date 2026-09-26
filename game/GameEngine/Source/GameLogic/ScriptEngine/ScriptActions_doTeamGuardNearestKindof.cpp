// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// The action template at index 400 names TEAM_GUARD_NEAREST_KINDOF.
// Retail RVA 0x002FCC90 finds the nearest object with the requested kind bit
// for each player, then makes the team guard the closest result.

extern "C" double sqrt(double value);

#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

// This declaration keeps the one-pointer BFME AsciiString layout.
#include "ascii_string.h"

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void sub(const Coord3D *other)
	{
		x -= other->x;
		y -= other->y;
		z -= other->z;
	}

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

// BFME uses STLport's bitset for its 192-bit KindOfMaskType.
template <int NUMBITS>
class BitFlags
{
	_STL::bitset<NUMBITS> m_bits;

public:
	enum BogusInitType { kInit = 0 };

	BitFlags()
	{
	}

	BitFlags(BogusInitType, int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}

	void clear()
	{
		m_bits.reset();
	}

	void set(int bit)
	{
		m_bits._Unchecked_set((size_t)bit);
	}
};

typedef BitFlags<192> KindOfMaskType;

class Object
{
public:
	char m_beforePosition[0x38];
	Coord3D m_position;
};

class Player
{
};

class BfmeFindClosestCall
{
};

extern void j_0001b685(void);

static Object *findClosestByKindOf(Player *player, const Coord3D *position,
	KindOfMaskType setMask, KindOfMaskType clearMask)
{
	typedef Object *(BfmeFindClosestCall::*Function)(const Coord3D *,
		KindOfMaskType, KindOfMaskType);
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_0001b685;
	return (reinterpret_cast<BfmeFindClosestCall *>(player)->*function.member)(
		position, setMask, clearMask);
}

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class AIGroup
{
public:
	enum GuardMode
	{
		GUARDMODE_NORMAL = 0
	};
	enum CommandSourceType
	{
		CMD_FROM_PLAYER = 0,
		CMD_FROM_SCRIPT = 1
	};
};

class BfmeGroupGuardObjectCall
{
public:
	void groupGuardObject(Object *object, AIGroup::GuardMode guardMode,
		AIGroup::CommandSourceType commandSource);
};

class AI
{
public:
	AIGroup *createGroup();
};

class Team
{
};

class BfmeTeamEstimatePositionCall
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *position) const;
};

class BfmeTeamAsAIGroupCall
{
public:
	void getTeamAsAIGroup(AIGroup *group);
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
extern AI *TheAI;
extern void j_00022ec1(void);
extern void j_000241fe(void);
extern void j_0003257e(void);

static __forceinline Coord3D *bfmeGetEstimateTeamPosition(Team *team,
	Coord3D *position)
{
	typedef Coord3D *(BfmeTeamEstimatePositionCall::*Function)(Coord3D *) const;
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_000241fe;
	return (reinterpret_cast<const BfmeTeamEstimatePositionCall *>(team)->*
		function.member)(position);
}

static __forceinline void bfmeGetTeamAsAIGroup(Team *team, AIGroup *group)
{
	typedef void (BfmeTeamAsAIGroupCall::*Function)(AIGroup *);
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_00022ec1;
	(reinterpret_cast<BfmeTeamAsAIGroupCall *>(team)->*function.member)(group);
}

static __forceinline void bfmeGroupGuardObject(AIGroup *group,
	Object *object, AIGroup::GuardMode guardMode,
	AIGroup::CommandSourceType commandSource)
{
	typedef void (BfmeGroupGuardObjectCall::*Function)(Object *,
		AIGroup::GuardMode, AIGroup::CommandSourceType);
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_0003257e;
	(reinterpret_cast<BfmeGroupGuardObjectCall *>(group)->*function.member)(
		object, guardMode, commandSource);
}

class ScriptActions
{
protected:
	void doTeamGuardNearestKindof(const AsciiString &teamName, int kindofBit);
};

void ScriptActions::doTeamGuardNearestKindof(const AsciiString &teamName,
	int kindofBit)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (theTeam)
	{
		Coord3D position;
		bfmeGetEstimateTeamPosition(theTeam, &position);
		Object *closestObject = 0;
		Real closestDistance = 99999.0f;
		PlayerMaskType playerMask = 0xffff;

		for (;;)
		{
			Player *player =
				ThePlayerList->getEachPlayerFromMask(playerMask);
			KindOfMaskType kindofMask(KindOfMaskType::kInit, kindofBit);
			{
				Object *object = findClosestByKindOf(player, &position,
					kindofMask, KINDOFMASK_NONE);
				if (object)
				{
					Coord3D distance;
					distance.x = object->m_position.x;
					distance.y = object->m_position.y;
					distance.z = object->m_position.z;
					distance.sub(&position);
					Real objectDistance = distance.length();
					if (!closestObject || objectDistance < closestDistance)
					{
						closestObject = object;
						closestDistance = objectDistance;
					}
				}
			}
			if (playerMask == 0)
				break;
		}

		if (closestObject)
		{
			AIGroup *theGroup = TheAI->createGroup();
			if (theGroup)
			{
				bfmeGetTeamAsAIGroup(theTeam, theGroup);
				bfmeGroupGuardObject(theGroup, closestObject,
					AIGroup::GUARDMODE_NORMAL, AIGroup::CMD_FROM_SCRIPT);
			}
		}
	}
}

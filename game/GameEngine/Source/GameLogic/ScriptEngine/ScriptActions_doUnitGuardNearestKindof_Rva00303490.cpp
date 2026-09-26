// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// ScriptActions::doUnitGuardNearestKindof, retail RVA 0x00303490 (381B).
// The executeAction arm for action-template 401 names this action
// UNIT_GUARD_NEAREST_KINDOF: it resolves the named unit, finds the closest
// object carrying the requested kind bit for each player, and gives the unit
// an ordinary script guard order for the closest result.

extern "C" double sqrt(double value);

#include <bitset>

typedef bool Bool;
typedef float Real;
typedef unsigned short PlayerMaskType;
typedef unsigned int UnsignedInt;

// This declaration keeps the one-pointer BFME AsciiString layout.  The
// getUnitNamed slot takes the script parameter by reference, so no temporary
// StringBase copy or cleanup is part of this body.
#include "ascii_string.h"

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

// BFME uses STLport's bitset for its 192-bit KindOfMaskType.  The explicit
// kInit constructor is the source-level form used by the retail action: the
// compiler sets one requested bit in the six-word temporary before passing it
// to Player::findClosestByKindOf.
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
	char m_betweenPositionAndAI[0x1c0];
	class AIUpdateInterface *m_ai; // retail Object+0x204
};

class Player
{
};

// The body at 0x000CFD20 is the canonical Player::findClosestByKindOf.  The
// caller's ILT is 0x0001B685; retaining that typed thunk preserves the retail
// relocation without claiming the neutral j_ name as a second global owner.
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

class AICommandInterface
{
};

class AIUpdateInterface
{
public:
	char m_beforeCommands[0x20];
	AICommandInterface m_command;
};

// ILT 0x00014FDD reaches the canonical AICommandInterface::aiGuardObject body
// at 0x00154670.  This target is called with Object*, GuardMode=0 and
// CMD_FROM_SCRIPT=1; the TU-local type records the real thiscall/stack ABI while
// avoiding an additional alias pin for the overloaded thunk spelling.
class BfmeGuardObjectCall
{
public:
	void aiGuardObject(Object *object, int guardMode, int commandSource);
};

extern void j_00014fdd(void);

static __forceinline void bfmeGuardObject(AICommandInterface *commands,
	Object *object)
{
	typedef void (BfmeGuardObjectCall::*Function)(Object *, int, int);
	union
	{
		void (*raw)(void);
		Function member;
	} function;
	function.raw = j_00014fdd;
	(reinterpret_cast<BfmeGuardObjectCall *>(commands)->*function.member)(
		object, 0, 1);
}

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
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual Object *getUnitNamed(const AsciiString &name) = 0;
};

extern const KindOfMaskType KINDOFMASK_NONE;
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
	void doUnitGuardNearestKindof(const AsciiString &unitName, int kindofBit);
};

void ScriptActions::doUnitGuardNearestKindof(const AsciiString &unitName,
	int kindofBit)
{
	Object *theUnit = TheScriptEngine->getUnitNamed(unitName);
	if (theUnit)
	{
		Object *closestObject = 0;
		Real closestDistance = 99999.0f;
		PlayerMaskType playerMask = 0xffff;

		for (;;)
		{
			Player *player =
				ThePlayerList->getEachPlayerFromMask(playerMask);
			KindOfMaskType kindofMask(KindOfMaskType::kInit, kindofBit);
			{
				Object *object = findClosestByKindOf(player, &theUnit->m_position,
					kindofMask, KINDOFMASK_NONE);
				if (object)
				{
					Coord3D distance;
					distance.x = object->m_position.x;
					distance.y = object->m_position.y;
					distance.z = object->m_position.z;
					distance.sub(&theUnit->m_position);
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
			AIUpdateInterface *ai = theUnit->m_ai;
			if (ai)
				bfmeGuardObject(&ai->m_command, closestObject);
		}
	}
}

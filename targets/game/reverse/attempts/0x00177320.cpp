// ?d_00177320@@YAXXZ
// partial score=0.99383 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// probe: python tools/probe.py <this file> "?update@Rva00177320State@@UAE?AW4StateReturnType@@XZ" 0x00177320

// Open-BFME: unnamed AIInternalMoveToState-derived State::update() override,
// retail 0x00177320, 486 bytes, served as game/gen_asm/d_00177320.asm. No
// direct named caller (reached only through StateMachine's virtual update
// dispatch), so this stays address-kept; the base-class call through ILT
// 0x000488F6 to retail 0x00172E70 (AIInternalMoveToState::update) is real and
// proves the inheritance. Zero Hour's AIAttackApproachTargetState::updateInternal
// (AIStates.cpp) is the twin family: goal-destroyed early-out, victim checks,
// setCurrentVictim, computePath() == false -> failure, base update, any
// non-continue result normalised to success.
//
// Shape: if the state machine's goal object was destroyed, notify the AI
// (virtual slot +0x204), clear the victim and fail (-2). Otherwise clear status
// bit 28 on the owner. A goal that is hidden (status94 bit 0x40000) or
// stealthed-and-undetected fails; a crushable goal with the owner predicate at
// 0x001C7530 switches the machine (virtual slot +0x20) to state 0xE9 and
// continues (0). A weapon in range succeeds (-1) unless the AI has a path
// (+0x140) and TheAI's pathfinder (+0x0C, 0x003E5E40) reports false. Then the
// victim is set; without a path the goal position is cached at +0x54 and a
// 2D distance below TheAI data (+0x14) fields +0x94 + +0x90 succeeds. Past the
// CRC-desync log gate, computePath (virtual slot +0x44) false fails, else the
// base update runs.
//
// Remaining residue (3 bytes): retail keeps the TheAI data pointer in ESI, this
// source in EDI. See build/r177320 in the seat that banked it.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

template <int NUMBITS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, int index)
	{
		m_bits.set(index);
	}
	BitFlags() {}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType86;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

struct Coord3D
{
	Real x, y, z;
	void set(Real a, Real b, Real c) { x=a; y=b; z=c; }
	void set(const Coord3D *p) { x = p->x; y = p->y; z = p->z; }
	Real length(void) const;					// ?length@Coord3D@@QBEMXZ, real landed
};

class Player;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const void *player) const;	// ILT 0x00003B1B
};

class Weapon
{
public:
	Bool isWithinAttackRange(const void *source, const void *target, Int extra) const; // real, Weapon_isWithinAttackRange.cpp
};

class AIUpdateInterfaceLike : public BFMEVirtualSlots<129>
{
public:
	virtual void notifyVictimIsDead(void) = 0;			// vtable +0x204
	void setCurrentVictim(const class Object *victim);		// ILT 0x0004AB4C

	char m_bfmeUnreconstructed_004[0x140 - 0x04];
	void *m_bfmeField140;						///< retail this+0x140
};

class Object
{
public:
	Player *getControllingPlayer(void) const;			// ILT 0x00020824
	void *getCurrentWeapon(void *slotType);			// ILT 0x00031A7F
	Bool crushPolicy(Object *other, Int testType) const;		// ILT 0x000420AA
	void setStatus(const ObjectStatusMaskType86 &mask, Bool value);	// ILT 0x000307E7
	Bool rva001c7530(void) const;					// ABI-only pin, retail 0x001C7530
	const Coord3D *getPosition(void) const { return &m_position; }
	AIUpdateInterfaceLike *getAI(void) { return (AIUpdateInterfaceLike *)m_bfmeAi; }

	char m_bfmeUnreconstructed_000[0x38];
	Coord3D m_position;						///< retail this+0x38
	char m_bfmeUnreconstructed_44[0x94 - 0x44];
	UnsignedInt m_bfmeStatus94;					///< retail this+0x94
	char m_bfmeUnreconstructed_98[0x204 - 0x98];
	void *m_bfmeAi;						///< retail this+0x204
};

class StateMachine : public BFMEVirtualSlots<8>
{
public:
	virtual StateReturnType setState(UnsignedInt id) = 0;	// vtable +0x20
	Bool isGoalObjectDestroyed(void) const;			// ILT 0x0000432C
	Object *getGoalObject(void) const;				// ILT 0x0000E570
	Object *getOwner(void) { return m_owner; }

	char m_bfmeUnreconstructed_004[0x10 - 0x04];
	Object *m_owner;						///< retail this+0x10
};

class TheAISubA
{
public:
	Bool rva003e5e40(const Object *owner);				// ABI-only pin, retail 0x003E5E40
};

class TheAISubB
{
public:
	char m_bfmeUnreconstructed_000[0x90];
	Real m_bfmeRangeA;						///< retail this+0x90
	Real m_bfmeRangeB;						///< retail this+0x94
};

class AIGlobal
{
public:
	char m_bfmeUnreconstructed_000[0x0C];
	TheAISubA *m_bfmeSubA;						///< retail this+0x0C
	char m_bfmeUnreconstructed_010[0x14 - 0x10];
	TheAISubB *m_bfmeSubB;						///< retail this+0x14
};

extern AIGlobal *TheAI;						// 0x012EF214
extern Bool Glo012F0239;						// 0x012F0239
extern void *TheCRCParameterCheck;					// 0x012ED4FC

extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...); // 0x0003A17A

class AIInternalMoveToState : public BFMEVirtualSlots<17>
{
public:
	virtual Bool computePath(void);					// vtable +0x44
	virtual StateReturnType update(void);				// real, retail 0x00172E70
};

class Rva00177320State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update(void);

	StateMachine *getMachine(void) { return m_bfmeMachine; }
	Object *getMachineOwner(void) { return m_bfmeMachine->getOwner(); }
	Object *getMachineGoalObject(void) { return m_bfmeMachine->getGoalObject(); }

	char m_bfmeUnreconstructed_004[0x1C - 0x04];
	StateMachine *m_bfmeMachine;					///< retail this+0x1C
	char m_bfmeUnreconstructed_020[0x54 - 0x20];
	Coord3D m_bfmeCachedGoalPos;					///< retail this+0x54
};

StateReturnType Rva00177320State::update(void)
{
	Object *owner = getMachineOwner();
	AIUpdateInterfaceLike *ai = owner->getAI();
	if (getMachine()->isGoalObjectDestroyed())
	{
		ai->notifyVictimIsDead();
		ai->setCurrentVictim(0);
		return STATE_FAILURE;
	}

	owner->setStatus(ObjectStatusMaskType86(ObjectStatusMaskType86::kInit, 28), false);

	StateReturnType result = STATE_FAILURE;
	Object *goal = getMachineGoalObject();
	if (goal)
	{
		if (goal->m_bfmeStatus94 & 0x40000)
			return STATE_FAILURE;
		if (reinterpret_cast<const BFMEObjectStealthQuery *>(goal)->isStealthedAndUndetected(owner->getControllingPlayer()))
			return STATE_FAILURE;
		if (owner->crushPolicy(goal, 2) && owner->rva001c7530())
		{
			getMachine()->setState(0xe9);
			return STATE_CONTINUE;
		}

		Weapon *weapon = reinterpret_cast<Weapon *>(owner->getCurrentWeapon(0));
		if (weapon && weapon->isWithinAttackRange(owner, goal, 0))
		{
			Bool losOk = TheAI->m_bfmeSubA->rva003e5e40(owner);
			if (!ai->m_bfmeField140 || losOk)
				return STATE_SUCCESS;
		}

		ai->setCurrentVictim(goal);
		if (!ai->m_bfmeField140)
		{
			m_bfmeCachedGoalPos = *goal->getPosition();
			const Coord3D *goalPos = &m_bfmeCachedGoalPos;
			TheAISubB *data = TheAI->m_bfmeSubB;
			Coord3D diff;
			diff.set(owner->getPosition());
			diff.x -= goalPos->x;
			diff.y -= goalPos->y;
			diff.z = 0;
			if (diff.length() < data->m_bfmeRangeB + data->m_bfmeRangeA)
				return STATE_SUCCESS;
		}

		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath20");

		if (computePath() == false)
			return STATE_FAILURE;
		result = AIInternalMoveToState::update();
		if (result != STATE_CONTINUE)
			return STATE_SUCCESS;
	}
	return result;
}

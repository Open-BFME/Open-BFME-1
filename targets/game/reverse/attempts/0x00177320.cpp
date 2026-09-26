// ?d_00177320@@YAXXZ
// partial score=0.38 date=2026-09-22
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: unnamed AIInternalMoveToState-derived State::update() override,
// retail 0x00177320, 486 bytes, served as Code/gen_asm/d_00177320.asm. No
// direct named caller (reached only through StateMachine's virtual update
// dispatch), so this lands address-kept; the base-class call at retail
// 0x00172E70 (?update@AIInternalMoveToState@@UAE?AW4StateReturnType@@XZ) is
// real and proves the inheritance. The neighbouring already-landed
// Rva00177A40State::onExit (Rva00177A40State_onExit.cpp) shows the same
// ObjectStatusMaskType bit-28 clear/set idiom, but that file's m_machine sits
// at +0x18 while this body reads its own machine pointer at +0x1c, so the two
// are NOT assumed to share one layout -- every field here is measured from
// this body's own bytes only.
//
// Shape: if the state machine's goal object was destroyed, clear the victim
// (through a still-dump virtual slot) and continue (-2). Otherwise clear
// status bit 28 on the owner. If there is no goal, or the goal is
// dead/hidden-from-us (status94 bit 0x40000) or stealthed-and-undetected, or
// we can crush/squish it and a still-dump owner predicate at 0x001C7530
// agrees, transition the state machine (virtual slot +0x20) to state 0xE9 and
// succeed (0). Otherwise look for a weapon in attack range plus a
// TheAI-derived line-of-sight-ish helper (still-dump 0x003E5E40), or fall
// back to a cached-position distance-vs-threshold check; on failure return
// -1. On success, past a debug CRC-desync log gate, defer to a self-check
// virtual slot (+0x44) and either continue (-2) or hand off to
// AIInternalMoveToState::update(), normalising any non-zero result to -1.

#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
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

struct Coord3D
{
	Real x, y, z;
	Real length(void) const;					// ?length@Coord3D@@QBEMXZ, real landed
};

class Player;
// (ObjectStatusMaskType86 declared above)

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

class Object
{
public:
	Player *getControllingPlayer(void) const;			// ILT 0x00020824
	void *getCurrentWeapon(void *slotType);			// ILT 0x00031A7F
	Bool crushPolicy(Object *other, Int testType) const;		// ILT 0x000420AA
	void setStatus(const ObjectStatusMaskType86 &mask, Bool value);	// ILT 0x000307E7
	Bool rva001c7530(void) const;					// ABI-only pin, retail 0x001C7530

	char m_bfmeUnreconstructed_000[0x38];
	Coord3D m_position;						///< retail this+0x38
	char m_bfmeUnreconstructed_44[0x94 - 0x44];
	UnsignedInt m_bfmeStatus94;					///< retail this+0x94
	char m_bfmeUnreconstructed_98[0x204 - 0x98];
	void *m_bfmeAi;						///< retail this+0x204
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed(void) const;			// ILT 0x0000432C
	Object *getGoalObject(void) const;				// ILT 0x0000E570

	char m_bfmeUnreconstructed_000[0x10];
	Object *m_owner;						///< retail this+0x10
};

class AIUpdateInterfaceLike
{
public:
	void setCurrentVictim(const Object *victim);			// ILT 0x0004AB4C

	char m_bfmeUnreconstructed_000[0x140];
	void *m_bfmeField140;						///< retail this+0x140
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

enum StateReturnType { STATE_RETURN_PLACEHOLDER = 0 };

class AIInternalMoveToState
{
public:
	virtual StateReturnType update(void);				// real, retail 0x00172E70
};

class Rva00177320State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update(void);

	char m_bfmeUnreconstructed_004[0x1C - 0x04];
	StateMachine *m_bfmeMachine;					///< retail this+0x1C
	char m_bfmeUnreconstructed_020[0x54 - 0x20];
	Coord3D m_bfmeCachedGoalPos;					///< retail this+0x54
};

// Raw vtable-slot calls use MSVC's plain (single, non-virtual, no-base)
// pointer-to-member representation, which is just the code address, to reach
// __thiscall without the reserved __thiscall keyword on a free function type.
struct VSlotHelperVoid0 { void call(void); };
struct VSlotHelperBool0 { Bool call(void); };
struct VSlotHelperVoid1Int { void call(Int); };

typedef void (VSlotHelperVoid0::*VSlotVoidFn)(void);
typedef Bool (VSlotHelperBool0::*VSlotBoolFn)(void);
typedef void (VSlotHelperVoid1Int::*VSlotSetStateFn)(Int);

// ?rva00177320@Rva00177320State@@UAEHXZ (StateReturnType via Int-sized ABI)
StateReturnType Rva00177320State::update(void)
{
	StateMachine *machine = m_bfmeMachine;
	Object *owner = machine->m_owner;
	AIUpdateInterfaceLike *ai = reinterpret_cast<AIUpdateInterfaceLike *>(owner->m_bfmeAi);

	if (machine->isGoalObjectDestroyed())
	{
		void **vtbl = *reinterpret_cast<void ***>(ai);
		VSlotVoidFn slot204;
		*reinterpret_cast<void **>(&slot204) = vtbl[0x204 / 4];
		(reinterpret_cast<VSlotHelperVoid0 *>(ai)->*slot204)();
		ai->setCurrentVictim(0);
		return (StateReturnType)-2;
	}

	owner->setStatus(ObjectStatusMaskType86(ObjectStatusMaskType86::kInit, 28), false);

	machine = m_bfmeMachine;
	Object *goal = machine->getGoalObject();
	if (!goal)
		return (StateReturnType)-2;

	if (goal->m_bfmeStatus94 & 0x40000)
		goto continueState;

	{
		Player *player = owner->getControllingPlayer();
		if (reinterpret_cast<const BFMEObjectStealthQuery *>(goal)->isStealthedAndUndetected(player))
			goto continueState;
	}

	if (owner->crushPolicy(goal, 2) && owner->rva001c7530())
	{
		void **mvtbl = *reinterpret_cast<void ***>(machine);
		VSlotSetStateFn slot20;
		*reinterpret_cast<void **>(&slot20) = mvtbl[0x20 / 4];
		(reinterpret_cast<VSlotHelperVoid1Int *>(machine)->*slot20)(0xe9);
		return (StateReturnType)0;
	}

	{
		Weapon *weapon = reinterpret_cast<Weapon *>(owner->getCurrentWeapon(0));
		if (!weapon)
			goto haveNoRangedPath;
		if (!weapon->isWithinAttackRange(owner, goal, 0))
			goto haveNoRangedPath;
	}

	{
		Bool losOk = TheAI->m_bfmeSubA->rva003e5e40(owner);
		if (!ai->m_bfmeField140)
			goto haveNoRangedPath;
		if (losOk)
			goto haveNoRangedPath;

		ai->setCurrentVictim(goal);
		if (!ai->m_bfmeField140)
		{
			m_bfmeCachedGoalPos.x = goal->m_position.x;
			m_bfmeCachedGoalPos.y = goal->m_position.y;
			m_bfmeCachedGoalPos.z = goal->m_position.z;

			Coord3D diff;
			diff.x = owner->m_position.y - m_bfmeCachedGoalPos.x;
			diff.y = owner->m_position.x - m_bfmeCachedGoalPos.y;
			diff.z = 0;
			Real dist = diff.length();

			Real threshold = TheAI->m_bfmeSubB->m_bfmeRangeB + TheAI->m_bfmeSubB->m_bfmeRangeA;
			if (dist > threshold)
				return (StateReturnType)-1;
		}
	}
	goto haveRangedPath;

haveNoRangedPath:
	return (StateReturnType)-1;

continueState:
	return (StateReturnType)-2;

haveRangedPath:
	;

	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, (const char *)0x1099604);

	void **selfVtbl = *reinterpret_cast<void ***>(this);
	VSlotBoolFn slot44;
	*reinterpret_cast<void **>(&slot44) = selfVtbl[0x44 / 4];
	if (!(reinterpret_cast<VSlotHelperBool0 *>(this)->*slot44)())
		return (StateReturnType)-2;

	StateReturnType baseResult = AIInternalMoveToState::update();
	if (baseResult != 0)
		return (StateReturnType)-1;
	return baseResult;
}

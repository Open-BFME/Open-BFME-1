// ?d_00177720@@YAXXZ
// partial score=0.32 date=2026-09-22
// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME: unnamed AIInternalMoveToState-derived State::update() override,
// retail 0x00177720, 622 bytes, served as Code/gen_asm/d_00177320.asm (same
// dump file as the sibling body at 0x00177320). No direct named caller
// (reached only through StateMachine's virtual dispatch), so this lands
// address-kept; direct calls to the real AIInternalMoveToState::update
// (0x00172E70) and ::onEnter (0x00021E27) prove the inheritance, and the real
// Object::setStatusBit / AIUpdateInterface::destroyPath / AIUpdateInterface
// setCurrentVictim calls (already landed elsewhere) are reused as-is.
//
// Shape: sets the AI's range slot (+0x168) to 50.0, fetches the state
// machine's goal, and if a still-dump virtual chain off the machine's +0x1FC
// pointer agrees the goal is already handled, pokes the AI (virtual slot
// +0x1E8) and fails (-1). Otherwise: if the goal was destroyed, or (when
// alive) is already flagged dead/hidden, or fails a crush-policy/stealth
// check, jump to the "reacquire" branch. If alive and crushable-and-visible,
// set victim, self-check (virtual slot +0x44), and delegate to the base
// update(); on a non-zero result whose kind and self-check both agree, cache
// the goal's position, destroy the AI's path, set status bit 28, and
// tail-call the base onEnter(); on a zero result, or when the goal was null
// to begin with, set status bit 28 from a still-dump owner predicate and
// return that stored result. The "reacquire" branch clears the range slot,
// and if a per-state flag (+0x68) is set and the same still-dump owner
// predicate agrees, looks for a new target via a still-dump SEH-heavy helper
// at 0x0014D120, crush-tests it, tells the state machine about it (virtual
// slot +0x38), self-checks, and on success sets the flag and tail-calls the
// base update(); any failure along that path falls through to the same
// tail-call (with the flag left clear).

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
template <int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };
	BitFlags() { }
	BitFlags(_dummy_kInit, Int idx1) { m_bits.set(idx1); }
private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

class Player;

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const void *player) const;	// ILT 0x00003B1B
};

struct Coord3D
{
	Real x, y, z;
};

class Object
{
public:
	Player *getControllingPlayer(void) const;			// ILT 0x00020824
	Bool crushPolicy(Object *other, Int testType) const;		// ILT 0x000420AA
	void setStatus(const ObjectStatusMaskType &objectStatus, Bool set);	// real, ObjectStatusBits.cpp
	void setStatusBit(Int bit, Bool set);				// real, ObjectStatusBits.cpp, ILT 0x00032DEE
	Bool isKindOf(Int kind) const;					// ILT 0x0003251F
	Bool rva001c7530(void) const;					// ABI-only pin, retail 0x001C7530

	char m_bfmeUnreconstructed_000[0x70];
	Int m_bfmeField70;						///< retail this+0x70
	char m_bfmeUnreconstructed_74[0x94 - 0x74];
	UnsignedInt m_bfmeStatus94;					///< retail this+0x94
	char m_bfmeUnreconstructed_98[0x204 - 0x98];
	void *m_bfmeAi;						///< retail this+0x204
	char m_bfmeUnreconstructed_208[0x344 - 0x208];
	unsigned char m_bfmeByte344;					///< retail this+0x344
};

class AIUpdateInterfaceLike
{
public:
	void set(Int value);						// real, retail 0x0026FE90 (disp32 setter family)
	void destroyPath(void);					// real, retail 0x0026F080
	void setCurrentVictim(const Object *victim);			// ILT 0x0004AB4C

	char m_bfmeUnreconstructed_000[0x168];
	Int m_bfmeRangeSlot;						///< retail this+0x168
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed(void) const;			// ILT 0x0000432C
	Object *getGoalObject(void) const;				// ILT 0x0000E570

	char m_bfmeUnreconstructed_000[0x10];
	Object *m_owner;						///< retail this+0x10
	char m_bfmeUnreconstructed_014[0x1FC - 0x14];
	void *m_bfmeField1FC;						///< retail this+0x1FC
};

class TheAISubB
{
public:
	char m_bfmeUnreconstructed_000[0x94];
	Real m_bfmeRangeB;						///< retail this+0x94
};

class AIGlobal
{
public:
	char m_bfmeUnreconstructed_000[0x14];
	TheAISubB *m_bfmeSubB;						///< retail this+0x14
};

extern AIGlobal *TheAI;						// 0x012EF214
extern Bool Glo012F0239;						// 0x012F0239
extern void *TheCRCParameterCheck;					// 0x012ED4FC

extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...); // 0x0003A17A

// ABI-only pin: stdcall, (Object *owner, Real rangeB, Int flag2, Int aiField70, Int zero) -> Object*
extern "C" Object *__stdcall rva0014d120(Object *owner, Real rangeB, Int flag2, Int aiField70, Int zero);

enum StateReturnType { STATE_RETURN_PLACEHOLDER = 0 };

class AIInternalMoveToState
{
public:
	virtual StateReturnType update(void);				// real, retail 0x00172E70
	virtual StateReturnType onEnter(void);				// real, retail 0x00021E27
};

class Rva00177720State : public AIInternalMoveToState
{
public:
	virtual StateReturnType update(void);

	char m_bfmeUnreconstructed_004[0x1C - 0x04];
	StateMachine *m_bfmeMachine;					///< retail this+0x1C
	char m_bfmeUnreconstructed_020[0x24 - 0x20];
	Coord3D m_bfmeCachedGoalPos;					///< retail this+0x24
	char m_bfmeUnreconstructed_030[0x68 - 0x30];
	Bool m_bfmeReacquireFlag;					///< retail this+0x68
};

// Raw vtable-slot calls use MSVC's plain (single, non-virtual, no-base)
// pointer-to-member representation, which is just the code address, to reach
// __thiscall without the reserved __thiscall keyword on a free function type.
struct VSlotHelperVoid0 { void call(void); };
struct VSlotHelperBool0 { Bool call(void); };
struct VSlotHelperPtr0 { void *call(void); };
struct VSlotHelperVoid1Ptr { void call(void *); };
struct VSlotHelperBool1Ptr { Bool call(void *); };

typedef void (VSlotHelperVoid0::*VSlotVoidFn)(void);
typedef Bool (VSlotHelperBool0::*VSlotBoolFn)(void);
typedef void *(VSlotHelperPtr0::*VSlotPtrFn)(void);
typedef void (VSlotHelperVoid1Ptr::*VSlotVoid1PtrFn)(void *);
typedef Bool (VSlotHelperBool1Ptr::*VSlotBool1PtrFn)(void *);

static inline Bool SelfCheck(Rva00177720State *self)
{
	VSlotBoolFn slot44;
	*reinterpret_cast<void **>(&slot44) = (*reinterpret_cast<void ***>(self))[0x44 / 4];
	return (reinterpret_cast<VSlotHelperBool0 *>(self)->*slot44)();
}

static inline void *CallPtrSlot(void *obj, Int slot)
{
	VSlotPtrFn fn;
	*reinterpret_cast<void **>(&fn) = (*reinterpret_cast<void ***>(obj))[slot / 4];
	return (reinterpret_cast<VSlotHelperPtr0 *>(obj)->*fn)();
}

static inline Bool CallBool1PtrSlot(void *obj, Int slot, void *arg)
{
	VSlotBool1PtrFn fn;
	*reinterpret_cast<void **>(&fn) = (*reinterpret_cast<void ***>(obj))[slot / 4];
	return (reinterpret_cast<VSlotHelperBool1Ptr *>(obj)->*fn)(arg);
}

static inline void CallVoid0Slot(void *obj, Int slot)
{
	VSlotVoidFn fn;
	*reinterpret_cast<void **>(&fn) = (*reinterpret_cast<void ***>(obj))[slot / 4];
	(reinterpret_cast<VSlotHelperVoid0 *>(obj)->*fn)();
}

static inline void CallVoid1PtrSlot(void *obj, Int slot, void *arg)
{
	VSlotVoid1PtrFn fn;
	*reinterpret_cast<void **>(&fn) = (*reinterpret_cast<void ***>(obj))[slot / 4];
	(reinterpret_cast<VSlotHelperVoid1Ptr *>(obj)->*fn)(arg);
}

static inline void MaybeLogDesync(const char *format)
{
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, format);
}

// ?update@Rva00177720State@@UAE?AW4StateReturnType@@XZ
StateReturnType Rva00177720State::update(void)
{
	StateMachine *machine = m_bfmeMachine;
	Object *owner = machine->m_owner;
	AIUpdateInterfaceLike *ai = reinterpret_cast<AIUpdateInterfaceLike *>(owner->m_bfmeAi);
	ai->set(0x42480000); // 50.0f, by raw bit pattern (matches retail's immediate)
	Object *goal = machine->getGoalObject();

	if (machine->m_bfmeField1FC)
	{
		void *chained = CallPtrSlot(machine->m_bfmeField1FC, 0x68);
		if (chained && CallBool1PtrSlot(chained, 0x124, goal))
		{
			CallVoid0Slot(ai, 0x1e8);
			return (StateReturnType)-1;
		}
	}

	if (!machine->isGoalObjectDestroyed())
	{
		if (!goal)
			goto afterChecks;
		if (goal->m_bfmeByte344 & 1)
			goto reacquire;
		if (goal->m_bfmeStatus94 & 0x20000)
			goto reacquire;
	}
	else
	{
		goto reacquire;
	}

afterChecks:
	{
		StateReturnType stored = (StateReturnType)-2;

		if (!goal)
			goto storeAndReturn;

		if (!owner->crushPolicy(goal, 2))
			return (StateReturnType)-1;

		if (goal->m_bfmeStatus94 & 0x40000)
			return (StateReturnType)-2;

		{
			Player *player = owner->getControllingPlayer();
			if (reinterpret_cast<const BFMEObjectStealthQuery *>(goal)->isStealthedAndUndetected(player))
				return (StateReturnType)-2;
		}

		ai->setCurrentVictim(goal);
		MaybeLogDesync((const char *)0x10996cc);
		if (!SelfCheck(this))
			return (StateReturnType)-2;

		stored = AIInternalMoveToState::update();
		if (stored != (StateReturnType)0)
		{
			if (goal->m_bfmeByte344 & 1)
				return (StateReturnType)-1;
			if (!owner->isKindOf(0x96))
				return (StateReturnType)-1;

			m_bfmeCachedGoalPos.x = *reinterpret_cast<Real *>(reinterpret_cast<char *>(goal) + 0x38);
			m_bfmeCachedGoalPos.y = *reinterpret_cast<Real *>(reinterpret_cast<char *>(goal) + 0x3c);
			m_bfmeCachedGoalPos.z = *reinterpret_cast<Real *>(reinterpret_cast<char *>(goal) + 0x40);

			ai->destroyPath();
			MaybeLogDesync((const char *)0x10996a8);
			if (!SelfCheck(this))
				return (StateReturnType)-1;

			owner->setStatusBit(0x1c, true);
			return AIInternalMoveToState::onEnter();
		}

	storeAndReturn:
		owner->setStatusBit(0x1c, owner->rva001c7530());
		return stored;
	}

reacquire:
	ai->set(0);

	if (m_bfmeReacquireFlag && owner->rva001c7530())
	{
		m_bfmeReacquireFlag = false;

		Real rangeB = TheAI->m_bfmeSubB->m_bfmeRangeB;
		Object *newTarget = rva0014d120(owner, rangeB, 2, owner->m_bfmeField70, 0);

		if (newTarget && owner->crushPolicy(newTarget, 2))
		{
			CallVoid1PtrSlot(machine, 0x38, newTarget);

			MaybeLogDesync((const char *)0x1099684);
			if (SelfCheck(this))
			{
				m_bfmeReacquireFlag = true;
				return AIInternalMoveToState::update();
			}
			return (StateReturnType)-2;
		}
	}

	return AIInternalMoveToState::update();
}

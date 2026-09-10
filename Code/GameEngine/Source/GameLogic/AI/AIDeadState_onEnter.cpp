// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <bitset>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

// BFME's ModelState additions put the complete weapon-state block at bits
// 39..56 and the per-slot weapon-use conditions at 116..118.  The later
// ENGAGED condition is bit 147.  The values are also recovered independently
// by WeaponSet::getModelConditionForWeaponSlot and the retail model-state name
// table.
enum ModelConditionFlagType
{
	MODELCONDITION_PREATTACK_A = 39,
	MODELCONDITION_FIRING_A = 40,
	MODELCONDITION_FIRING_OR_PREATTACK_A = 41,
	MODELCONDITION_FIRING_OR_RELOADING_A = 42,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_A = 43,
	MODELCONDITION_RELOADING_A = 44,
	MODELCONDITION_PREATTACK_B = 45,
	MODELCONDITION_FIRING_B = 46,
	MODELCONDITION_FIRING_OR_PREATTACK_B = 47,
	MODELCONDITION_FIRING_OR_RELOADING_B = 48,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_B = 49,
	MODELCONDITION_RELOADING_B = 50,
	MODELCONDITION_PREATTACK_C = 51,
	MODELCONDITION_FIRING_C = 52,
	MODELCONDITION_FIRING_OR_PREATTACK_C = 53,
	MODELCONDITION_FIRING_OR_RELOADING_C = 54,
	MODELCONDITION_BETWEEN_FIRING_SHOTS_C = 55,
	MODELCONDITION_RELOADING_C = 56,
	MODELCONDITION_MOVING = 60,
	MODELCONDITION_DYING = 61,
	MODELCONDITION_USING_WEAPON_A = 116,
	MODELCONDITION_USING_WEAPON_B = 117,
	MODELCONDITION_USING_WEAPON_C = 118,
	MODELCONDITION_ENGAGED = 147
};

template <int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum BogusInitType
	{
		kInit = 0
	};

	BitFlags()
	{
	}

	BitFlags(BogusInitType, Int bit)
	{
		m_bits.set(bit);
	}

	void set(Int bit)
	{
		m_bits.set(bit);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<320> ModelConditionFlags;

class Object;

class ScriptEngine
{
public:
	void notifyOfObjectCreationOrDestruction();
};

extern ScriptEngine *TheScriptEngine;

#pragma comment(linker, "/alternatename:?notifyOfObjectCreationOrDestruction@ScriptEngine@@QAEXXZ=?j_0003b15b@@YAXXZ")

class Pathfinder
{
public:
	void removeObjectFromPathfindMap(Object *object);
};

class AI
{
public:
	Pathfinder *pathfinder() const
	{
		return m_pathfinder;
	}

private:
	unsigned char m_unreconstructed_00[0x0C];
	Pathfinder *m_pathfinder;
};

extern AI *TheAI;

enum KindOfType
{
	KINDOF_INFANTRY = 8
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	const Overridable *getFinalOverride() const;

	Overridable *m_nextOverride;
};

#pragma comment(linker, "/alternatename:?getFinalOverride@Overridable@@QBEPBV1@XZ=?j_000022bb@@YAXXZ")

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5] & (1 << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_unreconstructed_08[0xC8 - 0x08];
	UnsignedInt m_kindof[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
			tmpl = (const ThingTemplate *)tmpl->m_nextOverride->getFinalOverride();
		return tmpl;
	}

	Bool isKindOf(KindOfType kind) const
	{
		return getTemplate()->isKindOf(kind);
	}

protected:
	virtual ~Thing();

	const ThingTemplate *m_template;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	void clearAndSetModelConditionFlags(const ModelConditionFlags &clear,
		const ModelConditionFlags &set);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
public:
	unsigned char m_unreconstructed_00[0x10];
	Object *m_owner;
};

enum StateReturnType
{
	STATE_CONTINUE = 0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State
{
public:
	virtual StateReturnType onEnter();

protected:
	unsigned char m_unreconstructed_04[0x18];
	StateMachine *m_machine;

	Object *getMachineOwner() const
	{
		return m_machine->m_owner;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIDeadState : public State
{
public:
	virtual StateReturnType onEnter();
};

// ?onEnter@AIDeadState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIDeadState::onEnter()
{
	Object *obj = getMachineOwner();

	if (obj)
	{
		ModelConditionFlags nonDyingStuff;
		nonDyingStuff.set(MODELCONDITION_USING_WEAPON_A);
		nonDyingStuff.set(MODELCONDITION_USING_WEAPON_B);
		nonDyingStuff.set(MODELCONDITION_USING_WEAPON_C);
		nonDyingStuff.set(MODELCONDITION_FIRING_A);
		nonDyingStuff.set(MODELCONDITION_FIRING_B);
		nonDyingStuff.set(MODELCONDITION_FIRING_C);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_PREATTACK_A);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_PREATTACK_B);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_PREATTACK_C);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_RELOADING_A);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_RELOADING_B);
		nonDyingStuff.set(MODELCONDITION_FIRING_OR_RELOADING_C);
		nonDyingStuff.set(MODELCONDITION_BETWEEN_FIRING_SHOTS_A);
		nonDyingStuff.set(MODELCONDITION_BETWEEN_FIRING_SHOTS_B);
		nonDyingStuff.set(MODELCONDITION_BETWEEN_FIRING_SHOTS_C);
		nonDyingStuff.set(MODELCONDITION_RELOADING_A);
		nonDyingStuff.set(MODELCONDITION_RELOADING_B);
		nonDyingStuff.set(MODELCONDITION_RELOADING_C);
		nonDyingStuff.set(MODELCONDITION_PREATTACK_A);
		nonDyingStuff.set(MODELCONDITION_PREATTACK_B);
		nonDyingStuff.set(MODELCONDITION_PREATTACK_C);
		nonDyingStuff.set(MODELCONDITION_MOVING);
		nonDyingStuff.set(MODELCONDITION_ENGAGED);

		obj->clearAndSetModelConditionFlags(nonDyingStuff,
			ModelConditionFlags(ModelConditionFlags::kInit, MODELCONDITION_DYING));
		TheScriptEngine->notifyOfObjectCreationOrDestruction();

		if (obj->isKindOf(KINDOF_INFANTRY))
			TheAI->pathfinder()->removeObjectFromPathfindMap(obj);
	}

	return STATE_CONTINUE;
}

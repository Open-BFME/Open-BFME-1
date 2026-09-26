// ?applyModelCondition_002FDEF0@@YAXPAVObject@@H_N@Z
// partial score=0.45 date=2026-09-12
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline

// Retail outlines the shared UNIT/TEAM_SET_MODELCONDITION update once at
// 0x002FDEF0 (pinned as applyModelCondition_002FDEF0 in reverse/symbols.csv).
// ScriptActionsNamedSetModelCondition.cpp and ScriptActionsTeamSetModelCondition.cpp
// each already carry a private TU-local copy of this same body reachable from
// their own single call site. Landing the shared body's own address needs a
// TU-local caller shaped the same way, so the scaffold below is not a retail
// function; only the helper below is claimed.

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

class AsciiString
{
	char *m_data;
};

enum ModelConditionFlagType
{
	MODELCONDITION_USER_1 = 0xae,
	MODELCONDITION_USER_2,
	MODELCONDITION_USER_3,
	MODELCONDITION_USER_4
};

class ModelConditionFlags
{
public:
	UnsignedInt m_bits[10];
};

class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

// Upstream layout: GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h.
// These bases place the BFME model-condition mask at Object+0x110.
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0xa0];
	ModelConditionFlags m_modelConditionFlags;

	void notifyModelConditionChanged(void);
};

#define BFME_SCRIPT_ENGINE_SLOT(index) virtual void _se_##index(void) = 0;

// Upstream layout: GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h.
// BFME's getUnitNamed is slot 26, vtable offset +0x68, and takes one
// AsciiString reference.
class ScriptEngine
{
public:
	BFME_SCRIPT_ENGINE_SLOT(0)
	BFME_SCRIPT_ENGINE_SLOT(1)
	BFME_SCRIPT_ENGINE_SLOT(2)
	BFME_SCRIPT_ENGINE_SLOT(3)
	BFME_SCRIPT_ENGINE_SLOT(4)
	BFME_SCRIPT_ENGINE_SLOT(5)
	BFME_SCRIPT_ENGINE_SLOT(6)
	BFME_SCRIPT_ENGINE_SLOT(7)
	BFME_SCRIPT_ENGINE_SLOT(8)
	BFME_SCRIPT_ENGINE_SLOT(9)
	BFME_SCRIPT_ENGINE_SLOT(10)
	BFME_SCRIPT_ENGINE_SLOT(11)
	BFME_SCRIPT_ENGINE_SLOT(12)
	BFME_SCRIPT_ENGINE_SLOT(13)
	BFME_SCRIPT_ENGINE_SLOT(14)
	BFME_SCRIPT_ENGINE_SLOT(15)
	BFME_SCRIPT_ENGINE_SLOT(16)
	BFME_SCRIPT_ENGINE_SLOT(17)
	BFME_SCRIPT_ENGINE_SLOT(18)
	BFME_SCRIPT_ENGINE_SLOT(19)
	BFME_SCRIPT_ENGINE_SLOT(20)
	BFME_SCRIPT_ENGINE_SLOT(21)
	BFME_SCRIPT_ENGINE_SLOT(22)
	BFME_SCRIPT_ENGINE_SLOT(23)
	BFME_SCRIPT_ENGINE_SLOT(24)
	BFME_SCRIPT_ENGINE_SLOT(25)
	virtual Object *getUnitNamed(const AsciiString &) = 0;
};

#undef BFME_SCRIPT_ENGINE_SLOT

extern ScriptEngine *TheScriptEngine;

// ?applyModelCondition_002FDEF0@@YAXPAVObject@@H_N@Z
// Shared outlined helper for the UNIT/TEAM_SET_MODELCONDITION script actions.
// See docs/shape_levers.md, "Static function with a private register
// convention": a single-call static helper compiles its parameters wherever
// the one caller already holds them (obj in ESI, conditionNumber in EAX).
static void applyModelCondition_002FDEF0(
	Object *obj, Int conditionNumber, Bool set)
{
	ModelConditionFlagType condition;
	switch (conditionNumber)
	{
		case 1: condition = MODELCONDITION_USER_1; break;
		case 2: condition = MODELCONDITION_USER_2; break;
		case 3: condition = MODELCONDITION_USER_3; break;
		case 4: condition = MODELCONDITION_USER_4; break;
		default: condition = MODELCONDITION_USER_1; break;
	}

	UnsignedInt mask = 1u << ((UnsignedInt)condition & 31);
	UnsignedInt &word = obj->m_modelConditionFlags.m_bits[
		(UnsignedInt)condition >> 5];
	if (set)
	{
		if (!(word & mask))
		{
			word |= mask;
			obj->notifyModelConditionChanged();
		}
	}
	else
	{
		if (word & mask)
		{
			word &= ~mask;
			obj->notifyModelConditionChanged();
		}
	}
}

// Reconstruction scaffold, absent from retail: gives the helper above a
// single TU-local call site shaped like the two real callers, so it compiles
// with the same private register convention they already reproduce.
class ModelConditionHelperScaffold
{
public:
	void bfmeScaffoldCall(const AsciiString &, Int, Bool);
};

void ModelConditionHelperScaffold::bfmeScaffoldCall(
	const AsciiString &unitName, Int conditionNumber, Bool set)
{
	Object *unit = TheScriptEngine->getUnitNamed(unitName);
	if (!unit)
		return;

	applyModelCondition_002FDEF0(unit, conditionNumber, set);
}

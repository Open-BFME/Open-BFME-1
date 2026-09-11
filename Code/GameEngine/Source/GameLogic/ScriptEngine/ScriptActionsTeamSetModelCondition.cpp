// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline
// stlport
// Readable reconstruction of ScriptActions::doTeamSetModelCondition.
//
// Identity evidence:
//   * ScriptActions::executeAction at 0x00303BF0 is already byte-matched.  Its
//     action-329 arm extracts (AsciiString const &, Int, Bool) and calls this
//     body through ILT 0x000119FF.
//   * ScriptEngine's matched action-template initializer names slot 329
//     TEAM_SET_MODELCONDITION and describes the integer as custom condition
//     1--4.  The retail switch maps those values to USER_1 through USER_4.
//   * The body calls getTeamNamed and walks Team's member-list DLINK, the same
//     layout and pointer-to-member ABI as the exact team-action donor in
//     ScriptActionsTeamMemberFlags.cpp.

#include "StringInline.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

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

// Layout donor: reference/shims/objectdlink/ObjectDlinkPmf.h.  The bases put
// m_modelConditionFlags at the retail Object+0x110 offset.
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0xa0];
	ModelConditionFlags m_modelConditionFlags;

	void notifyModelConditionChanged(void);
};

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
// Upstream layout: GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h.
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// Upstream layout: GeneralsMD/Code/GameEngine/Include/Common/Team.h.
class Team
{
public:
	Object *m_unmodelled0;
	Object *m_unmodelled1;
	Object *m_unmodelled2;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

#define BFME_SCRIPT_ENGINE_SLOT(index) virtual void _se_##index() = 0;

// Upstream layout: GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h.
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

#undef BFME_SCRIPT_ENGINE_SLOT

extern ScriptEngine *TheScriptEngine;

// Retail outlined this common update at 0x002FDEF0 and assigned it a private
// register convention.  The suffix is a reconstruction alias; not historical
// identity.  Keeping the clean helper TU-local reproduces that convention in
// doTeamSetModelCondition.  Only the named action body is claimed here.
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

// Upstream declaration: GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h.
class ScriptActions
{
protected:
	void doTeamSetModelCondition(const AsciiString &, Int, Bool);
};

// ?doTeamSetModelCondition@ScriptActions@@IAEXABVAsciiString@@H_N@Z
void ScriptActions::doTeamSetModelCondition(
	const AsciiString &teamName, Int conditionNumber, Bool set)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (!obj)
			continue;
		applyModelCondition_002FDEF0(obj, conditionNumber, set);
	}
}

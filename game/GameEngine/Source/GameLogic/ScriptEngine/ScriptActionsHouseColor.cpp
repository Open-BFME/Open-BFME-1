// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// The two house-colour indicator actions:
//
//   0x002F74E0  doUnitEnableHouseColor  UNIT_ENABLE_HOUSE_COLOR
//   0x002F7530  doTeamEnableHouseColor  TEAM_ENABLE_HOUSE_COLOR
//
// Both reach a Drawable through Object vtable slot 10 and flip its house-colour
// indicator. One does it to a single named unit, the other to every member of a
// team.

#include "StringInline.h"

typedef bool Bool;

class ScriptActions;
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
private:
	friend class ScriptActions;
	void bfmeSetIndicatorOn(Bool enabled);
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class BfmeObjectVtbl
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual Drawable *getDrawable() = 0;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

template<class OBJCLASS>
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	// The by-value unit lookup at +0x6C, which other translation units in this
	// tree spell getUnitNamedByValue. Both bodies here take the name by value.
	virtual Object *getUnitNamed(AsciiString name) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doUnitEnableHouseColor(Parameter *unit, Bool enabled);
	void doTeamEnableHouseColor(Parameter *team, Bool enabled);
};

void ScriptActions::doUnitEnableHouseColor(Parameter *unit, Bool enabled)
{
	Object *object = TheScriptEngine->getUnitNamed(unit->m_string);
	if (object) {
		Drawable *drawable = object->getDrawable();
		if (drawable) {
			drawable->bfmeSetIndicatorOn(enabled);
		}
	}
}

void ScriptActions::doTeamEnableHouseColor(Parameter *team, Bool enabled)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (theTeam)
	{
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			Drawable *drawable = iter.cur()->getDrawable();
			if (drawable)
				drawable->bfmeSetIndicatorOn(enabled);
		}
	}
}

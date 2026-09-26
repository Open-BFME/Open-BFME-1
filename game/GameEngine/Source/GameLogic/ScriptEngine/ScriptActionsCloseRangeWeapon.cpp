// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// The two actions that switch a DualWeaponBehavior between its weapons:
//
//   0x002F6B90  doTeamToggleCloseRangeWeapon   TEAM_TOGGLE_CLOSE_RANGE_WEAPON
//   0x002F6CA0  doNamedToggleCloseRangeWeapon  NAMED_TOGGLE_CLOSE_RANGE_WEAPON
//
// Both find the DualWeaponBehavior update module by the name key
// "DualWeaponBehavior" and write its close-range flag at +0x20. The only
// difference is that one does it to every member of a team and the other to one
// named unit.

#include "StringInline.h"

typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class Object;
class SupplyWarehouseDockUpdate;
class Team;

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
};

// Both lookups take the name by value through this wrapper.
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
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	SupplyWarehouseDockUpdate *findUpdateModule(int key);
	unsigned char m_tail[0x40];
};

class DualWeaponBehavior
{
private:
	unsigned char m_beforeCloseRangeFlag[0x20];

public:
	Bool m_useCloseRangeWeapon;
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

public:
	Object *m_head;

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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool unused) = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25() = 0;
	virtual void _slot26() = 0;
	virtual Object *getUnitNamedByValue(BfmeAsciiStringArg name) = 0;
};

// The name the named-unit action's file gave this same vtable.
typedef ScriptEngine ScriptEngineByValue;

class NameKeyGenerator;

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamToggleCloseRangeWeapon(const AsciiString &teamName,
		Bool enabled);
	void doNamedToggleCloseRangeWeapon(const AsciiString &unitName,
		Bool enabled);
};

void ScriptActions::doTeamToggleCloseRangeWeapon(
	const AsciiString &teamName, Bool enabled)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (team)
	{
		static const int dualWeaponBehaviorKey =
			TheNameKeyGenerator->nameToKey("DualWeaponBehavior");

		for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			DualWeaponBehavior *behavior = (DualWeaponBehavior *)
				iter.cur()->findUpdateModule(dualWeaponBehaviorKey);
			if (behavior)
				behavior->m_useCloseRangeWeapon = enabled;
		}
	}
}

void ScriptActions::doNamedToggleCloseRangeWeapon(
	const AsciiString &unitName, Bool enabled)
{
	Object *object = TheScriptEngine->getUnitNamedByValue(unitName);
	if (object)
	{
		static const int dualWeaponBehaviorKey =
			TheNameKeyGenerator->nameToKey("DualWeaponBehavior");
		DualWeaponBehavior *behavior = (DualWeaponBehavior *)
			object->findUpdateModule(dualWeaponBehaviorKey);
		if (behavior)
			behavior->m_useCloseRangeWeapon = enabled;
	}
}

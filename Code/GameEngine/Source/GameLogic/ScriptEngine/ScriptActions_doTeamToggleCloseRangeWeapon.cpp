// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_TOGGLE_CLOSE_RANGE_WEAPON at retail RVA 0x002F6B90.

#include "StringInline.h"

typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
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

class Object;
class SupplyWarehouseDockUpdate;

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
};

class NameKeyGenerator;

extern ScriptEngine *TheScriptEngine;
extern NameKeyGenerator *TheNameKeyGenerator;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class ScriptActions
{
protected:
	void doTeamToggleCloseRangeWeapon(const AsciiString &teamName,
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

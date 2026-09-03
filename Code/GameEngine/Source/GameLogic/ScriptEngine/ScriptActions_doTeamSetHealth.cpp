// cl: /DNDEBUG /DWIN32 /MD /EHsc
// TEAM_SET_HEALTH at retail RVA 0x002F6A70.

typedef bool Bool;
typedef float Real;

template<class T>
inline const T &min(const T &left, const T &right)
{
	return left < right ? left : right;
}

template<class T>
inline const T &max(const T &left, const T &right)
{
	return left > right ? left : right;
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
private:
	char *m_text;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Scripts.h
class Parameter
{
public:
	unsigned char m_unknown[8];
	int m_integer;
	Real m_real;
	AsciiString m_string;
};

class Team;

class BfmeScriptEngineVtbl_44
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
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BodyModule.h
class BodyModuleInterface
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
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void setHealth(Real health, Bool force) = 0;
	virtual void _slot58() = 0;
	virtual void updateHealth() = 0;
};

class Object;

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((char *)this + 0x200);
	}
};

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
private:
	unsigned char m_beforeMembers[0x0c];
	Object *m_head;

public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamSetHealth(Parameter *team, Parameter *health);
};

extern BfmeScriptEngineVtbl_44 *TheScriptEngine;

// ?doTeamSetHealth@ScriptActions@@IAEXPAVParameter@@0@Z
void ScriptActions::doTeamSetHealth(Parameter *team, Parameter *health)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (theTeam)
	{
		Real value = health->m_real;
		value = min(value, 100.0f);
		value = max(0.0f, value);

		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			BodyModuleInterface *body = iter.cur()->getBodyModule();
			if (body)
			{
				body->setHealth(value, true);
				body->updateHealth();
			}
		}
	}
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc

typedef bool Bool;
typedef int Int;

class Object;

template <class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();

public:
	Int compare(const StringBase &) const throw();
};

class AsciiString
{
public:
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString();

private:
	char *m_text;
};

inline Bool operator==(const AsciiString &left, const AsciiString &right)
{
	return ((const StringBase<char> *)&left)->compare(
		*(const StringBase<char> *)&right) == 0;
}

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeInt[0x10];
	AsciiString m_string;
};

class Waypoint
{
public:
	AsciiString getPathLabel1() const;
	AsciiString getPathLabel2() const;
	AsciiString getPathLabel3() const;
};

class AIUpdateInterface
{
public:
	Waypoint *getCompletedWaypoint() const
	{
		return *(Waypoint **)((const char *)this + 0x13c);
	}
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

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
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

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface **)((const char *)this + 0x204);
	}
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS * (OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance(void)
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done(void) const { return m_cur == 0; }
	OBJCLASS *cur(void) const { return m_cur; }
};

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamReachedWaypointsEnd(Parameter *, Parameter *);
};

// ?evaluateTeamReachedWaypointsEnd@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamReachedWaypointsEnd(
	Parameter *pTeamParm, Parameter *pWaypointPathParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(
		pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	AsciiString pathName = pWaypointPathParm->getString();
	Bool anyAtEnd = false;
	Bool anyNotAtEnd = false;
	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pObj = iter.cur();
		if (!pObj)
			continue;

		AIUpdateInterface *ai = pObj->getAIUpdateInterface();
		if (!ai)
			continue;

		const Waypoint *targetWay = ai->getCompletedWaypoint();
		if (!targetWay)
		{
			anyNotAtEnd = true;
			continue;
		}

		Bool found = false;
		if (targetWay->getPathLabel1() == pathName)
			found = true;
		if (targetWay->getPathLabel2() == pathName)
			found = true;
		if (targetWay->getPathLabel3() == pathName)
			found = true;
		if (found)
			anyAtEnd = true;
		else
			anyNotAtEnd = true;
	}
	return anyAtEnd;
}

// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// ScriptConditions::evaluateTeamHasObjectStatus at retail 0x0032BB90.

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc) :
		m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

template<class T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const StringBase &);
	~StringBase();
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

class Parameter
{
public:
	const AsciiString &getString() const { return m_string; }
	Int getInt() const { return m_int; }

private:
	unsigned char m_beforeType[4];
	unsigned char m_initialized;
	unsigned char m_padding[3];
	Int m_int;
	float m_real;
	AsciiString m_string;
};

class ObjectStatusView
{
public:
	unsigned char m_beforeStatus[0x90];
	UnsignedInt m_status[3];
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
	Bool evaluateTeamHasObjectStatus(Parameter *pTeamParm,
		Parameter *pObjectStatus, Bool entireTeam);
};

// ?evaluateTeamHasObjectStatus@ScriptConditions@@IAE_NPAVParameter@@0_N@Z
Bool ScriptConditions::evaluateTeamHasObjectStatus(Parameter *pTeamParm,
	Parameter *pObjectStatus, Bool entireTeam)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pObj = iter.cur();
		if (!pObj)
			return false;

		UnsignedInt status = pObjectStatus->getInt();
		ObjectStatusView *obj = (ObjectStatusView *)pObj;
		Bool currObjHasStatus =
			(obj->m_status[status >> 5] & (1u << (status & 31))) != 0;

		if (entireTeam && !currObjHasStatus)
			return false;
		else if (!entireTeam && currObjHasStatus)
			return true;
	}

	if (entireTeam)
		return true;
	return false;
}

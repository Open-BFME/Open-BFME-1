// cl: /DNDEBUG /MD /EHsc /Ireference/shims/objectdlink

#include "ObjectDlinkPmf.h"

typedef bool Bool;
typedef unsigned short PlayerMaskType;

template <class T> class StringBase
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
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class DamageInfo
{
private:
	unsigned char m_beforeSourcePlayerMask[0x0c];

public:
	PlayerMaskType m_sourcePlayerMask;
};

class BodyModuleInterface
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
	virtual const DamageInfo *getLastDamageInfo() const = 0;
};

class BfmeObjectView
{
public:
	BodyModuleInterface *getBodyModule() const
	{
		return *(BodyModuleInterface **)((const char *)this + 0x200);
	}
};

template <class T> class DlinkIterator
{
public:
	typedef T *(T::*GetNextFunc)() const;

	DlinkIterator(T *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	T *cur() const { return m_cur; }

private:
	T *m_cur;
	GetNextFunc m_getNextFunc;
};

class Team
{
public:
	DlinkIterator<Object> iterate_TeamMemberList() const
	{
		return DlinkIterator<Object>(m_memberListHead,
			Object::dlink_next_TeamMemberList);
	}

private:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_memberListHead;
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
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateTeamAttackedByPlayer(Parameter *, Parameter *);
};

// ?evaluateTeamAttackedByPlayer@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateTeamAttackedByPlayer(
	Parameter *pTeamParm, Parameter *pPlayerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	PlayerMaskType mask =
		TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	for (DlinkIterator<Object> iter = theTeam->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *pCur = iter.cur();
		if (!pCur)
			continue;

		BodyModuleInterface *body =
			((const BfmeObjectView *)pCur)->getBodyModule();
		if (!body)
			continue;

		const DamageInfo *lastDamageInfo = body->getLastDamageInfo();
		if (!lastDamageInfo)
			continue;

		if (lastDamageInfo->m_sourcePlayerMask == mask)
			return true;
	}

	return false;
}

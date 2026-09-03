// ?doTeamForceEmotion@ScriptActions@@IAEXPAVParameter@@W4EmotionType@@M@Z
// partial score=0.95 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/stringinline
// Open-BFME: TEAM_FORCE_EMOTION at retail RVA 0x002F75D0.

#include "StringInline.h"

typedef bool Bool;

enum EmotionType
{
	EMOTION_INVALID = -1
};

class ScriptActions;
class Drawable;
class Object;

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

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	void forceEmotion(EmotionType emotion, float duration,
		const Object *source);
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
	virtual Team *getTeamNamed(AsciiString name, Bool unused) = 0;
};

extern ScriptEngine *TheScriptEngine;

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doTeamForceEmotion(Parameter *team, EmotionType emotion,
		float duration);
};

void ScriptActions::doTeamForceEmotion(Parameter *team, EmotionType emotion,
	float duration)
{
	if (emotion < 0)
		return;
	if (emotion >= 10)
		return;

	Team *theTeam = TheScriptEngine->getTeamNamed(team->m_string, false);
	if (theTeam)
	{
		for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList();
			!iter.done(); iter.advance())
		{
			iter.cur()->forceEmotion(emotion, duration, 0);
		}
	}
}

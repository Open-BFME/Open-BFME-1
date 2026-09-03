// ?doPlayerForceEmotion@ScriptActions@@IAEXPAVParameter@@W4EmotionType@@M@Z
// partial score=0.82 date=2026-09-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Open-BFME: PLAYER_FORCE_EMOTION at retail RVA 0x002F7670.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

typedef bool Bool;

enum EmotionType
{
	EMOTION_INVALID = -1
};

class ScriptActions;
class Drawable;
class Object;
class Team;
class TeamPrototype;
class Player;

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

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Team
{
private:
	void *m_vptr;
	void *m_prototype;
	void *m_id;

public:
	Object *m_head;
	Team *_bfme_nextInInstanceList();

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head) {}

	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

class BfmeTeamPrototypeInstances
{
public:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;

	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}
};

class BfmePlayerTeamListNode
{
public:
	BfmePlayerTeamListNode *m_next;
	BfmePlayerTeamListNode *m_prev;
	TeamPrototype *m_value;
};

class Player
{
private:
	unsigned char m_unmodelled_000[0x288];

public:
	BfmePlayerTeamListNode *m_playerTeamPrototypes;
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
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	unsigned short getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(unsigned short &mask);
};

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptActions
{
protected:
	void doPlayerForceEmotion(Parameter *player, EmotionType emotion,
		float duration);
};

void ScriptActions::doPlayerForceEmotion(Parameter *player,
	EmotionType emotion, float duration)
{
	Team *team;
	if (emotion < 0)
		return;
	if (emotion >= 10)
		return;

	unsigned short mask =
		((BfmeScriptEngine_getPlayerMaskFromAsciiString *)TheScriptEngine)
			->getPlayerMaskFromAsciiString(player->m_string, 0);
	if (!mask)
		return;

	do
	{
		Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (thePlayer)
		{
			BfmePlayerTeamListNode *it;
			it = ((Player *)thePlayer)->m_playerTeamPrototypes;
			it = it->m_next;
			while (it != ((Player *)thePlayer)->m_playerTeamPrototypes)
			{
				team =
					((BfmeTeamPrototypeInstances *)it->m_value)
						->m_teamInstanceList;
				if (team)
				{
				 do
				{
					for (DLINK_ITERATOR<Object> objectIter =
						team->iterate_TeamMemberList();
						!objectIter.done(); objectIter.advance())
					{
						objectIter.cur()->forceEmotion(emotion, duration, 0);
					}
					team = team->_bfme_nextInInstanceList();
				} while (team);
				}
				it = it->m_next;
			}
		}
	} while (mask);
}

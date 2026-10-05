// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
// Open-BFME: PLAYER_FORCE_EMOTION handler at retail RVA 0x002F7670, 260 bytes.
//
// executeAction (0x00303BF0) reaches this body from the PLAYER_FORCE_EMOTION
// arm; it is the player-wide sibling of the TEAM_FORCE_EMOTION handler at
// 0x002F75D0 and forces the emotion on every member of every team of each
// player in the mask. The name follows the doNamedForceEmotion /
// doTeamForceEmotion siblings.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "StringInline.h"

typedef bool Bool;
typedef unsigned short PlayerMaskType;

enum EmotionType
{
	EMOTION_INVALID = -1
};

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
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};


class Team
{
	void *m_vptr;
	void *m_prototype;
	void *m_id;

public:
	Object *m_head;
	Team *_bfme_nextInInstanceList();	// ILT 0x00022A70

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class TeamIterator
{
public:
	typedef Team *(Team::*Next)();
	TeamIterator(Team *p) : m_cur(p), m_next(&Team::_bfme_nextInInstanceList) {}
	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
	void advance() { if (m_cur) m_cur = (m_cur->*m_next)(); }
private:
	Team *m_cur;
	Next m_next;
};

class TeamPrototype
{
public:
	char m_beforeInstances[0x274];
	Team *m_instances;							// +0x274
	TeamIterator iterate_TeamInstanceList() const { return TeamIterator(m_instances); }
};

class Player
{
public:
	typedef _STL::list<TeamPrototype *> PlayerTeamList;
	char m_beforeTeams[0x288];
	PlayerTeamList m_teams;						// +0x288
	const PlayerTeamList *getPlayerTeams() const { return &m_teams; }
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};

class BfmeScriptEngine_getPlayerMaskFromAsciiString
{
public:
	PlayerMaskType getPlayerMaskFromAsciiString(const AsciiString &name,
		Bool *isWildcard);
};

class ScriptEngine : public BfmeScriptEngine_getPlayerMaskFromAsciiString
{
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class Parameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class ScriptActions
{
protected:
	void doPlayerForceEmotion(Parameter *player, EmotionType emotion, float duration);
};

// ?doPlayerForceEmotion@ScriptActions@@IAEXPAVParameter@@W4EmotionType@@M@Z
void ScriptActions::doPlayerForceEmotion(Parameter *player, EmotionType emotion,
	float duration)
{
	if (emotion < 0)
		return;
	if (emotion >= 10)
		return;

	PlayerMaskType mask = TheScriptEngine->getPlayerMaskFromAsciiString(player->m_string, 0);
	while (mask)
	{
		Player *thePlayer = ThePlayerList->getEachPlayerFromMask(mask);
		if (!thePlayer)
			continue;

		Player::PlayerTeamList::const_iterator it;
		for (it = thePlayer->getPlayerTeams()->begin(); it != thePlayer->getPlayerTeams()->end(); ++it)
		{
			for (TeamIterator teams = (*it)->iterate_TeamInstanceList(); !teams.done(); teams.advance())
			{
				Team *team = teams.cur();
				if (!team)
					continue;
				for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList();
					!objects.done(); objects.advance())
				{
					Object *obj = objects.cur();
					if (!obj)
						continue;
					obj->forceEmotion(emotion, duration, 0);
				}
			}
		}
	}
}

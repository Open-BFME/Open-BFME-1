// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink
// stlport
// Retail 0x00329230: Zero Hour's unowned faction count with BFME object layout.
#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef int Int;

class Parameter
{
public:
	Int getInt() const { return m_value; }
private:
	char m_reserved[8];
	Int m_value;
};

template<class T> class DLINK_ITERATOR
{
public:
	typedef T *(T::*Next)() const;
	DLINK_ITERATOR(T *p, Next fn) : m_cur(p), m_next(fn) {}
	bool done() const { return m_cur == 0; }
	T *cur() const { return m_cur; }
	void advance() { if (m_cur) m_cur = (m_cur->*m_next)(); }
private:
	T *m_cur;
	Next m_next;
};

class Team
{
public:
	Team *_bfme_nextInInstanceList();
	char m_beforeMembers[0x0c];
	Object *m_head;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class TeamIterator
{
public:
	typedef Team *(Team::*Next)();
	TeamIterator(Team *p) : m_cur(p), m_next(&Team::_bfme_nextInInstanceList) {}
	bool done() const { return m_cur == 0; }
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
	Team *m_instances;
	TeamIterator iterate_TeamInstanceList() const { return TeamIterator(m_instances); }
};

class Player
{
public:
	typedef _STL::list<TeamPrototype *> PlayerTeamList;
	char m_reserved[0x288];
	PlayerTeamList m_teams;
	const PlayerTeamList *getPlayerTeams() const { return &m_teams; }
};

class PlayerList
{
public:
	Player *getNeutralPlayer() const { return *(Player *const *)((const char *)this + 0x14); }
};
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluateSkirmishUnownedFactionUnitComparison(Parameter *, Parameter *, Parameter *);
};

Bool ScriptConditions::evaluateSkirmishUnownedFactionUnitComparison(
	Parameter *, Parameter *comparison, Parameter *count)
{
	Player *player = ThePlayerList->getNeutralPlayer();
	if (!player)
		return false;
	Int total = 0;
	Player::PlayerTeamList::const_iterator it;
	for (it = player->getPlayerTeams()->begin(); it != player->getPlayerTeams()->end(); ++it) {
		for (TeamIterator teams = (*it)->iterate_TeamInstanceList(); !teams.done(); teams.advance()) {
			Team *team = teams.cur();
			if (!team) continue;
			for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList();
				!objects.done(); objects.advance()) {
				Object *object = objects.cur();
				if (!object) continue;
				if (*(const unsigned char *)((const char *)object + 0x1a4) & 0x20)
					++total;
			}
		}
	}
	switch (comparison->getInt()) {
	case 0: return total < count->getInt();
	case 1: return total <= count->getInt();
	case 2: return total == count->getInt();
	case 3: return total >= count->getInt();
	case 4: return total > count->getInt();
	case 5: return total != count->getInt();
	}
	return false;
}

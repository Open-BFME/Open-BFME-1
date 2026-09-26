// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink
// stlport
// Retail 0x003254B0: count captured objects for each player in a script mask.
#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned short PlayerMaskType;

class Parameter
{
public:
	Int getInt() const { return m_value; }
private:
	char m_beforeValue[8];
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
	char m_beforeTeams[0x288];
	PlayerTeamList m_teams;
	const PlayerTeamList *getPlayerTeams() const { return &m_teams; }
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(PlayerMaskType &mask);
};
extern PlayerList *ThePlayerList;

class ScriptEngine
{
public:
	PlayerMaskType unidentified_0034DB40(Parameter *parameter);
};
extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
	Bool evaluateSkirmishPlayerHasComparisonCapturedUnits(Parameter *, Parameter *, Parameter *);
};

Bool ScriptConditions::evaluateSkirmishPlayerHasComparisonCapturedUnits(
	Parameter *playerParam, Parameter *comparison, Parameter *count)
{
	PlayerMaskType mask = TheScriptEngine->unidentified_0034DB40(playerParam);
	while (mask) {
		Player *player = ThePlayerList->getEachPlayerFromMask(mask);
		if (!player) continue;
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
					if (*(const unsigned char *)((const char *)object + 0x344) & 4)
						++total;
				}
			}
		}
		Bool result = false;
		switch (comparison->getInt()) {
		case 0: result = total < count->getInt(); break;
		case 1: result = total <= count->getInt(); break;
		case 2: result = total == count->getInt(); break;
		case 3: result = total >= count->getInt(); break;
		case 4: result = total > count->getInt(); break;
		case 5: result = total != count->getInt(); break;
		}
		if (result) return true;
	}
	return false;
}

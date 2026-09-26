// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink
// stlport
// Retail 0x003252A0: count garrisoned objects in each player's team list.
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

class Object;
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

class Rva003252A0Contain
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual Bool slot02() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual unsigned int slot64(unsigned int) = 0;
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
	Bool evaluateSkirmishPlayerHasComparisonGarrisoned(Parameter *, Parameter *, Parameter *);
};

Bool ScriptConditions::evaluateSkirmishPlayerHasComparisonGarrisoned(
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
					Rva003252A0Contain *module = *(Rva003252A0Contain **)((char *)object + 0x1fc);
					if (module && module->slot02() && module->slot64(0) > 0)
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

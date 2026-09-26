// ?evaluateSkirmishUnownedFactionUnitComparison@ScriptConditions@@IAE_NPAVParameter@@00@Z
// partial score=0.65 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/objectdlink
// Retail 0x00329230. The neutral player's team members disabled as unmanned.
#include "ObjectDlinkPmf.h"

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

template<class T>
class DLINK_ITERATOR
{
public:
	typedef T *(T::*GetNextFunc)() const;
	DLINK_ITERATOR(T *current, GetNextFunc next) : m_current(current), m_next(next) {}
	bool done() const { return m_current == 0; }
	T *cur() const { return m_current; }
	void advance() { if (m_current) m_current = (m_current->*m_next)(); }
private:
	T *m_current;
	GetNextFunc m_next;
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class Team : public BfmeTeamInstanceLink
{
public:
	char m_beforeMembers[0x0c];
	Object *m_head;
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, &Object::dlink_next_TeamMemberList);
	}
};

class TeamPrototype
{
public:
	char m_beforeInstances[0x274];
	Team *m_instances;
};

struct TeamListNode
{
	TeamListNode *next;
	TeamListNode *previous;
	TeamPrototype *value;
};

class Player
{
public:
	TeamListNode *getTeams() const { return *(TeamListNode *const *)((const char *)this + 0x288); }
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
	TeamListNode *node = player->getTeams()->next;
	for (; node != player->getTeams(); node = node->next) {
		Team *team = node->value->m_instances;
		for (; team; team = (Team *)team->_bfme_nextInInstanceList()) {
			for (DLINK_ITERATOR<Object> objects = team->iterate_TeamMemberList();
				!objects.done(); objects.advance()) {
				Object *object = objects.cur();
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

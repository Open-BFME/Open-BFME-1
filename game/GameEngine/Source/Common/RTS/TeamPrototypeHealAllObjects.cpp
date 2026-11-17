// cl: /DNDEBUG /DWIN32 /MD /EHsc
//
// Retail 0x000EE730, 42 bytes through the ret at +0x29 (the ledger row stopped
// at 39, short of the shared `pop esi; ret` its loop exits branch to).
// Player::healAllObjects calls it through ILT 0x0001BF40, pinned as
// TeamPrototype::healAllObjects; it is Zero Hour's walk of the prototype's
// team instance list (head at +0x274) healing each team through
// Team::healAllObjects (ILT 0x00035625).

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	void healAllObjects();
};

// Retail reaches the team instance-list advance through ILT 0x00022A70
// (ledger row ?j_00022a70@@YAXXZ); the PMF value is that thunk's address.
extern void j_00022a70();

class TeamPrototype
{
public:
	void healAllObjects();

	DLINK_ITERATOR<Team> iterate_TeamInstanceList() const
	{
		union { void (*fn)(); DLINK_ITERATOR<Team>::GetNextFunc call; } u = { j_00022a70 };
		return DLINK_ITERATOR<Team>(m_firstInstance, u.call);
	}

private:
	char m_unmodelled00[0x274];
	Team *m_firstInstance;
};

// ?healAllObjects@TeamPrototype@@QAEXXZ
void TeamPrototype::healAllObjects()
{
	for (DLINK_ITERATOR<Team> iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->healAllObjects();
	}
}

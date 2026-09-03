// cl: /DNDEBUG /MD /EHsc
//
// TeamPrototype::damageTeamMembers.  Same instance-list walk as the already-
// matched countTeamInstances / findTeamByID / hasAnyObjects: head at this+0x274,
// advance through ILT 0x00022A70 (_bfme_nextInInstanceList).  Each instance is
// forwarded to Team::damageTeamMembers (ILT 0x0000D148 -> 0x000F33F0): that
// body walks Team+0x0C members, skips effectively-dead / destroyed, and either
// kill()s or attemptDamage()s from the amount.

typedef bool Bool;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool damageTeamMembers(Real amount);			// ILT 0x0000D148 -> 0x000F33F0

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();				// ILT 0x00022A70
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head)
		: m_cur(head)
	{
	}

	bool done() const
	{
		return m_cur == 0;
	}

	Team *cur() const
	{
		return m_cur;
	}

	void advance()
	{
		if (m_cur)
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	void damageTeamMembers(Real amount);

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}

	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;						// +0x274
};

// ?damageTeamMembers@TeamPrototype@@QAEXM@Z
void TeamPrototype::damageTeamMembers(Real amount)
{
	for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->damageTeamMembers(amount);
	}
}

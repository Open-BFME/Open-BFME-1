// cl: /DNDEBUG /MD /EHsc
//
// TeamPrototype::findTeamByID.  Same instance-list walk as the already-
// matched countTeamInstances: head at this+0x274, advance through ILT
// 0x00022A70 (_bfme_nextInInstanceList).  Team id sits at Team+0x08
// (BFME dropped Zero Hour's second base vptr).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Team *_bfme_nextInInstanceList();

	unsigned int getID() const { return m_id; }

private:
	void *m_vptr;				// +0x00
	void *m_proto;				// +0x04
	unsigned int m_id;			// +0x08
};

class BfmeTeamInstanceLink
{
public:
	BfmeTeamInstanceLink *_bfme_nextInInstanceList();
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator(Team *head) : m_cur(head) {}

	bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (Team *)((BfmeTeamInstanceLink *)m_cur)->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

struct BfmeTeamPrototypeInstances
{
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;

	BfmeTeamInstanceIterator iterate() const
	{
		return BfmeTeamInstanceIterator(m_teamInstanceList);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Team *findTeamByID(unsigned int teamID);
};

// ?findTeamByID@TeamPrototype@@QAEPAVTeam@@I@Z
Team *TeamPrototype::findTeamByID(unsigned int teamID)
{
	for (BfmeTeamInstanceIterator iter = ((const BfmeTeamPrototypeInstances *)this)->iterate();
		 !iter.done();
		 iter.advance())
	{
		if (iter.cur()->getID() == teamID)
			return iter.cur();
	}
	return 0;
}

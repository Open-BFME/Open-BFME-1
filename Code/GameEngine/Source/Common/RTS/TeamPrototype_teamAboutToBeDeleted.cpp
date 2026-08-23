// cl: /DNDEBUG /MD /EHsc

// TeamPrototype::teamAboutToBeDeleted, retail 0x000F4090, 57 bytes. Zero Hour's
// body unchanged: tell every team on the instance list to drop its override
// relationship with the team that is going away.
//
// The reference's `team ? team->getID() : TEAM_ID_INVALID' is what the guarded
// load is -- the id sits at Team+0x08 and the invalid id is zero.
//
// Same iterator the other TeamPrototype bodies measured: head at +0x274, the
// next team through a call, advance() carrying its own null check.

typedef unsigned int UnsignedInt;

typedef UnsignedInt TeamID;

enum { TEAM_ID_INVALID = 0 };

class Team
{
public:
	void removeOverrideTeamRelationship(TeamID teamID);		// ILT 0x0001A48D

	TeamID getID(void) const { return m_id; }

	unsigned char m_unmodelled_000[8];
	TeamID m_id;							// Team+0x08

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();				// ILT thunk at 0x00022A70
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator( Team *head )
		: m_cur( head )
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
		if( m_cur )
			m_cur = m_cur->_bfme_nextInInstanceList();
	}

private:
	Team *m_cur;
};

class TeamPrototype
{
public:
	void teamAboutToBeDeleted( Team *team );

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?teamAboutToBeDeleted@TeamPrototype@@QAEXPAVTeam@@@Z
void TeamPrototype::teamAboutToBeDeleted( Team *team )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		iter.cur()->removeOverrideTeamRelationship( team ? team->getID() : TEAM_ID_INVALID );
	}
}

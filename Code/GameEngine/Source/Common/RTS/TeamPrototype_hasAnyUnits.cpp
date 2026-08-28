// cl: /DNDEBUG /MD /EHsc
// readable body of ?hasAnyUnits@TeamPrototype@@QBE_NXZ: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamPrototype::hasAnyUnits, retail 0x000F7120, 52 bytes. Zero Hour's body:
// walk the team instance list and hand back true for the first team that has
// any units.
//
// Same iterator TeamPrototype_countBuildings.cpp measured: the list head is at
// +0x274 and BFME reaches the next team through a call rather than through the
// DLINK member Zero Hour's macros expand to, so advance() carries its own null
// check -- that is the second test on the same register, and the branch it
// feeds goes straight to the exit because an iterator that is done stays done.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyUnits() const;						// ILT thunk at 0x000064F6

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	Bool hasAnyUnits( void ) const;

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?hasAnyUnits@TeamPrototype@@QBE_NXZ
Bool TeamPrototype::hasAnyUnits( void ) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyUnits() )
			return true;
	}

	return false;
}

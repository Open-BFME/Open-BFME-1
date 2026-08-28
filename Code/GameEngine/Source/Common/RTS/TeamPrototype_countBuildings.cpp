// cl: /DNDEBUG /MD /EHsc
// readable body of ?countBuildings@TeamPrototype@@QAEHXZ: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamPrototype::countBuildings, retail 0x000F6F90. Zero Hour's body: walk the
// team instance list and add up each team's own count.
//
// The list head is at +0x274 and BFME reaches the next team through a call
// rather than through the DLINK member Zero Hour's macros expand to, so the
// iterator is written out here with the two calls it makes.
//
// advance() carries its own null check. That is what the second test on the
// same register is - the loop body cannot have changed it, and the branch it
// feeds goes straight to the exit because an iterator that is done stays done.

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Int countBuildings();							// ILT thunk at 0x00015294

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
	Int countBuildings( void );

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?countBuildings@TeamPrototype@@QAEHXZ
Int TeamPrototype::countBuildings( void )
{
	Int retVal = 0;

	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		retVal += iter.cur()->countBuildings();
	}

	return retVal;
}

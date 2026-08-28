// cl: /DNDEBUG /MD /EHsc
// readable body of ?countBuildings@TeamPrototype@@QAEHXZ: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?hasAnyBuildFacility@TeamPrototype@@QBE_NXZ: Code/GameEngine/Source/Common/RTS/Team.cpp
// readable body of ?hasAnyUnits@TeamPrototype@@QBE_NXZ: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamPrototype::countBuildings (retail 0x000F6F90), ::hasAnyBuildFacility
// (0x000F0DA0, 52 bytes) and ::hasAnyUnits (0x000F7120, 52 bytes) are one Zero
// Hour shape: walk the team instance list and fold each team's own answer.
//
// The list head is at +0x274 and BFME reaches the next team through a call
// rather than through the DLINK member Zero Hour's macros expand to, so the
// iterator is written out here with the two calls it makes.
//
// advance() carries its own null check. That is what the second test on the
// same register is - the loop body cannot have changed it, and the branch it
// feeds goes straight to the exit because an iterator that is done stays done.

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Int countBuildings();							// ILT thunk at 0x00015294
	Bool hasAnyBuildFacility() const;				// ILT thunk at 0x0003F594
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
	Int countBuildings( void );
	Bool hasAnyBuildFacility( void ) const;
	Bool hasAnyUnits( void ) const;

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
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

// ?hasAnyBuildFacility@TeamPrototype@@QBE_NXZ
Bool TeamPrototype::hasAnyBuildFacility( void ) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildFacility() )
			return true;
	}

	return false;
}

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

// cl: /DNDEBUG /MD /EHsc

// BFME's two-dword KindOfMaskType overload.  This is the same instance-list
// walk as the neighbouring hasAnyBuildings overloads, with the BFME list head
// at TeamPrototype+0x274 and the next link reached through a call.

typedef unsigned int UnsignedInt;
typedef bool Bool;

template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[ 2 ];
};

typedef BitFlags<116> KindOfMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Bool hasAnyBuildings( KindOfMaskType kindOf ) const;
	Team *_bfme_nextInInstanceList();
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator( Team *head ) : m_cur( head ) { }
	Bool done() const { return m_cur == 0; }
	Team *cur() const { return m_cur; }
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
	Bool hasAnyBuildings( KindOfMaskType kindOf ) const;

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;
};

Bool TeamPrototype::hasAnyBuildings( KindOfMaskType kindOf ) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		const UnsignedInt first = kindOf.m_bits[ 0 ];
		const UnsignedInt second = kindOf.m_bits[ 1 ];
		KindOfMaskType forwarded;
		forwarded.m_bits[ 0 ] = first;
		forwarded.m_bits[ 1 ] = second;
		if( iter.cur()->hasAnyBuildings( forwarded ) )
			return true;
	}

	return false;
}

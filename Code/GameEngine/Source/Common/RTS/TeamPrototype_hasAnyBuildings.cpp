// cl: /DNDEBUG /MD /EHsc

// TeamPrototype::hasAnyBuildings, retail 0x000F7020, 117 bytes. Zero Hour's
// mask-taking overload with the same extra flag its hasAnyObjects sibling
// carries, asked of every team on the instance list.
//
// The mask is BitFlags<192> -- six dwords, which the `ret 0x1C' accounts for
// together with the flag -- and it is passed by value, so most of the body is
// the copy the compiler builds in the outgoing argument slots on every
// iteration.  Player::hasAnyBuildings at 0x000CDF70 is the other half: it
// forwards the same two arguments to every prototype through the thunk at
// 0x0000B55F, which is this body.
//
// Same iterator the other TeamPrototype bodies measured: head at +0x274, the
// next team through a call, advance() carrying its own null check.

typedef unsigned int UnsignedInt;
typedef bool Bool;

template <int NUMBITS> class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<192> KindOfMaskType;

class Team
{
public:
	Bool hasAnyBuildings(KindOfMaskType kindOf, Bool bfmeFlag);	// ILT 0x0003B5B6

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
	Bool hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag );

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList()
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?hasAnyBuildings@TeamPrototype@@QAE_NV?$BitFlags@$0MA@@@_N@Z
Bool TeamPrototype::hasAnyBuildings( KindOfMaskType kindOf, Bool bfmeFlag )
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		if( iter.cur()->hasAnyBuildings( kindOf, bfmeFlag ) )
			return true;
	}

	return false;
}

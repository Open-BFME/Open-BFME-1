// cl: /DNDEBUG /MD /EHsc
// readable body of ?countObjectsByThingTemplate@TeamPrototype@@QBEXHPBQBVThingTemplate@@_NPAH1@Z: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamPrototype::countObjectsByThingTemplate, retail 0x000F4030, 76 bytes.
// Zero Hour's body: hand all five arguments to every team on the instance list.
//
// Same iterator TeamPrototype_countBuildings.cpp measured: the list head is at
// +0x274 and BFME reaches the next team through a call, so advance() carries its
// own null check -- that is the second test on the same register, and the branch
// it feeds goes straight to the exit because an iterator that is done stays done.

typedef int Int;
typedef bool Bool;

class ThingTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;	// ILT 0x00010181

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
	void countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const;

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[ 0x274 ];
	Team *m_teamInstanceList;						// +0x274
};

// ?countObjectsByThingTemplate@TeamPrototype@@QBEXHPBQBVThingTemplate@@_NPAH1@Z
void TeamPrototype::countObjectsByThingTemplate(Int numTmplates, const ThingTemplate* const* things, Bool ignoreDead, Int *counts, Bool ignoreUnderConstruction) const
{
	for( BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance() )
	{
		iter.cur()->countObjectsByThingTemplate(numTmplates, things, ignoreDead, counts, ignoreUnderConstruction);
	}
}

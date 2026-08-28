// cl: /DNDEBUG /MD /EHsc
// readable body of ?updateState@TeamPrototype@@QAEXXZ: Code/GameEngine/Source/Common/RTS/Team.cpp

// TeamPrototype::updateState, retail 0x000F71C0, 143 bytes. Zero Hour's body:
// update every team on the instance list, then sweep the empty ones away.
//
// Same iterator the other TeamPrototype bodies measured -- head at +0x274, the
// next team through a call, advance() carrying its own null check.
//
// The removal test is the reference's, with getControllingPlayer() inline: it
// is the owning player of the team's PROTOTYPE, so the walk is m_proto at
// Team+0x04, the player at TeamPrototype+0x08 and the default team at
// Player+0x230.  Both hops are null-checked.
//
// The singleton flag is bit 0 of the byte at TeamPrototype+0x18, and a team's
// active flag is the byte at Team+0x31; deleteInstance is `delete this' through
// the team's own vtable slot 0, which is what carries the 1.

typedef bool Bool;

class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_unmodelled_000[0x230];
	Team *m_defaultTeam;					// Player+0x230
};

class TeamPrototype;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();					// vtable slot 0

	void updateState(void);					// ILT 0x0004383D

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList();			// ILT thunk at 0x00022A70

	void deleteInstance() { delete this; }

	Player *getControllingPlayer() const;
	Bool isActive() const { return m_active; }
	void *getFirstItemIn_TeamMemberList() const { return m_memberListHead; }

	TeamPrototype *m_proto;					// Team+0x04
	unsigned char m_unmodelled_008[0x0C - 0x08];
	void *m_memberListHead;					// Team+0x0C
	unsigned char m_unmodelled_010[0x31 - 0x10];
	Bool m_active;						// Team+0x31
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	void teamAboutToBeDeleted(Team *team);			// ILT 0x000228EF
};

extern TeamFactory *TheTeamFactory;

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
	void updateState(void);

	Player *getOwningPlayer() const { return m_owningPlayer; }
	Bool getIsSingleton() const { return (m_flags & 1) != 0; }

private:
	BfmeTeamInstanceIterator iterate_TeamInstanceList() const
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

	unsigned char m_unmodelled_000[8];
	Player *m_owningPlayer;					// +0x08
	unsigned char m_unmodelled_00c[0x18 - 0x0C];
	unsigned char m_flags;					// +0x18, bit 0 is the singleton flag
	unsigned char m_unmodelled_019[0x274 - 0x19];
	Team *m_teamInstanceList;				// +0x274
};

Player *Team::getControllingPlayer() const
{
	if( m_proto )
		return m_proto->getOwningPlayer();
	return 0;
}

// ?updateState@TeamPrototype@@QAEXXZ
void TeamPrototype::updateState(void)
{
	for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->updateState();
	}
	/* remove empty teams. */
	Bool done = false;
	while (!done) {
		done = true;
		for (BfmeTeamInstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
		{
			if (iter.cur()->getFirstItemIn_TeamMemberList() == 0)
			{
				// Team has no members.
				if (this->getIsSingleton())
				{
					continue; // Don't delete singleton teams, even if they are empty.
				}

				if (iter.cur()->getControllingPlayer() && iter.cur()->getControllingPlayer()->m_defaultTeam == iter.cur())
				{
					// This is the player's default team, so don't remove it.
					continue;
				}

				// don't delete inactive teams - they are under construction
				if (iter.cur()->isActive() == false)
				{
					continue;
				}

				// So remove it
				TheTeamFactory->teamAboutToBeDeleted(iter.cur());
				iter.cur()->deleteInstance();

				done = false;
				break; // Not sure what state the iterator is in after deleting a member of the list. jba
			}
		}
	}
}

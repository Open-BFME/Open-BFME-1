// cl: /DNDEBUG /MD /EHsc

// BFME keys teams by the pair of names used by its TeamFactory map.  This is
// the Zero Hour findTeam body with that second key forwarded through both
// lookups and BFME's TeamPrototype instance-list offsets.

class AsciiString;
class Team;

class TeamPrototype
{
public:
	Team *firstTeam() const { return m_teamInstanceList; }
	bool isSingleton() const { return (m_flags & 1) != 0; }

private:
	unsigned char m_unmodelled_000[ 0x18 ];
	unsigned int m_flags;
	unsigned char m_unmodelled_01c[ 0x274 - 0x1c ];
	Team *m_teamInstanceList;
};

class TeamFactory
{
public:
	Team *findTeam( const AsciiString &name, const AsciiString &owner );
	TeamPrototype *findTeamPrototype( const AsciiString &name, const AsciiString &owner );
	Team *createInactiveTeam( const AsciiString &name, const AsciiString &owner );
};

Team *TeamFactory::findTeam( const AsciiString &name, const AsciiString &owner )
{
	TeamPrototype *prototype = findTeamPrototype( name, owner );
	if( prototype )
	{
		Team *team = prototype->firstTeam();
		if( team == 0 && !prototype->isSingleton() )
			team = createInactiveTeam( name, owner );
		return team;
	}
	return 0;
}

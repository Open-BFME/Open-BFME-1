// cl: /DNDEBUG /MD /EHsc
// The four TeamFactory bodies that make or find a Team, and they are
// consecutive in the image:
//
//   0x000F7CA0  createTeam             33B
//   0x000F7CD0  createTemporaryTeam   ~90B
//   0x000F7E70  createTeamOnPrototype 155B
//   0x000F7F40  findTeam               65B
//
// Four adjacent bodies is itself the argument that they were one translation
// unit before they were four.
//
// The models they shared had drifted in every way this project sees:
//
// Team. One file gave it 0x33 bytes ending at the two flags, another 0x110
// bytes -- which is the size createTeamOnPrototype and createTemporaryTeam
// both allocate -- and the flag at +0x32 was m_started in one file and
// m_created in the other, with the identical two-line body setting it. It is
// one byte with one name now.
//
// TeamPrototype. findTeam named the singleton flag at +0x18 and the instance
// list at +0x274; createTemporaryTeam knew only that the whole thing is 0x278
// bytes because it news one. Those corroborate rather than conflict: the named
// layout ends at +0x274 plus a pointer, which is exactly 0x278. The two
// singleton reads stay distinct on purpose -- findTeam reads +0x18 as a dword
// and createTeamOnPrototype reads it as a byte, and the width is in the bytes.
//
// TeamFactory. One file knew the unique team id at +0x1C, another knew the
// prototype id at +0x18 and the team id after it. One layout holds both.
//
// AND THE CALLEE THAT IS DECLARED TWICE ON PURPOSE. createTeam reaches
// createInactiveTeam through the ILT thunk at 0x0000D15C, and reverse pins that
// spelling as the PRIVATE ?bfmeCreateInactiveTeam@TeamFactory@@AAE...; findTeam
// reaches the same function at its body, 0x000F7AB0, pinned as the PUBLIC
// ?createInactiveTeam@TeamFactory@@QAE.... One function, two routes, two
// decorations, two addresses -- so both declarations stay and each body keeps
// the spelling that lands on its own call target. Collapsing them to one name
// would move one of the two calls.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

class Player;
class TeamFactory;
class TeamPrototype;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	void __cdecl format(AsciiString fmt, ...);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Dict.h
class Dict
{
public:
	Dict(int numPairsToPreAllocate);			// ILT 0x00002ECD -> 0x00068550
	~Dict() { releaseData(); }

private:
	void releaseData();					// ILT 0x00014475 -> 0x000681C0
	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	Team(TeamPrototype *prototype, UnsignedInt id);		// ILT 0x00031638 -> 0x000F7790

	__forceinline void setActive() {
		if (!m_active) {
			m_created = 1;
			m_active = 1;
		}
	}

	char m_padding[0x31];
	UnsignedByte m_active;					// +0x31
	UnsignedByte m_created;					// +0x32
	char m_tail[0xdd];					// total 0x110
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
		Player *pOwner, bool isSingleton, Dict *d, int id);

	Team *firstTeam() const { return m_teamInstanceList; }
	bool isSingleton() const { return (m_flags & 1) != 0; }

	// createTeamOnPrototype reads the same flag a byte wide, and the width is
	// in its bytes, so the two readers stay distinct.
	__forceinline bool getIsSingleton() const {
		return (*(const UnsignedByte *)&m_flags & 1) != 0;
	}
	__forceinline Team *getFirstItemIn_TeamInstanceList() const {
		return m_teamInstanceList;
	}

private:
	unsigned char m_unmodelled_000[ 0x18 ];
	UnsignedInt m_flags;					// +0x18
	unsigned char m_unmodelled_01c[ 0x274 - 0x1c ];
	Team *m_teamInstanceList;				// +0x274, ending the 0x278 object
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	unsigned char m_pad[0x1c];
	AsciiString m_playerName;				// +0x1C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory
{
public:
	Team *createTeam(const AsciiString &owner, const AsciiString &name);
	Team *createTemporaryTeam(Player *player);
	Team *createTeamOnPrototype(TeamPrototype *prototype);
	Team *findTeam(const AsciiString &name, const AsciiString &owner);

	TeamPrototype *findTeamPrototype(const AsciiString &name, const AsciiString &owner);
	Team *createInactiveTeam(const AsciiString &name, const AsciiString &owner);	///< the body, 0x000F7AB0

private:
	/// the same function reached through the ILT thunk at 0x0000D15C
	Team *bfmeCreateInactiveTeam(const AsciiString &owner, const AsciiString &name);

	char m_pad[0x18];
	int m_uniqueTeamPrototypeID;				// +0x18
	UnsignedInt m_uniqueTeamID;				// +0x1C
};

// ?createTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@0@Z
Team *TeamFactory::createTeam(const AsciiString &owner, const AsciiString &name)
{
	Team *team = bfmeCreateInactiveTeam(owner, name);
	if (!team->m_active)
	{
		team->m_created = 1;
		team->m_active = 1;
	}
	return team;
}

// ?createTemporaryTeam@TeamFactory@@QAEPAVTeam@@PAVPlayer@@@Z
//
// The method name is a reconstruction from the __TempTeam%d format string; it
// is not a recovered original identifier (absent from ZH Team.cpp/Team.h and
// from exports).
Team *TeamFactory::createTemporaryTeam(Player *player)
{
	Dict dict(0);
	AsciiString name;
	name.format(AsciiString("__TempTeam%d"), m_uniqueTeamPrototypeID + 1);
	TeamPrototype *proto = new TeamPrototype(this, player->m_playerName, name, player, true, &dict, ++m_uniqueTeamPrototypeID);
	if (!proto)
		return 0;
	return new Team(proto, ++m_uniqueTeamID);
}

// ?createTeamOnPrototype@TeamFactory@@QAEPAVTeam@@PAVTeamPrototype@@@Z
//
// The caller at 0x000F7FA0 is TeamPrototype::xfer, and its call to this body
// identifies the method.
Team *TeamFactory::createTeamOnPrototype(TeamPrototype *prototype)
{
  if (prototype == 0)
    return 0;

  Team *team = 0;
  if (prototype->getIsSingleton()) {
    team = prototype->getFirstItemIn_TeamInstanceList();
    if (team)
      return team;
  }

  team = new Team(prototype, ++m_uniqueTeamID);
  team->setActive();
  return team;
}

// ?findTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@0@Z
//
// BFME keys teams by the pair of names its TeamFactory map uses. This is the
// Zero Hour body with that second key forwarded through both lookups.
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

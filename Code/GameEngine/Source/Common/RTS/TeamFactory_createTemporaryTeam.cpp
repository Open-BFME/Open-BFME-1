// cl: /DNDEBUG /MD /EHsc
//
// 0x000F7CD0: TeamFactory helper that formats __TempTeam%d, constructs a
// 0x278-byte TeamPrototype and a 0x110-byte Team. The method name is a
// reconstruction from that format string -- it is not a recovered original
// identifier (absent from ZH Team.cpp/Team.h and from exports).
//
// Dict is the four-byte m_data object: ctor ??0Dict@@QAE@H@Z (ILT 0x00002ECD
// -> matched 0x00068550), destructor inlines to releaseData (ILT 0x00014475
// -> matched 0x000681C0). TeamPrototype takes Dict* as in
// TeamFactoryCtorThunk.cpp. Team ctor is the matched
// ??0Team@@QAE@PAVTeamPrototype@@I@Z (ILT 0x00031638 -> 0x000F7790, 631B).
// Owner string is the argument's +0x1c (same Player slice as
// CastleBehaviorIsPlayerAllowedToCapture).

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

class Dict
{
public:
	Dict(int numPairsToPreAllocate);
	~Dict() { releaseData(); }

private:
	void releaseData();
	void *m_data;
};

class Player;
class TeamFactory;

class TeamPrototype
{
public:
	TeamPrototype(TeamFactory *tf, const AsciiString &owner, const AsciiString &name,
		Player *pOwner, bool isSingleton, Dict *d, int id);
private:
	char m_bytes[0x278];
};

class Team
{
public:
	Team(TeamPrototype *prototype, unsigned int id);
private:
	char m_bytes[0x110];
};

class Player
{
public:
	unsigned char m_pad[0x1c];
	AsciiString m_playerName;
};

class TeamFactory
{
public:
	Team *createTemporaryTeam(Player *player);

private:
	char m_pad[0x18];
	int m_uniqueTeamPrototypeID;
	int m_uniqueTeamID;
};

// ?createTemporaryTeam@TeamFactory@@QAEPAVTeam@@PAVPlayer@@@Z
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

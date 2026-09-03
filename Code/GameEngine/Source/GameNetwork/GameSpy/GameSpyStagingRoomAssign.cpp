// cl: /O2 /Ob0
//
// Retail 0x004F15B0: GameSpyStagingRoom::operator=.  Base GameInfo assign,
// then eight 0x78-byte GameSpyGameSlot assigns from this+0x58, then the
// GameSpy-only fields from +0x418.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo &operator=(const GameInfo &other);

private:
	char m_pad[0x58];
};

class Rva004F0D30
{
public:
	Rva004F0D30 &operator=(const Rva004F0D30 &other);

private:
	char m_pad[0x78];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	UnicodeString &operator=(const UnicodeString &other);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString &operator=(const AsciiString &other);

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom &operator=(const GameSpyStagingRoom &other);

private:
	Rva004F0D30 m_GameSpySlot[8];
	UnicodeString m_gameName;
	int m_id;
	void *m_transport;
	AsciiString m_localName;
	unsigned char m_requiresPassword;
	unsigned char m_allowObservers;
	unsigned int m_version;
	unsigned int m_exeCRC;
	unsigned int m_iniCRC;
	int m_extra438;
	unsigned char m_isQM;
	int m_extra440;
	AsciiString m_ladderIP;
	AsciiString m_pingStr;
	int m_pingInt;
	unsigned short m_ladderPort;
	int m_reportedNumPlayers;
	int m_reportedMaxPlayers;
	int m_reportedNumObservers;
	int m_extra460;
	int m_extra464;
};

// ??4GameSpyStagingRoom@@QAEAAV0@ABV0@@Z
GameSpyStagingRoom &GameSpyStagingRoom::operator=(const GameSpyStagingRoom &other)
{
	GameInfo::operator=(other);
	for (int i = 0; i < 8; i++)
		m_GameSpySlot[i] = other.m_GameSpySlot[i];
	m_gameName = other.m_gameName;
	m_id = other.m_id;
	m_transport = other.m_transport;
	m_localName = other.m_localName;
	m_requiresPassword = other.m_requiresPassword;
	m_allowObservers = other.m_allowObservers;
	m_version = other.m_version;
	m_exeCRC = other.m_exeCRC;
	m_iniCRC = other.m_iniCRC;
	m_extra438 = other.m_extra438;
	m_isQM = other.m_isQM;
	m_extra440 = other.m_extra440;
	m_ladderIP = other.m_ladderIP;
	m_pingStr = other.m_pingStr;
	m_pingInt = other.m_pingInt;
	m_ladderPort = other.m_ladderPort;
	m_reportedNumPlayers = other.m_reportedNumPlayers;
	m_reportedMaxPlayers = other.m_reportedMaxPlayers;
	m_reportedNumObservers = other.m_reportedNumObservers;
	m_extra460 = other.m_extra460;
	m_extra464 = other.m_extra464;
	return *this;
}

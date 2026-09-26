// cl: /DNDEBUG /MD /EHsc

extern const char g_bfmeEmptyAscii[];

class AsciiString
{
public:
	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	AsciiString() : m_data(0) {}
	~AsciiString() { releaseBuffer(); }

	void set(const char *text, int length);
	void concat(const char *text, int length);
	Header *m_data;

	private:
	void releaseBuffer();
};

static __forceinline int asciiLength(const AsciiString::Header *data)
{
	return data ? data->length : 0;
}

static __forceinline const char *asciiText(const AsciiString::Header *data)
{
	return data ? data->data : g_bfmeEmptyAscii;
}

class Team
{
public:
	void setActive()
	{
		if (!m_active)
		{
			m_created = true;
			m_active = true;
		}
	}

private:
	unsigned char m_pad[0x31];
	bool m_active;
	bool m_created;
};

class TeamFactory
{
public:
	Team *findTeam(const AsciiString &owner, const AsciiString &name);
};

extern TeamFactory *TheTeamFactory;

class Player
{
public:
	void setDefaultTeam();

private:
	unsigned char m_pad00[0x1c];
	AsciiString m_playerName;
	unsigned char m_pad20[0x210];
	Team *m_defaultTeam;
};

// ?setDefaultTeam@Player@@QAEXXZ
void Player::setDefaultTeam()
{
	AsciiString teamName;
	teamName.set("team", 4);
	teamName.concat(asciiText(m_playerName.m_data), asciiLength(m_playerName.m_data));
	Team *team = TheTeamFactory->findTeam(m_playerName, teamName);
	if (team)
	{
		m_defaultTeam = team;
		team->setActive();
	}
}

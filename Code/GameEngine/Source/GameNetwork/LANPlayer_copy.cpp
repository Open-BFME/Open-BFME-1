// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

template <typename Character>
class StringBase
{
public:
	StringBase(const StringBase &other);
	~StringBase(void);

private:
	Character *m_data;
};

class LANPlayerUnicodeString : private StringBase<unsigned short>
{
public:
	LANPlayerUnicodeString(const LANPlayerUnicodeString &other)
		: StringBase<unsigned short>(other)
	{
	}

	~LANPlayerUnicodeString(void)
	{
	}
};

class LANPlayer
{
public:
	LANPlayer(const LANPlayer &other);

private:
	LANPlayerUnicodeString m_name;
	LANPlayerUnicodeString m_login;
	LANPlayerUnicodeString m_host;
	unsigned int m_lastHeard;
	LANPlayer *m_next;
	unsigned int m_ip;
	unsigned int m_addressPadding;
};

LANPlayer::LANPlayer(const LANPlayer &other)
	: m_name(other.m_name),
	  m_login(other.m_login),
	  m_host(other.m_host),
	  m_lastHeard(other.m_lastHeard),
	  m_next(other.m_next),
	  m_ip(other.m_ip),
	  m_addressPadding(other.m_addressPadding)
{
}

// cl: /DNDEBUG /MD /EHsc

// Retail 0x00638150, the default GameSpyGameSlot constructor.
// The base GameSlot keeps one wide and one narrow string at +0x28 and +0x2c.

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { releaseBuffer(); }
	void clear() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class UnicodeString
{
public:
	UnicodeString() : m_data(0) {}
	~UnicodeString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class GameSlot
{
public:
	GameSlot();
	virtual void reset() = 0;

private:
	unsigned char m_prefix[0x24];
	UnicodeString m_name;
	AsciiString m_serial;
	unsigned int m_connectInfo;
	unsigned short m_value34;
	unsigned char m_tail[0x0e];
};

class GameSpyGameSlot : public GameSlot
{
public:
	GameSpyGameSlot();

private:
	int m_profileID;
	AsciiString m_gameSpyLogin;
	AsciiString m_gameSpyLocale;
	AsciiString m_pingStr;
	int m_pingInt;
	int m_wins;
	int m_losses;
	int m_rankPoints;
	int m_favoriteSide;
	int m_extra68;
	int m_extra6c;
	AsciiString m_extra70;
	AsciiString m_extra74;
};

#pragma comment(linker, "/alternatename:??0GameSlot@@QAE@XZ=?j_00013e58@@YAXXZ")

GameSpyGameSlot::GameSpyGameSlot()
{
	GameSlot();
	m_gameSpyLogin.clear();
	m_gameSpyLocale.clear();
	m_profileID = 0;
	m_wins = 0;
	m_losses = 0;
	m_rankPoints = 0;
	m_favoriteSide = 0;
	m_pingInt = 0;
	m_profileID = 0;
	m_pingStr.clear();
	m_extra6c = -1;
	m_extra68 = -1;
}

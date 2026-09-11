// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// GameSlot::reset is called by the retail GameSlot constructor at 0x0061F0C0.
// The BFME layout extends the Zero Hour slot with an AsciiString at +0x2C and
// a four-byte connection block at +0x34.  The comma expression keeps the four
// adjacent reset stores in their source order while preserving VC7.1's shared
// -1 value for the remaining fields.

class AsciiString
{
public:
	void clear();

private:
	void *m_data;
};

struct GameSlotConnectInfo
{
	GameSlotConnectInfo() : m_port(0) {}

	int m_unused;
	unsigned short m_port;
	char m_padding[2];
};

struct GameSlotConnectStorage
{
	GameSlotConnectStorage &operator=(const GameSlotConnectInfo &that)
	{
		*(unsigned int *)this = *(const unsigned int *)&that.m_port;
		return *this;
	}

	unsigned short m_port;
	char m_padding[2];
};

class GameSlot
{
public:
	virtual void reset();

private:
	int m_state;
	bool m_isAccepted;
	bool m_hasMap;
	bool m_isMuted;
	char m_pad0b;
	int m_color;
	int m_startPos;
	int m_playerTemplate;
	int m_teamNumber;
	int m_origColor;
	int m_origStartPos;
	int m_origPlayerTemplate;
	void *m_name;
	AsciiString m_slotNameKeyText;
	unsigned int m_ip;
	GameSlotConnectStorage m_connectInfo;
	int m_nat;
	unsigned int m_lastFrameInGame;
	bool m_disconnected;
};

void GameSlot::reset()
{
	int emptyValue = -1;
	m_color = (m_state = 1, m_isAccepted = false,
		m_hasMap = true, emptyValue);
	GameSlotConnectInfo emptyConnectInfo;
	emptyConnectInfo.m_port = 0;
	*(volatile unsigned int *)&m_connectInfo =
		*(const unsigned int *)&emptyConnectInfo.m_port;
	m_startPos = emptyValue;
	m_playerTemplate = emptyValue;
	m_teamNumber = emptyValue;
	m_nat = 1;
	m_lastFrameInGame = 0;
	m_disconnected = false;
	m_ip = 0;
	m_isMuted = false;
	m_origPlayerTemplate = emptyValue;
	m_origStartPos = emptyValue;
	m_origColor = emptyValue;
	m_slotNameKeyText.clear();
}

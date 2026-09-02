// ?reset@GameSlot@@UAEXXZ
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

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

	unsigned short m_port;
	unsigned short m_padding;
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
	GameSlotConnectInfo m_connectInfo;
	int m_nat;
	unsigned int m_lastFrameInGame;
	bool m_disconnected;
};

// ?reset@GameSlot@@UAEXXZ
void GameSlot::reset()
{
	int emptyValue = -1;
	GameSlotConnectInfo emptyConnectInfo;
	m_connectInfo = emptyConnectInfo;
	m_state = 1;
	m_isAccepted = false;
	m_hasMap = true;
	m_color = emptyValue;
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

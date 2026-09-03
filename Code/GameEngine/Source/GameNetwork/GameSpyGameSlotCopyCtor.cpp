// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GameSpyGameSlot copy constructor, retail 0x004FA0A0, 203 bytes.
// Copies the GameSlot base (0x0006E600), stores vtable 0x01102FD0, then the
// BFME GameSpy fields: profile id, three AsciiStrings, seven POD dwords, two
// more AsciiStrings.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase();

	int *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot(const GameSlot &other);
	~GameSlot();
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);

private:
	unsigned char m_body[0x44 - 4];
};

class GameSpyGameSlot : public GameSlot
{
public:
	virtual void slot0(void);
	virtual void slot1(void);
	virtual void slot2(void);

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

void GameSpyGameSlot::slot0(void) {}
void GameSpyGameSlot::slot1(void) {}
void GameSpyGameSlot::slot2(void) {}

inline void *operator new(unsigned int, void *place) { return place; }

void BfmeGameSpyGameSlotCopyAnchor(void *storage, const GameSpyGameSlot &other)
{
	new (storage) GameSpyGameSlot(other);
}

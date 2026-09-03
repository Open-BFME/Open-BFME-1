// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GameInfo copy constructor, retail 0x004F9A70, 134 bytes.
// Compiler-generated copy of the BFME GameInfo object. It stores the same
// vtable the default ctor at 0x00620310 installs (0x01102F7C), copies the
// three bools as bytes, block-copies the eight slot pointers, and calls
// AsciiString's copy ctor for the map name at +0x3C.

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

class GameSlot;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void reset(void);

private:
	int m_preorderMask;
	int m_crcInterval;
	unsigned char m_inGame;
	unsigned char m_inProgress;
	unsigned char m_surrendered;
	int m_gameID;
	GameSlot *m_slots[8];
	int m_localIP;
	int m_extra38;
	AsciiString m_mapName;
	int m_mapCRC;
	int m_mapSize;
	int m_mapMask;
	int m_seed;
	int m_useStats;
	int m_tail;
};

inline void *operator new(unsigned int, void *place) { return place; }

void BfmeGameInfoCopyAnchor(void *storage, const GameInfo &other)
{
	new (storage) GameInfo(other);
}

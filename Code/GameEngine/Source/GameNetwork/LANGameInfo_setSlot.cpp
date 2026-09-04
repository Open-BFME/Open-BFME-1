// cl: /DNDEBUG /MD /EHsc
// LANGameInfo::setSlot, retail 0x0068EA70 (119 bytes).

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset();
	void setAccept() { m_isAccepted = true; }
	void setMapAvailability(Bool hasMap);

protected:
	Int m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	UnsignedByte m_bfmeTail[0x44 - 0x0b];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANPlayer.h
class LANPlayer
{
	UnsignedByte m_bfmeBody[0x1c];
};

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/LANGameInfo.h
class LANGameSlot : public GameSlot
{
public:
	LANGameSlot& operator=(const LANGameSlot& other);
	~LANGameSlot();

private:
	LANPlayer m_user;
	StringBase<char> m_serial;
	UnsignedInt m_lastHeard;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
protected:
	UnsignedByte m_bfmeBody[0x58];
};

// ?setSlot@LANGameInfo@@QAEXHVLANGameSlot@@@Z
class LANGameInfo : public GameInfo
{
public:
	void setSlot(Int slotNum, LANGameSlot slotInfo);

private:
	LANGameSlot m_LANSlot[MAX_SLOTS];
};

void LANGameInfo::setSlot(Int slotNum, LANGameSlot slotInfo)
{
	if (slotNum < 0 || slotNum >= MAX_SLOTS)
		return;

	m_LANSlot[slotNum] = slotInfo;

	if (slotNum == 0)
	{
		m_LANSlot[slotNum].setAccept();
		m_LANSlot[slotNum].setMapAvailability(true);
	}
}

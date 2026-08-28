// cl: /DNDEBUG /MD /EHsc

// Six destructible members, destroyed in reverse declaration order with the
// unwind state counting down 4 to -1.
//
// ??_M gives the array: base +0x58, eight elements, 0x78 bytes each. Eight times
// 0x78 is 0x3C0, which lands exactly on +0x418 where the next member starts --
// the arithmetic checking out is what confirms the reading.
//
// Two different releaseBuffer targets appear, so two string types: the narrow one
// and StringBase<unsigned short> for the wide member at +0x418. The name is QAE,
// public and non-virtual, so there is no vptr and the layout starts with data.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();

	char *m_data;
};

template <class T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();

	T *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
};

class GameSpyStagingRoomSlot
{
public:
	~GameSpyStagingRoomSlot();

private:
	unsigned char m_body[0x78];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	~GameSpyStagingRoom();

private:
	unsigned char m_gap0[0x3C];
	BFMERetailAsciiString m_name;
	unsigned char m_gap1[0x18];
	GameSpyStagingRoomSlot m_slots[8];
	UnicodeString m_wide;
	unsigned char m_gap2[0x08];
	BFMERetailAsciiString m_424;
	unsigned char m_gap3[0x1C];
	BFMERetailAsciiString m_444;
	BFMERetailAsciiString m_448;
};

// ??1GameSpyStagingRoom@@QAE@XZ
GameSpyStagingRoom::~GameSpyStagingRoom()
{
}

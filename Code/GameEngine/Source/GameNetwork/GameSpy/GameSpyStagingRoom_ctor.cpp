// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ??0GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp

#include "string_base.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	__forceinline AsciiString() : m_data(0) {}
	~AsciiString();

	__forceinline void set(const char *text, Int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}

	__forceinline void clear()
	{
		((StringBase<char> *)this)->clear();
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	__forceinline UnicodeString() : m_data(0) {}
	~UnicodeString();

private:
	unsigned short *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot();
	~GameSlot();
	virtual void reset();

private:
	unsigned char m_body[0x3C];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	~GameInfo();
	virtual Int bfmeVtableSlot0();
	virtual Int bfmeVtableSlot1();
	virtual void reset();

	void setSlotPointer(Int index, GameSlot *slot);

private:
	// The matched GameInfo constructor fixes the BFME base at 0x58 bytes.
	unsigned char m_body[0x54];
};

class GameSpyGameSlot : public GameSlot
{
public:
	GameSpyGameSlot();

private:
	// The array constructor and cleanUpSlotPointers independently fix this stride.
	unsigned char m_body[0x38];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom : public GameInfo
{
public:
	GameSpyStagingRoom();
	virtual void reset();

private:
	GameSpyGameSlot m_slots[8];
	UnicodeString m_gameName;
	Int m_id;
	void *m_transport;
	AsciiString m_localName;
	Bool m_requiresPassword;
	Bool m_allowObservers;
	unsigned char m_pad42A[6];
	UnsignedInt m_exeCRC;
	UnsignedInt m_iniCRC;
	UnsignedInt m_version;
	Bool m_isQM;
	unsigned char m_pad43D[3];
	Int m_qmLadderType;
	AsciiString m_ladderIP;
	AsciiString m_pingString;
	Int m_ping;
	UnsignedShort m_ladderPort;
	unsigned char m_pad452[10];
	Int m_reportedNumPlayers;
	Int m_reportedMaxPlayers;
	Int m_reportedNumObservers;
};

GameSpyStagingRoom::GameSpyStagingRoom()
{
	for (Int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_slots[i]);

	m_transport = 0;
	m_localName.set("localhost", 9);
	m_ladderIP.clear();
	m_ladderPort = 0;
	m_reportedMaxPlayers = 0;
	m_isQM = false;
	m_qmLadderType = 0;
	m_exeCRC = 0;
	m_iniCRC = 0;
	m_version = 0;
	m_reportedNumObservers = 0;
}

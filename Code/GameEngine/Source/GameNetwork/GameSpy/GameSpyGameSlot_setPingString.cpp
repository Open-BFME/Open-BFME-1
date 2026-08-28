// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?getLocalSlotNum@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
// readable body of ?reset@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
// readable body of ?resetAccepted@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
// readable body of ?setPingString@GameSpyGameSlot@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp
// readable body of ?setPingString@GameSpyStagingRoom@@: Code/GameEngine/Source/GameNetwork/GameSpy/StagingRoomGameInfo.cpp

#include "string_base.h"

typedef int Int;
typedef bool Bool;

struct statsgame_s;
typedef statsgame_s *statsgame_t;

extern "C" void FreeGame(statsgame_t game);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	__forceinline AsciiString() : m_data(0) {}

	__forceinline AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(*(const StringBase<char> *)&other);
	}

	~AsciiString();

	__forceinline AsciiString &operator=(const AsciiString &other)
	{
		((StringBase<char> *)this)->set(*(const StringBase<char> *)&other);
		return *this;
	}

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfoInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual AsciiString getLocalName();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67();
	virtual void slot68();
	virtual void slot69();
	virtual Int getPingValue(const AsciiString &other);
};

extern GameSpyInfoInterface *TheGameSpyInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isPlayer(AsciiString userName) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual Int bfmeVtableSlot0();
	virtual Int bfmeVtableSlot1();
	virtual void reset();
	virtual void startGame(Int gameID);
	virtual Bool amIHost() const;
	virtual Int getLocalSlotNum() const;
	const GameSlot *getConstSlot(Int index) const;
	virtual void resetAccepted();

protected:
	unsigned char m_body[8];
	Bool m_inGame;
	unsigned char m_pad[3];
};

class GameSpyGameSlot
{
public:
	void setPingString(AsciiString pingString);

private:
	// The constructor fixes the ping fields at +0x50 and +0x54.
	unsigned char m_body[0x50];
	AsciiString m_pingString;
	Int m_ping;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom : public GameInfo
{
public:
	void setPingString(AsciiString pingString);
	virtual void reset();
	virtual Bool amIHost() const;
	virtual Int getLocalSlotNum() const;
	virtual void resetAccepted();

private:
	// The constructor fixes the ping fields at +0x448 and +0x44C.
	unsigned char m_derivedBody[0x438];
	AsciiString m_pingString;
	Int m_ping;
	unsigned char m_tail[0x14];
	statsgame_t m_statsGame;
};

void GameSpyGameSlot::setPingString(AsciiString pingString)
{
	m_pingString = pingString;
	m_ping = TheGameSpyInfo->getPingValue(pingString);
}

void GameSpyStagingRoom::setPingString(AsciiString pingString)
{
	m_pingString = pingString;
	m_ping = TheGameSpyInfo->getPingValue(pingString);
}

Int GameSpyStagingRoom::getLocalSlotNum() const
{
	if (!m_inGame)
		return -1;

	AsciiString localName = TheGameSpyInfo->getLocalName();
	for (Int i = 0; i < 8; ++i)
	{
		const GameSlot *slot = getConstSlot(i);
		if (slot != 0 && slot->isPlayer(localName))
			return i;
	}

	return -1;
}

void GameSpyStagingRoom::resetAccepted()
{
	GameInfo::resetAccepted();
	amIHost();
}

void GameSpyStagingRoom::reset()
{
	GameInfo::reset();
	if (m_statsGame != 0)
		FreeGame(m_statsGame);
	m_statsGame = 0;
}

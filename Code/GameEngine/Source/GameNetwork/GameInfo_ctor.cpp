// cl: /DNDEBUG /MD /EHsc
// readable body of ??0GameInfo@@QAE@XZ: Code/GameEngine/Source/GameNetwork/GameInfo.cpp

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	__forceinline AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

class GameSlot;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Money.h
class Money
{
public:
	__forceinline Money() : m_value(0) {}

private:
	int m_value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	virtual void reset();

private:
	int m_preorderMask;
	int m_crcInterval;
	unsigned char m_inGame;
	unsigned char m_inProgress;
	unsigned char m_oldFactionsOnly;
	unsigned char m_padding0f;
	int m_gameID;
	GameSlot *m_slots[8];
	Money m_startingCash;
	unsigned short m_superweaponRestriction;
	unsigned char m_padding3a[2];
	AsciiString m_mapName;
};

GameInfo::GameInfo()
	: m_superweaponRestriction(0)
{
	for (int i = 0; i < 8; ++i)
		m_slots[i] = 0;
	reset();
}

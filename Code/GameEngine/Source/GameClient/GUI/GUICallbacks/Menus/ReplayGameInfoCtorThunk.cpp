// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// BFME's GameInfo base is 0x58 bytes and its ReplayGameInfo slots are
// 0x44-byte objects beginning at +0x58.  The shared ZH headers describe a
// 0x60/+0x40 layout, so this constructor keeps the retail layout local.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot();
	~GameSlot();
	virtual void reset();

	char m_bfmeFields[0x40];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	~GameInfo();
	virtual void reset();
	void setSlotPointer(Int index, GameSlot *slot);

	char m_bfmeFields[0x54];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class ReplayGameInfo : public GameInfo
{
private:
	GameSlot m_ReplaySlot[8];

public:
	ReplayGameInfo();
};

ReplayGameInfo::ReplayGameInfo()
{
	for (Int i = 0; i < 8; ++i) {
		setSlotPointer(i, &m_ReplaySlot[i]);
	}
}

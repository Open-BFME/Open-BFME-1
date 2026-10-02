// cl: /DNDEBUG /MD /EHsc
// SinglePlayerSkirmishGameInfo's constructor, retail 0x00619720 (134 bytes).
// It installs the Snapshot table 0x011171C8, whose slot-2 literal getter
// 0x00619820 returns "SinglePlayerSkirmishGameInfo", and its object is stored
// to 0x012F7090 by the caller at 0x0061B58B. The byte twin at 0x00075C10 is
// SkirmishGameInfo's (SkirmishGameInfoCtor.cpp). Evidence:
// targets/game/reverse/identity_evidence/0061fda0-singleplayerskirmishgameinfo-xfer.md.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	GameSlot();
	~GameSlot();
private:
	unsigned char m_storage[0x44];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameInfo();
	virtual ~GameInfo();
	void setSlotPointer(int index, GameSlot *slot);
private:
	unsigned char m_storage[0x54];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
};

class SinglePlayerSkirmishGameInfo : public GameInfo, public Snapshot
{
public:
	SinglePlayerSkirmishGameInfo();
	virtual ~SinglePlayerSkirmishGameInfo();
private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();
	GameSlot m_skirmishSlot[8];	// twin layout of SkirmishGameInfo; member name unproven
};

// ??0SinglePlayerSkirmishGameInfo@@QAE@XZ
SinglePlayerSkirmishGameInfo::SinglePlayerSkirmishGameInfo()
{
	for (int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_skirmishSlot[i]);
}

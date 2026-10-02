// cl: /DNDEBUG /MD /EHsc

// SkirmishGameInfo's constructor, retail 0x00075C10 (134 bytes).
// It installs the Snapshot table 0x01075E7C, whose slot-2 literal getter
// 0x00075CF0 returns "SkirmishGameInfo" and whose slot 3 is SkirmishGameInfo::xfer
// (0x0061F930); BfmeAptScreenSkirmish stores the new object to 0x012F7094
// (TheSkirmishGameInfo) at 0x0057BEA7. A byte twin of
// SinglePlayerSkirmishGameInfoCtor.cpp (0x00619720): only the EH table and
// the two vtables differ. Evidence:
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

class SkirmishGameInfo : public GameInfo, public Snapshot
{
public:
	SkirmishGameInfo();
	virtual ~SkirmishGameInfo();
private:
	virtual void crc(void *);
	virtual void xfer(void *);
	virtual void loadPostProcess();
	GameSlot m_slots[8];
};

// ??0SkirmishGameInfo@@QAE@XZ
SkirmishGameInfo::SkirmishGameInfo()
{
	for (int i = 0; i < 8; ++i)
		setSlotPointer(i, &m_slots[i]);
}


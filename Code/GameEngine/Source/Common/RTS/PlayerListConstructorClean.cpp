// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PlayerList@@: Code/GameEngine/Source/Common/RTS/PlayerList.cpp
// Open-BFME5: lift the retail PlayerList constructor to clean C++.

// Keep the base classes local to this reconstruction.  The shipped ZH headers
// describe a different PlayerList layout (16 players rather than BFME's 32)
// and would therefore move the constructor's stores and EH frame.
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Player;

class Snapshot
{
public:
	Snapshot()
	{
		*(volatile unsigned int *)this = 0x01073744;
	}
	virtual ~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

// The retail constructor calls the player-storage constructor through the
// incremental-link thunk at 0x00041943.  This carrier is deliberately local:
// it records the observed allocation ABI without claiming an unresolved
// public class identity for the 0x6a4-byte object.
class Rva000DFBD0PlayerStorage
{
public:
	Rva000DFBD0PlayerStorage(int playerIndex);

private:
	unsigned char m_bytes[0x6a4];
};

extern void j_00041943();
extern void j_00030e90();

#pragma comment(linker, "/alternatename:??0Rva000DFBD0PlayerStorage@@QAE@H@Z=?j_00041943@@YAXXZ")

class __declspec(novtable) PlayerList : public SubsystemInterface, public Snapshot
{
public:
	PlayerList();
	virtual void init();

private:
	Player *m_local;
	int m_playerCount;
	Rva000DFBD0PlayerStorage *m_players[32];
};

#pragma comment(linker, "/alternatename:?init@PlayerList@@UAEXXZ=?j_00030e90@@YAXXZ")

// ??0PlayerList@@QAE@XZ
PlayerList::PlayerList()
{
	// Snapshot's base vtable is installed by its inlined constructor, then
	// replaced by the derived PlayerList pair at +8 and +0.
	*(volatile void **)((char *)this + 0) = (void *)0x0108417c;
	*(volatile void **)((char *)this + 8) = (void *)0x01084168;
	m_local = 0;
	m_playerCount = 0;

	for (int i = 0; i < 32; ++i)
	{
		m_players[i] = new Rva000DFBD0PlayerStorage(i);
	}

	init();
}

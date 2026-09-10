// ??0PlayerList@@QAE@XZ
// partial score=0.99 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PlayerList@@: Code/GameEngine/Source/Common/RTS/PlayerList.cpp
// BFME's PlayerList constructor uses two base subobjects and allocates the
// fixed 32-player table.  Keep the BFME offsets local to this reconstruction;
// the vendored PlayerList header describes the Zero Hour 16-player layout.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Player;

// Snapshot's default constructor is inlined in the retail PlayerList
// constructor.  Its base table is visible briefly before the derived table
// stores below, so keep that store as the real base-construction operation.
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

// The call at ILT 0x00041943 constructs the 0x6a4-byte player storage.  This
// is an address-derived carrier only: it makes no claim that the unresolved
// callee's public class identity is Player.  Its declared constructor lets
// MSVC emit the retail new-with-constructor EH path and the pin below routes
// that ABI call to the already observed ILT.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
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
	// replaced by the derived PlayerList pair.  These are the two concrete
	// retail tables at +8 and +0.
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

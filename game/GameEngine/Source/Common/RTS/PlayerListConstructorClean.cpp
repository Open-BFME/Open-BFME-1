// cl: /DNDEBUG /MD /EHsc
// readable body of ??0PlayerList@@: game/GameEngine/Source/Common/RTS/PlayerList.cpp
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

// The three vftable aliases stay: a `__identifier` extern of a ??_7X@@6B@ name
// is only accepted as the implicit vftable of the class it names, and taking it
// over makes this TU *emit* strong non-COMDAT definitions of retail's
// ??_7Snapshot@@6B@, ??_7PlayerList@@6BSnapshot@@@ and
// ??_7PlayerList@@6BSubsystemInterface@@@ data (plus new __purecall / ??_E*
// externals), which would shadow the resolver's pins for those data addresses.
extern "C" const void *bfmeVftSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftSnapshot=??_7Snapshot@@6B@")

class Snapshot
{
public:
	Snapshot()
	{
		*(volatile unsigned int *)this = (unsigned int)bfmeVftSnapshot;
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

// The ctor call still needs the alias: `new Rva000DFBD0PlayerStorage(i)` is the
// only spelling MSVC expands into retail's allocation shape (the frame temp at
// [esp+0x10], the null path's `jmp +2; xor eax,eax`), and a hand-written
// ::operator new plus member-pointer ctor call moves every register in the loop.
#pragma comment(linker, "/alternatename:??0Rva000DFBD0PlayerStorage@@QAE@H@Z=?j_00041943@@YAXXZ")

// A no-base carrier for the init() call below: a member pointer to a class
// without bases is the bare code address, so the union's call folds back into
// the direct thiscall the retail body performs.
class Rva00030E90Thunk
{
};

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

extern "C" void *bfmeVftPlayerListSubsystemInterface[];
extern "C" void *bfmeVftPlayerListSnapshot[];
#pragma comment(linker, "/alternatename:_bfmeVftPlayerListSubsystemInterface=??_7PlayerList@@6BSubsystemInterface@@@")
#pragma comment(linker, "/alternatename:_bfmeVftPlayerListSnapshot=??_7PlayerList@@6BSnapshot@@@")

// ??0PlayerList@@QAE@XZ
PlayerList::PlayerList()
{
	// Snapshot's base vtable is installed by its inlined constructor, then
	// replaced by the derived PlayerList pair at +8 and +0.
	*(volatile void **)((char *)this + 0) = bfmeVftPlayerListSubsystemInterface;
	*(volatile void **)((char *)this + 8) = bfmeVftPlayerListSnapshot;
	m_local = 0;
	m_playerCount = 0;

	for (int i = 0; i < 32; ++i)
	{
		m_players[i] = new Rva000DFBD0PlayerStorage(i);
	}

	// init() is reached through retail's incremental-link thunk at 0x00030E90.
	union { void (*fn)(); void (Rva00030E90Thunk::*call)(); } u = { j_00030e90 };
	((Rva00030E90Thunk *)this->*u.call)();
}

// cl: /DNDEBUG /MD /EHs-c-
// readable body of ?init@PlayerList@@: Code/GameEngine/Source/Common/RTS/PlayerList.cpp
// readable body of ?setLocalPlayer@PlayerList@@: Code/GameEngine/Source/Common/RTS/PlayerList.cpp
// Open-BFME5: PlayerList::setLocalPlayer, retail 0x000DF3C0, 97 bytes,
// converted out of Code/gen_asm/d_000d6fb0.asm. zh_sweep packet 000df3c0
// carries the earlier investigation; this finishes it.
//
// Zero Hour's body covers the first 45 bytes exactly and stops there. BFME
// appends 52 bytes that notify two subsystems, each with a function pointer,
// and the second notification is a tail call with the incoming argument slot
// overwritten. Both are outside the `player != m_local` guard -- retail's
// `je 0x000DF3ED` jumps past the swap and lands on the first of them -- so they
// run on every call, not only when the local player actually changes.
//
// What the two globals are:
//
//   0x012ED5BC  TheShroudManager. The engine-init block at 0x0038A2AC stores
//               the freshly constructed object here and then sets its name from
//               the literal "TheShroudManager" at 0x010EB3E0, the same
//               constructor-tag evidence that named TheRadar. Its neighbours
//               agree: 0x012ED5C4 takes "TheCollisionManager" twenty bytes
//               later in the same block.
//
//   0x012ED5C0  unnamed. Nothing in .text stores to it -- 25 reads, no write --
//               so whatever constructs it does so through a pointer, and the
//               init block skips straight from 0x012ED5BC to 0x012ED5C4. It
//               keeps an address-derived name until something proves one.
//
// The two methods are forwarders of the same shape, `mov ecx,[ecx+0x0C]; jmp`,
// which is why they are named for their addresses rather than guessed at: the
// body behind 0x008F7380 stores its two arguments at +0x64 and +0x6C of the
// object hanging off +0x0C, and nothing here says what those fields mean.
//
// The two function pointers are the ledger's own d_001072A0 and d_001072F0,
// 58-byte siblings 0x50 apart that each notify TheDisplay through vtable slot
// 0x10C/0x118 and TheRadar through 0x24/0x2C. Their addresses are relocation
// sites, so the byte gate does not depend on which one is which -- but the
// shapes match the two calls, and taking their address is what retail does.

typedef int Int;

class AsciiString;
class Team;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

class PlayerTemplate;

typedef unsigned short PlayerMaskType;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Player.h
class Player
{
public:
	void becomingLocalPlayer( bool becoming );
	void init( const PlayerTemplate *pt );

	unsigned char m_unreconstructed_00[0x24];
	Int m_playerRefreshTag;									///< +0x24, handed to the shroud manager
};

// The ledger's names for the two callbacks; see the header comment. The first
// is real C++ in SubsystemRefreshCallbacks.cpp and takes its three arguments;
// the second remains a byte dump under the no-argument name.
void d_001072a0( Int a1, Int a2, Int a3 );
void d_001072f0( void );

typedef void (*SubsystemRefreshProc3)( Int, Int, Int );
typedef void (*SubsystemRefreshProc)( void );

class ShroudManager
{
public:
	__declspec(noinline) void m_008F7380( Int tag, SubsystemRefreshProc3 refresh );
};

class Gen_012ED5C0
{
public:
	void m_00880E10( SubsystemRefreshProc refresh );
};

// The retail forwarder method names remain address-derived. The
// ShroudManager owner is anchored by its constructor tag; 0x012ED5C0 remains
// unnamed. Their declarations preserve the incoming argument widths so the
// compiler emits the target's `ret 4`/`ret 8`.
struct T_008f8c30 { void m( Int tag, SubsystemRefreshProc3 refresh ); };

extern ShroudManager *TheShroudManager;
extern Gen_012ED5C0 *g_012ED5C0;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerList.h
class PlayerList : public SubsystemInterface, public Snapshot
{
public:
	virtual void init( void );
	void setLocalPlayer( Player *player );
	Player *getNthPlayer( Int i );
	Player *getNeutralPlayer( void ) { return m_players[0]; }

private:
	Player *m_local;										///< +0x0C
	int m_playerCount;										///< +0x10
	Player *m_players[32];									///< +0x14
};

// ?m_008F7380@ShroudManager@@QAEXHP6AXHHH@Z@Z
__declspec(noinline) void ShroudManager::m_008F7380( Int tag, SubsystemRefreshProc3 refresh )
{
	((T_008f8c30 *)*(void **)((char *)this + 12))->m( tag, refresh );
}

//-----------------------------------------------------------------------------
// ?setLocalPlayer@PlayerList@@QAEXPAVPlayer@@@Z
void PlayerList::setLocalPlayer( Player *player )
{
	if (player == 0)
		player = getNeutralPlayer();

	if (player != m_local)
	{
		if (m_local)
			m_local->becomingLocalPlayer(false);
		m_local = player;
		player->becomingLocalPlayer(true);
	}

	if (TheShroudManager)
		TheShroudManager->m_008F7380(player->m_playerRefreshTag, d_001072a0);

	if (g_012ED5C0)
		g_012ED5C0->m_00880E10(d_001072f0);
}

//-----------------------------------------------------------------------------
// ?init@PlayerList@@UAEXXZ
//
// 128 bytes at 0x000DFA80, and its tail is setLocalPlayer inlined -- the same
// two subsystem notifications, reached the same way. That is what says the two
// bodies belong together: the standalone copy above is still emitted, and this
// one carries an inlined duplicate of it.
void PlayerList::init()
{
	m_playerCount = 1;
	m_players[0]->init(0);

	for (int i = 1; i < 32; i++)
		m_players[i]->init(0);

	// call setLocalPlayer so that becomingLocalPlayer() gets called appropriately
	setLocalPlayer(m_players[0]);

}

//-----------------------------------------------------------------------------
// ?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z
//
// The bound is 32, and that one byte is why this body is here and not in
// PlayerList.cpp: retail compares against 0x20 where the vendored
// MAX_PLAYER_COUNT gives 0x10. The same byte splits getEachPlayerFromMask
// below, twice.
Player *PlayerList::getNthPlayer(Int i)
{
	if( i < 0 || i >= 32 )
	{
		return 0;
	}
	return m_players[i];
}

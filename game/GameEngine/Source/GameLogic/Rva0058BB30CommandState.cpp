// cl: /O2 /DNDEBUG /MD
//
// Retail 0x0058BB30 (183 bytes): refreshes a small command-state record.
// The generated placeholder labels this entry as a free no-argument function,
// but the retail body consumes ECX as its record receiver and writes offsets
// +0 and +4, then fills the half-open range [+8, +0x1c).  The owner preserves that raw
// ABI without assigning an unsupported game-class identity.

typedef unsigned char Bool;

struct Rva00367E30Logic
{
public:
	unsigned char m_pad_000[0x10c];
	int m_mode_10c;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Glo012F1028Type
{
public:
	unsigned char m_pad_000[0x2c];
	unsigned char m_flag_02c;
	unsigned char m_flag_02d;
	unsigned char m_pad_02e[0x10c - 0x2e];
	int m_mode_10c;
};

extern Glo012F1028Type *Glo012F1028;

struct Rva002EE330PlayerList
{
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class Rva0058BB30Player
{
public:
	Bool isPlayerActive() const;
};

class AsciiString;

class CommandSet;

class ControlBar
{
public:
	const CommandSet *findCommandSet(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// These are the actual retail ILT thunks used by this body.  Their generated
// declarations are intentionally void/no-argument; the calls below recover
// only the register, stack, and return widths proven by 0x0058BB30 and by the
// retail thunk destinations.  No new alias pin is needed.
extern void j_0000762b();
extern void j_000179bd();
extern void j_00005a6a();
extern void j_00029dc0();
extern void j_00048cca();
extern void j_00023f88();

typedef Rva0058BB30Player *(__fastcall *GetLocalPlayerCall)(Rva002EE330PlayerList *);
typedef void *(__fastcall *LookupPlayerObjectCall)(Rva0058BB30Player *);
typedef const AsciiString *(__fastcall *GetCommandSetStringCall)(void *);
typedef void (__cdecl *FillByteRangeCall)(unsigned char *, unsigned char *, const unsigned char *);

class Rva0058BB30CommandState
{
public:
	void __fastcall refresh();

private:
	void *m_player;
	const CommandSet *m_commandSet;
	unsigned char m_unmodelled_008[0x1c - 0x08];
};

void __fastcall Rva0058BB30CommandState::refresh()
{
	register int mode = TheBfmeGameLogic->m_mode_10c;
	register Rva0058BB30CommandState &record = *this;
	// The first two mode tests intentionally dereference the known global before
	// the later flag pair's explicit null check; this is the retail branch order.
	if (mode == 8 || mode == 4)
	{
		record.m_player = 0;
		record.m_commandSet = 0;
		return;
	}

	if (Glo012F1028 != 0 && Glo012F1028->m_flag_02c != 0 &&
		Glo012F1028->m_flag_02d != 0)
	{
		record.m_player = 0;
		record.m_commandSet = 0;
		return;
	}

	register Rva002EE330PlayerList *players = Rva002EE330ThePlayers;
	Rva0058BB30Player *player =
		((GetLocalPlayerCall)j_0000762b)(players);
	typedef Bool (Rva0058BB30Player::*PlayerActiveCall)() const;
	union
	{
		void (*raw)(void);
		PlayerActiveCall member;
	} isPlayerActive;
	isPlayerActive.raw = j_000179bd;
	if (player != 0 &&
		!(reinterpret_cast<Rva0058BB30Player *>(player)->*
			isPlayerActive.member)())
		player = 0;

	if (player == record.m_player)
		return;

	record.m_player = player;
	record.m_commandSet = 0;
	if (player == 0)
		return;

	void *object = ((LookupPlayerObjectCall)j_00005a6a)(player);
	if (object == 0)
		return;

	const AsciiString *name =
		((GetCommandSetStringCall)j_00029dc0)(object);
	typedef const CommandSet *(ControlBar::*FindCommandSetCall)(const AsciiString &);
	union
	{
		void (*raw)(void);
		FindCommandSetCall member;
	} findCommandSet;
	findCommandSet.raw = j_00048cca;
	record.m_commandSet =
		(TheControlBar->*findCommandSet.member)(*name);

	unsigned char fillValue = 1;
	((FillByteRangeCall)j_00023f88)(
		reinterpret_cast<unsigned char *>(&record) + 8,
		reinterpret_cast<unsigned char *>(&record) + 0x1c,
		&fillValue);
}

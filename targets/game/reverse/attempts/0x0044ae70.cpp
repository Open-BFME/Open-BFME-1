// ??1InGameUI@@UAE@XZ
// partial score=0.90 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc
// Stashed reconstruction, not a landed body: keep it out of game/ until the
// two vtable stores below are reproducible. See the verdict row in
// re_attempts.log for what is left.
// Retail 0x0044AE70, 936 bytes.
//
// One user-declared destructor plus everything the compiler synthesises for
// it: two vtable stores, thirty EH states, and the implicit destruction of
// twenty-eight members in reverse declaration order. Both halves are
// load-bearing, so the class below is a view whose every field sits where
// retail reads it -- the offsets are checked at compile time at the bottom of
// this file, because a destructor is exactly the body where a field in the
// wrong place is invisible until the whole thing is compared.
//
// The two bases are ordered by the stores. 0x10F5B38 goes over the vptr at
// +0x00 and nothing is called for that base, so it is polymorphic with no
// destructor of its own and four bytes of payload, which puts the secondary
// base at +0x08. There 0x10F5B24 is written first -- the secondary base as
// seen through InGameUI -- and 0x1073744 replaces it immediately before the
// base destructor call, which is the base's own table. So the base whose
// destructor runs is the one at +0x08.
//
// The member view is measured, not invented: the twenty-eight offsets are the
// twenty-eight `lea`/vector-`_M` cleanup sites in the retail body, and every
// gap between them is an unreconstructed pad so the next site lands on its own
// offset. Which member is *what* is not recoverable from a destructor alone,
// so the types are named by offset and promise only what retail needs -- a
// non-trivial destructor, so the implicit cleanup exists at all, and a size
// that makes the element sizes in the `_M` pushes come out 0x04, 0x10, 0x14,
// 0x20 and 0x30.
//
// Destructors are declared and never defined, here and in the siblings: a
// definition in this TU would be inlined and the call retail makes would
// disappear. None of them is defined anywhere, exactly as
// BfmeMilitarySubtitleRecord's is not. The one exception is the secondary
// base's non-destructor virtual below, which is defined on purpose: it is the
// key function, and without a table in this object file the compiler drops the
// vptr store that retail makes before the base call.
//
// The two members the body cleans up by hand, +0x081C and +0x0560, are held as
// plain storage and reached through address-keyed casts, so the implicit pass
// has no destructor to call for either. That is what retail shows: the delete
// at +0x9C is the only visit to +0x081C and the release at +0xB8 the only
// visit to +0x0560.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned char UnsignedByte;

// ---------------------------------------------------------------- members

// One out-of-line destructor call each. The two at +0x18 and +0x1C are the
// same type: retail calls one function twice, four bytes apart.
struct Rva0044AE70Dtor
{
	~Rva0044AE70Dtor();
	UnsignedInt m_pad;
};

// +0x14 and the twelve more below it: releaseBuffer through a 4-byte
// `char*`, the BFME StringBase shape (see BFMERetailAsciiString in
// InGameUI.cpp). `set` has its only call site, at +0x14.
struct BfmeDtorString
{
	~BfmeDtorString() { releaseBuffer(); }
	char *m_data;
	void releaseBuffer();
	void set(const BfmeDtorString &other);
};

extern BfmeDtorString Rva01336E50EmptyString;

// +0x12F8: the one member whose destructor is a call followed by inline code
// in the caller. The head pointer is tested and handed to a __stdcall
// deallocate(head, 0x10) that takes ecx from nowhere, so that is a plain
// function and not a member call.
// __cdecl: retail's `add esp, 8` after this call is the caller popping the two
// arguments, which is the cdecl convention, so the declaration must not be
// __stdcall -- that moves the pop into the callee and the two bytes go away.
void nodeDealloc(void *p, UnsignedInt count);

struct Rva0044AE70Dtor12F8
{
	~Rva0044AE70Dtor12F8() { helper(); if (m_head) nodeDealloc(m_head, 16); }
	void helper();
	void *m_head;
};


// The five member arrays. Size is the whole contract: `_M` takes the element
// size as an argument and retail pushes 4, 0x10, 0x14, 0x20 and 0x30.
struct Rva0044AE70Elem04 { ~Rva0044AE70Elem04(); UnsignedInt m_pad; };
struct Rva0044AE70Elem10 { ~Rva0044AE70Elem10(); UnsignedInt m_pad[4]; };
struct Rva0044AE70Elem14 { ~Rva0044AE70Elem14(); UnsignedInt m_pad[5]; };
struct Rva0044AE70Elem20 { ~Rva0044AE70Elem20(); UnsignedInt m_pad[8]; };
struct Rva0044AE70Elem30 { ~Rva0044AE70Elem30(); UnsignedInt m_pad[12]; };

// ------------------------------------------------------------------ bases

// +0x00..+0x07. No destructor is called for this base: retail's four direct
// calls at +0x170..+0x185 clean it up from the body instead.
class BfmeBaseShim
{
public:
	virtual void baseSlot00();
	UnsignedInt m_pad;
};

// +0x08..+0x0B holds this base's own vptr, and its destructor is the one
// retail calls at the end -- `this` at +0x00, the table at +0x08, and
// 0x1073744 replacing the 0x10F5B24 the derived view wrote there at the top.
// That is the whole reason the hierarchy is a chain and not a pair of
// siblings: a second base with a destructor would have had its `this` at
// +0x08, and MSVC would have had to keep that address in a frame slot, which
// retail's 8-byte frame has no room for. The chain puts the second vptr at
// +0x08 while the base itself still starts at +0x00.
//
// `subsystemInit` is the key function and the only reason it exists:
// defining it puts ??_7SubsystemInterface@@6B@ in this object file, which is
// what lets the destructor store it before the base call.
class SubsystemInterface : public BfmeBaseShim
{
public:
	virtual ~SubsystemInterface();
	virtual void subsystemInit();

private:
	void subsystemRelease();
};

void SubsystemInterface::subsystemInit()
{
	subsystemRelease();
}


// ------------------------------------------------------------- the globals

class Rva0044AE70Glo12F33F8
{
public:
	virtual ~Rva0044AE70Glo12F33F8();
};

class Rva0044AE70Glo12F4B98Type
{
public:
	virtual ~Rva0044AE70Glo12F4B98Type();
};

class Rva0044AE70Glo12F4B70
{
public:
	virtual ~Rva0044AE70Glo12F4B70();
};

class Rva0044AE70Glo12F4B78
{
public:
	virtual ~Rva0044AE70Glo12F4B78();
};

// TheMouse: capture at slot 16 (+0x40), setCursor(int) at slot 14 (+0x38).
class MouseShim
{
public:
	virtual void mouseSlot00();
	virtual void mouseSlot01();
	virtual void mouseSlot02();
	virtual void mouseSlot03();
	virtual void mouseSlot04();
	virtual void mouseSlot05();
	virtual void mouseSlot06();
	virtual void mouseSlot07();
	virtual void mouseSlot08();
	virtual void mouseSlot09();
	virtual void mouseSlot0A();
	virtual void mouseSlot0B();
	virtual void mouseSlot0C();
	virtual void mouseSlot0D();
	virtual void setCursor(Int cursor);
	virtual void mouseSlot0F();
	virtual void capture();
};

// +0x081C, reached only through the delete in the body.
class MilitarySubtitleShim
{
public:
	virtual ~MilitarySubtitleShim();
};

// +0x0560, m_pendingGUICommand: one virtual at slot 7 (+0x1C), no argument.
class CommandButtonShim
{
public:
	virtual void cbSlot0();
	virtual void cbSlot1();
	virtual void cbSlot2();
	virtual void cbSlot3();
	virtual void cbSlot4();
	virtual void cbSlot5();
	virtual void cbSlot6();
	virtual void release();
};

class DrawableShim;

// The two vtable entries the body calls. Retail reaches them through a
// pointer whose type it cannot establish, so the compiler has to load the
// table and call through it; calling them as members of InGameUI would be
// devirtualised into a direct call and the bytes would be wrong. +0xCC and
// +0x118 are 0x33 apart, which is what fixes the fillers between them.
class BfmeInGameUIVtable
{
public:
#define RVA0044AE70_VSLOT(n) virtual void vslot##n();
	RVA0044AE70_VSLOT(00) RVA0044AE70_VSLOT(01) RVA0044AE70_VSLOT(02)
	RVA0044AE70_VSLOT(03) RVA0044AE70_VSLOT(04) RVA0044AE70_VSLOT(05)
	RVA0044AE70_VSLOT(06) RVA0044AE70_VSLOT(07) RVA0044AE70_VSLOT(08)
	RVA0044AE70_VSLOT(09) RVA0044AE70_VSLOT(0A) RVA0044AE70_VSLOT(0B)
	RVA0044AE70_VSLOT(0C) RVA0044AE70_VSLOT(0D) RVA0044AE70_VSLOT(0E)
	RVA0044AE70_VSLOT(0F) RVA0044AE70_VSLOT(10) RVA0044AE70_VSLOT(11)
	RVA0044AE70_VSLOT(12) RVA0044AE70_VSLOT(13) RVA0044AE70_VSLOT(14)
	RVA0044AE70_VSLOT(15) RVA0044AE70_VSLOT(16) RVA0044AE70_VSLOT(17)
	RVA0044AE70_VSLOT(18) RVA0044AE70_VSLOT(19) RVA0044AE70_VSLOT(1A)
	RVA0044AE70_VSLOT(1B) RVA0044AE70_VSLOT(1C) RVA0044AE70_VSLOT(1D)
	RVA0044AE70_VSLOT(1E) RVA0044AE70_VSLOT(1F) RVA0044AE70_VSLOT(20)
	RVA0044AE70_VSLOT(21) RVA0044AE70_VSLOT(22) RVA0044AE70_VSLOT(23)
	RVA0044AE70_VSLOT(24) RVA0044AE70_VSLOT(25) RVA0044AE70_VSLOT(26)
	RVA0044AE70_VSLOT(27) RVA0044AE70_VSLOT(28) RVA0044AE70_VSLOT(29)
	RVA0044AE70_VSLOT(2A) RVA0044AE70_VSLOT(2B) RVA0044AE70_VSLOT(2C)
	RVA0044AE70_VSLOT(2D) RVA0044AE70_VSLOT(2E) RVA0044AE70_VSLOT(2F)
	RVA0044AE70_VSLOT(30) RVA0044AE70_VSLOT(31) RVA0044AE70_VSLOT(32)
	// +0xCC, one argument
	virtual void vslot0CC(const void *start);
	RVA0044AE70_VSLOT(33) RVA0044AE70_VSLOT(34) RVA0044AE70_VSLOT(35)
	RVA0044AE70_VSLOT(36) RVA0044AE70_VSLOT(37) RVA0044AE70_VSLOT(38)
	RVA0044AE70_VSLOT(39) RVA0044AE70_VSLOT(3A) RVA0044AE70_VSLOT(3B)
	RVA0044AE70_VSLOT(3C) RVA0044AE70_VSLOT(3D) RVA0044AE70_VSLOT(3E)
	RVA0044AE70_VSLOT(3F) RVA0044AE70_VSLOT(40) RVA0044AE70_VSLOT(41)
	RVA0044AE70_VSLOT(42) RVA0044AE70_VSLOT(43) RVA0044AE70_VSLOT(44)
	// +0x118, four arguments
	virtual void vslot118(const void *a, const void *b, const void *c, Bool d);
#undef RVA0044AE70_VSLOT
};

extern Rva0044AE70Glo12F33F8 *Rva0044AE70The12F33F8;
extern Rva0044AE70Glo12F4B98Type *Rva0044AE70The12F4B98;
extern Rva0044AE70Glo12F4B70 *Rva0044AE70The12F4B70;
extern Rva0044AE70Glo12F4B78 *Rva0044AE70The12F4B78;
extern MouseShim *TheMouse;

// -------------------------------------------------------------- the class

// Every field is public on purpose: a destructor is the one body where the
// access specifiers buy nothing, and uniform access is what keeps MSVC from
// being free to reorder the layout.
class InGameUI : public SubsystemInterface
{
public:
	virtual ~InGameUI();
	// Overriding a virtual of the +0x08 base is what makes the compiler emit a
	// second table for that vptr. Without an override it can reuse the primary
	// one and skips the store at +0x08 entirely, which is the store retail
	// opens the body with.
	virtual void subsystemInit();

	void removeMilitarySubtitle();
	void stopCameoMovie();
	void destroyPlacementIcons();
	void freeMessageResources();
	void clearOwnerVok();
	void clearBodies();
	void clearHint();
	void clearFloatingText();

	// +0x08..+0x0F. MSVC 7.1 gives the base chain eight bytes -- the second
	// vptr lands at +0x04, not +0x08 -- so the first four are padding and the
	// saved/loaded flags sit where retail has them, at +0x0C. These are the
	// only own fields before the first member with a destructor.
	UnsignedInt m_pad008;
	Bool m_superweaponHiddenByScript;		// +0x00C
	Bool m_inputEnabled;					// +0x00D
	unsigned short m_pad00E;					// +0x00E

	Rva0044AE70Dtor m_rva00010;				// +0x010
	BfmeDtorString m_currentlyPlayingMovie;		// +0x014
	Rva0044AE70Dtor m_rva00018;				// +0x018
	Rva0044AE70Dtor m_rva0001C;				// +0x01C
	UnsignedInt m_pad020[6];					// +0x020 .. +0x037
	Rva0044AE70Elem14 m_rva00038[25];			// +0x038, 25 * 0x14
	UnsignedInt m_pad22C[194];				// +0x22C .. +0x533
	const void *m_pendingPlaceType;				// +0x534
	UnsignedInt m_pendingPlaceSourceObjectID;	// +0x538
	DrawableShim **m_placeIcon;				// +0x53C
	UnsignedInt m_pad540[8];					// +0x540 .. +0x55F
	CommandButtonShim *m_pendingGUICommand;	// +0x560
	UnsignedInt m_pad564[2];					// +0x564 .. +0x56B
	Rva0044AE70Elem10 m_rva0056C[6];			// +0x56C, 6 * 0x10
	Rva0044AE70Elem20 m_rva005CC[12];			// +0x5CC, 12 * 0x20
	UnsignedInt m_pad74C[3];					// +0x74C .. +0x757
	BfmeDtorString m_rva00758;				// +0x758
	UnsignedInt m_pad75C[2];					// +0x75C .. +0x763
	BfmeDtorString m_rva00764;				// +0x764
	UnsignedInt m_pad768[5];					// +0x768 .. +0x77B
	Rva0044AE70Dtor m_rva0077C;				// +0x77C
	UnsignedInt m_pad780[9];					// +0x780 .. +0x7A3
	BfmeDtorString m_rva007A4;				// +0x7A4
	UnsignedInt m_pad7A8[3];					// +0x7A8 .. +0x7B3
	BfmeDtorString m_rva007B4;				// +0x7B4
	UnsignedInt m_pad7B8[3];					// +0x7B8 .. +0x7C3
	BfmeDtorString m_rva007C4;				// +0x7C4
	UnsignedInt m_pad7C8[3];					// +0x7C8 .. +0x7D3
	BfmeDtorString m_rva007D4;				// +0x7D4
	UnsignedInt m_pad7D8[3];					// +0x7D8 .. +0x7E3
	BfmeDtorString m_rva007E4;				// +0x7E4
	UnsignedInt m_pad7E8[3];					// +0x7E8 .. +0x7F3
	BfmeDtorString m_rva007F4;				// +0x7F4
	UnsignedInt m_pad7F8[3];					// +0x7F8 .. +0x803
	BfmeDtorString m_rva00804;				// +0x804
	UnsignedInt m_pad808[5];					// +0x808 .. +0x81B
	void *m_militarySubtitle;				// +0x81C
	Bool m_isScrolling;						// +0x820
	Bool m_isSelecting;						// +0x821
	unsigned short m_pad822;					// +0x822
	Int m_mouseMode;							// +0x824
	Int m_mouseModeCursor;					// +0x828
	UnsignedInt m_pad82C[8];				// +0x82C .. +0x84B
	BfmeDtorString m_rva0084C;				// +0x84C
	UnsignedInt m_pad850[10];				// +0x850 .. +0x877
	BfmeDtorString m_rva00878;				// +0x878
	UnsignedInt m_pad87C[2];					// +0x87C .. +0x883
	BfmeDtorString m_rva00884;				// +0x884
	UnsignedInt m_pad888[3];					// +0x888 .. +0x893
	Rva0044AE70Elem30 m_rva00894[53];			// +0x894, 53 * 0x30
	Rva0044AE70Dtor m_rva01284;				// +0x1284
	UnsignedInt m_pad1288[4];				// +0x1288 .. +0x1297
	Rva0044AE70Dtor m_rva01298;				// +0x1298
	UnsignedInt m_pad129C[9];				// +0x129C .. +0x12BF
	Rva0044AE70Dtor m_rva012C0;				// +0x12C0
	Rva0044AE70Dtor m_rva012C4;				// +0x12C4
	UnsignedInt m_pad12C8[12];				// +0x12C8 .. +0x12F7
	Rva0044AE70Dtor12F8 m_rva012F8;			// +0x12F8
	UnsignedInt m_pad12FC[2];				// +0x12FC .. +0x1303
	Rva0044AE70Dtor m_rva01304;				// +0x1304
	UnsignedInt m_pad1308[5];				// +0x1308 .. +0x131B
	Rva0044AE70Elem04 m_rva0131C[32];			// +0x131C, 32 * 0x04
	DrawableShim *m_idleWorkerWin;			// +0x139C, no destructor
};

// The body, in the order retail calls it: four singleton deletes with their
// null stores, the subtitle pointer, the pending command, the empty-string
// reset, the placement teardown, the message resources, the icon array, and
// the four clearing helpers.
InGameUI::~InGameUI()
{
	delete Rva0044AE70The12F33F8;
	Rva0044AE70The12F33F8 = 0;

	delete Rva0044AE70The12F4B98;
	Rva0044AE70The12F4B98 = 0;

	delete Rva0044AE70The12F4B70;
	Rva0044AE70The12F4B70 = 0;

	delete Rva0044AE70The12F4B78;
	Rva0044AE70The12F4B78 = 0;

	removeMilitarySubtitle();

	delete (MilitarySubtitleShim *)m_militarySubtitle;
	m_militarySubtitle = 0;

	if (m_pendingGUICommand != 0)
		m_pendingGUICommand->release();
	m_pendingGUICommand = 0;

	if (m_currentlyPlayingMovie.m_data != 0 &&
		*(const unsigned short *)(m_currentlyPlayingMovie.m_data + 4) != 0)
		m_currentlyPlayingMovie.set(Rva01336E50EmptyString);

	stopCameoMovie();

	m_pendingPlaceType = 0;
	m_pendingPlaceSourceObjectID = 0;

	if (TheMouse != 0)
	{
		if (m_mouseMode == 1)
		{
			m_mouseMode = 0;
			m_mouseModeCursor = 2;
			TheMouse->capture();
			if (TheMouse != 0)
				TheMouse->setCursor(2);
		}
	}

	((BfmeInGameUIVtable *)this)->vslot0CC(0);

	destroyPlacementIcons();

	((BfmeInGameUIVtable *)this)->vslot118(0, 0, 0, 1);

	freeMessageResources();

	delete[] m_placeIcon;
	m_placeIcon = 0;

	clearOwnerVok();
	clearBodies();
	clearHint();
	clearFloatingText();
}

// ---------------------------------------------------------------- offsets
//
// A destructor reads every field it destroys, so a field one slot out of
// place shows up as a wall of diffs rather than as an error. These typedefs
// turn each offset into a compile error instead; a negative array size is the
// only spelling of "static_assert" MSVC 7.1 has.


// ---------------------------------------------------------------- offsets
//
// A destructor reads every field it destroys, so a field one slot out of place
// shows up as a wall of diffs rather than as an error. These typedefs turn each
// offset into a compile error instead; a negative array size is the only
// spelling of "static_assert" MSVC 7.1 has.

#define BFME_AT(member, off) \
	typedef char BfmeNeed_##member##_##off[ \
		(((UnsignedInt)(char *)&((InGameUI *)0)->member) == (off)) ? 1 : -1]

BFME_AT(m_superweaponHiddenByScript, 0x00C);
BFME_AT(m_rva00010, 0x010);
BFME_AT(m_currentlyPlayingMovie, 0x014);
BFME_AT(m_rva00018, 0x018);
BFME_AT(m_rva0001C, 0x01C);
BFME_AT(m_rva00038, 0x038);
BFME_AT(m_pendingPlaceType, 0x534);
BFME_AT(m_pendingPlaceSourceObjectID, 0x538);
BFME_AT(m_placeIcon, 0x53C);
BFME_AT(m_pendingGUICommand, 0x560);
BFME_AT(m_rva0056C, 0x56C);
BFME_AT(m_rva005CC, 0x5CC);
BFME_AT(m_rva00758, 0x758);
BFME_AT(m_rva00764, 0x764);
BFME_AT(m_rva0077C, 0x77C);
BFME_AT(m_rva007A4, 0x7A4);
BFME_AT(m_rva007B4, 0x7B4);
BFME_AT(m_rva007C4, 0x7C4);
BFME_AT(m_rva007D4, 0x7D4);
BFME_AT(m_rva007E4, 0x7E4);
BFME_AT(m_rva007F4, 0x7F4);
BFME_AT(m_rva00804, 0x804);
BFME_AT(m_militarySubtitle, 0x81C);
BFME_AT(m_mouseMode, 0x824);
BFME_AT(m_mouseModeCursor, 0x828);
BFME_AT(m_rva0084C, 0x84C);
BFME_AT(m_rva00878, 0x878);
BFME_AT(m_rva00884, 0x884);
BFME_AT(m_rva00894, 0x894);
BFME_AT(m_rva01284, 0x1284);
BFME_AT(m_rva01298, 0x1298);
BFME_AT(m_rva012C0, 0x12C0);
BFME_AT(m_rva012C4, 0x12C4);
BFME_AT(m_rva012F8, 0x12F8);
BFME_AT(m_rva01304, 0x1304);
BFME_AT(m_rva0131C, 0x131C);
BFME_AT(m_idleWorkerWin, 0x139C);

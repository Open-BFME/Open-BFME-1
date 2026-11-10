// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
// readable body of ??1InGameUI@@UAE@XZ: game/GameEngine/Source/GameClient/InGameUI.cpp
// Handoff: targets/game/reverse/attempt_support/20261107-0044ae70-ingameui-dtor.md
// Retail 0x0044AE70, 936 bytes.
// The primary vtable identifies InGameUI at +0. The Snapshot vtable sits at +8.
// Retail cleanup sites set the member offsets. Compile-time checks verify each offset.
// The destructor uses thirty EH states and destroys twenty-eight members in reverse order.
// Element types match the sizes passed to the retail vector cleanup calls.
// The STLport containers at +0x10, +0x18, +0x1C, +0x77C, +0x1298, +0x12C0, +0x12C4 and
// +0x1304 are the constructor TU's types (InGameUIConstructor.cpp). Retail's body calls
// their out-of-line base destructors (_List_base/_Rb_tree) while the unwind funclets call
// the distinct out-of-line list/map destructors, so the container destructor is inline here.
// That inline layer is also what gives MSVC retail's EBX zero and EBP movie-string address.
// The remaining member destructors stay undefined so MSVC emits calls instead of inlining them.
// Snapshot's defined virtual method makes MSVC emit the secondary vtable store.
// The members at +0x81C and +0x560 stay plain storage because the body deletes or releases them directly.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned char UnsignedByte;

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <map>
#include <new>
#include "ascii_string.h"
#include "subsystem_interface.h"
#include "snapshot.h"

// ---------------------------------------------------------------- members

// One out-of-line destructor call each. The two at +0x18 and +0x1C are the
// same type: retail calls one function twice, four bytes apart.
// +0x1284: RadiusDecal, destroyed through its out-of-line destructor (0x00458340).
class RadiusDecal
{
public:
	~RadiusDecal();
	UnsignedInt m_template;
};


// Element types. The linker's incremental-thunk order (tools/ilt_oracle.py) confirms
// each base-destructor instantiation at its retail address; see
// targets/game/reverse/identity_evidence/0x0044ae70-ingameui-dtor-callees.md.
class WindowLayout;
class Drawable;
class FloatingTextData;
class WorldAnimationData;
class NamedTimerInfo;
struct Rva004402D0Element;
// +0x1304 holds 8-byte POD elements (ilt_oracle fits ICoord2D at 0x00440510, but that
// instantiation name is already pinned to other bodies), so the element is address-named.
struct Rva00440510Element { unsigned int first, second; };
// +0x14 and the twelve more below it are AsciiStrings: each destructor is the
// out-of-line StringBase<char>::releaseBuffer, and +0x14's reset is StringBase::set.


// +0x12F8: a list whose base destructor retail inlined: the out-of-line
// _List_base<Gen_t_00443e40_p8cd>::clear (0x00443E40, the ledger's instantiation
// name), then the node allocator's deallocate of the sentinel node (16 bytes).
struct Gen_t_00443e40_p8cd;
namespace _STL {
template <> void _List_base<Gen_t_00443e40_p8cd, allocator<Gen_t_00443e40_p8cd> >::clear();
}
struct Rva0044AE70Dtor12F8
{
	~Rva0044AE70Dtor12F8()
	{
		((_STL::_List_base<Gen_t_00443e40_p8cd, _STL::allocator<Gen_t_00443e40_p8cd> > *)this)->clear();
		if (m_head) _STL::_Node_alloc::deallocate(m_head, 16);
	}
	void *m_head;
};


// The five member arrays. Size is the whole contract: `_M` takes the element
// size as an argument and retail pushes 4, 0x10, 0x14, 0x20 and 0x30.
struct MoveHint0043AAD0 { ~MoveHint0043AAD0(); UnsignedInt field_00, field_04, field_08, field_0c; Bool field_10; };
struct Message0043DBA0 { ~Message0043DBA0(); UnsignedInt text, displayString, timestamp, color; };
struct Map0044B780 { ~Map0044B780(); UnsignedInt storage[3]; };
struct List00442C90 { ~List00442C90(); void *head; };
class RadiusDecalTemplate { public: ~RadiusDecalTemplate(); UnsignedInt storage[12]; };

// ------------------------------------------------------------------ bases

// ------------------------------------------------------------- the globals

class ControlBar { public: virtual ~ControlBar(); };
class Glo012F4B98Type { public: virtual ~Glo012F4B98Type(); };
class BfmeGlobal_012f4b70 { public: virtual ~BfmeGlobal_012f4b70(); };
class Rva0044AE70Glo12F4B78 { public: virtual ~Rva0044AE70Glo12F4B78(); };
extern ControlBar *TheControlBar;
extern Glo012F4B98Type *Glo012F4B98;
extern BfmeGlobal_012f4b70 *TheBfmeGlobal_012f4b70;
extern void *g_bfmeSubsystem012F4B78;

// TheMouse: capture at slot 16 (+0x40), setCursor(int) at slot 14 (+0x38).
class Mouse
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

extern ControlBar *TheControlBar;
extern Glo012F4B98Type *Glo012F4B98;
extern BfmeGlobal_012f4b70 *TheBfmeGlobal_012f4b70;
extern void *g_bfmeSubsystem012F4B78;
extern Mouse *TheMouse;

// 0x0043FBB0 (ledger ?bfmeClear@Gen_0043FBB0@@QAEXXZ): BFME's list clear called
// between clearWorldAnimations and resetIdleWorker; its InGameUI name is unproven.
class Gen_0043FBB0 { public: void bfmeClear(); };

// -------------------------------------------------------------- the class

// Every field is public on purpose: a destructor is the one body where the
// access specifiers buy nothing, and uniform access is what keeps MSVC from
// being free to reorder the layout.
class InGameUI : public SubsystemInterface, public Snapshot
{
public:
	virtual ~InGameUI();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual const char *GetSnapshotName();
	virtual void LoadPostProcess();
	virtual void DoXfer(Xfer &);
	virtual void removeMilitarySubtitle();
	virtual void stopCameoMovie();
	void destroyPlacementIcons();
	void freeMessageResources();
protected:
	void clearFloatingText();
	void clearWorldAnimations();
private:
	virtual void resetIdleWorker();
public:

	// The two bases occupy +0x00..+0x0B.
	Bool m_superweaponHiddenByScript;		// +0x00C
	Bool m_inputEnabled;					// +0x00D
	unsigned short m_pad00E;					// +0x00E

	_STL::list<WindowLayout *> m_rva00010;				// +0x010
	AsciiString m_currentlyPlayingMovie;		// +0x014
	_STL::list<Drawable *> m_rva00018;				// +0x018
	_STL::list<Drawable *> m_rva0001C;				// +0x01C
	UnsignedInt m_pad020[6];					// +0x020 .. +0x037
	MoveHint0043AAD0 m_rva00038[25];			// +0x038, 25 * 0x14
	UnsignedInt m_pad22C[194];				// +0x22C .. +0x533
	const void *m_pendingPlaceType;				// +0x534
	UnsignedInt m_pendingPlaceSourceObjectID;	// +0x538
	DrawableShim **m_placeIcon;				// +0x53C
	UnsignedInt m_pad540[8];					// +0x540 .. +0x55F
	CommandButtonShim *m_pendingGUICommand;	// +0x560
	UnsignedInt m_pad564[2];					// +0x564 .. +0x56B
	Message0043DBA0 m_rva0056C[6];			// +0x56C, 6 * 0x10
	Map0044B780 m_rva005CC[32];			// +0x5CC, 32 * 0x0C
	UnsignedInt m_pad74C[3];					// +0x74C .. +0x757
	AsciiString m_rva00758;				// +0x758
	UnsignedInt m_pad75C[2];					// +0x75C .. +0x763
	AsciiString m_rva00764;				// +0x764
	UnsignedInt m_pad768[5];					// +0x768 .. +0x77B
	_STL::map<AsciiString, NamedTimerInfo *> m_rva0077C;				// +0x77C
	UnsignedInt m_pad788[7];					// +0x788 .. +0x7A3
	AsciiString m_rva007A4;				// +0x7A4
	UnsignedInt m_pad7A8[3];					// +0x7A8 .. +0x7B3
	AsciiString m_rva007B4;				// +0x7B4
	UnsignedInt m_pad7B8[3];					// +0x7B8 .. +0x7C3
	AsciiString m_rva007C4;				// +0x7C4
	UnsignedInt m_pad7C8[3];					// +0x7C8 .. +0x7D3
	AsciiString m_rva007D4;				// +0x7D4
	UnsignedInt m_pad7D8[3];					// +0x7D8 .. +0x7E3
	AsciiString m_rva007E4;				// +0x7E4
	UnsignedInt m_pad7E8[3];					// +0x7E8 .. +0x7F3
	AsciiString m_rva007F4;				// +0x7F4
	UnsignedInt m_pad7F8[3];					// +0x7F8 .. +0x803
	AsciiString m_rva00804;				// +0x804
	UnsignedInt m_pad808[5];					// +0x808 .. +0x81B
	void *m_militarySubtitle;				// +0x81C
	Bool m_isScrolling;						// +0x820
	Bool m_isSelecting;						// +0x821
	unsigned short m_pad822;					// +0x822
	Int m_mouseMode;							// +0x824
	Int m_mouseModeCursor;					// +0x828
	UnsignedInt m_pad82C[8];				// +0x82C .. +0x84B
	AsciiString m_rva0084C;				// +0x84C
	UnsignedInt m_pad850[10];				// +0x850 .. +0x877
	AsciiString m_rva00878;				// +0x878
	UnsignedInt m_pad87C[2];					// +0x87C .. +0x883
	AsciiString m_rva00884;				// +0x884
	UnsignedInt m_pad888[3];					// +0x888 .. +0x893
	RadiusDecalTemplate m_rva00894[53];			// +0x894, 53 * 0x30
	RadiusDecal m_rva01284;				// +0x1284
	UnsignedInt m_pad1288[4];				// +0x1288 .. +0x1297
	_STL::list<FloatingTextData *> m_rva01298;				// +0x1298
	UnsignedInt m_pad129C[9];				// +0x129C .. +0x12BF
	_STL::list<WorldAnimationData *> m_rva012C0;				// +0x12C0
	_STL::list<Rva004402D0Element *> m_rva012C4;				// +0x12C4
	UnsignedInt m_pad12C8[12];				// +0x12C8 .. +0x12F7
	Rva0044AE70Dtor12F8 m_rva012F8;			// +0x12F8
	UnsignedInt m_pad12FC[2];				// +0x12FC .. +0x1303
	_STL::list<Rva00440510Element> m_rva01304;				// +0x1304
	UnsignedInt m_pad1308[5];				// +0x1308 .. +0x131B
	List00442C90 m_rva0131C[32];			// +0x131C, 32 * 0x04
	DrawableShim *m_idleWorkerWin;			// +0x139C, no destructor
};

// The body, in the order retail calls it: four singleton deletes with their
// null stores, the subtitle pointer, the pending command, the empty-string
// reset, the placement teardown, the message resources, the icon array, and
// the four clearing helpers.
InGameUI::~InGameUI()
{
	delete TheControlBar;
	TheControlBar = 0;

	delete Glo012F4B98;
	Glo012F4B98 = 0;

	delete TheBfmeGlobal_012f4b70;
	TheBfmeGlobal_012f4b70 = 0;

	delete (Rva0044AE70Glo12F4B78 *)g_bfmeSubsystem012F4B78;
	g_bfmeSubsystem012F4B78 = 0;

	InGameUI::removeMilitarySubtitle();

	delete (MilitarySubtitleShim *)m_militarySubtitle;
	m_militarySubtitle = 0;

	if (m_pendingGUICommand != 0)
	{
		m_pendingGUICommand->release();
		m_pendingGUICommand = 0;
	}

	const char *movieData = *(const char *const *)&m_currentlyPlayingMovie;
	if (movieData != 0 && *(const unsigned short *)(movieData + 4) != 0)
		m_currentlyPlayingMovie.set(AsciiString::TheEmptyString);

	InGameUI::stopCameoMovie();

	m_pendingPlaceType = 0;
	m_pendingPlaceSourceObjectID = 0;

	if (TheMouse != 0)
	{
		if (m_mouseMode == 1)
		{
			m_mouseMode = 0;
			m_mouseModeCursor = 2;
		}
		TheMouse->capture();
		if (TheMouse != 0)
			TheMouse->setCursor(2);

		((BfmeInGameUIVtable *)this)->vslot0CC(0);

		destroyPlacementIcons();
	}

	((BfmeInGameUIVtable *)this)->vslot118(0, 0, 0, 1);

	freeMessageResources();

	delete[] m_placeIcon;
	m_placeIcon = 0;

	clearFloatingText();
	clearWorldAnimations();
	((Gen_0043FBB0 *)this)->bfmeClear();
	InGameUI::resetIdleWorker();
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

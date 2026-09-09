// ??0BfmeAptScreenSaveLoad@@QAE@PAX@Z
// partial score=0.35 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenSaveLoad constructor, retail 0x0056E980, 1719 bytes. The
// factory (createAptScreenSaveLoad, retail 0x00104DC0) already lives in
// Code/GameEngine/Source/GameClient/AptScreenFactories.cpp with a stub
// BfmeAptScreenSaveLoad class (char m_unmodelled[0x288]); the real landing
// spot for this body is THAT file, extending its existing shared classes
// (AsciiString/FunctorBinding/_bfme_AptGameWindow/BfmeAptFunctorMarker/
// WindowManager/g_theWindowManager - all already there for QuitMenu/
// DisconnectScreen/SpellStore/CampaignReview). This stash re-declares just
// enough of them to stand alone for review; a landing attempt should ADD to
// AptScreenFactories.cpp rather than duplicate these types in a second TU.
//
// What is PROVEN here (compiles; the EH prologue before "sub esp,0x50"
// matches byte for byte; every string/address below was read directly off
// the retail image or an existing reverse/symbols.csv pin, not guessed):
//
//  - Same multiple-inheritance shape as the other four AptScreenFactories.cpp
//    ctors: primary vtable at +0, secondary (registry) vtable at +0x218
//    (BfmeAptScreenSaveLoadVftable / ...SecondaryVftable - both still need
//    data pins to the real 0x110a684/0x110a680 arrays, same as the others).
//  - Singleton guard is g_bfmeReadyAG (0x012F4B44), ALREADY PINNED
//    (reverse/symbols.csv, "pin"). No new pin needed for the guard.
//  - Member layout, derived from the exact zero-store offsets/widths at
//    RVA +0x0034-+0x0097 and confirmed by 0x218(base)+0x70=0x288(object
//    size, matches AptScreenFactories.cpp's factory comment):
//      +0x258 int, +0x25c int, +0x260 bool (NOT zeroed here - set later,
//      unrecovered), +0x264/+0x268/+0x26c/+0x270/+0x274 int, +0x278 bool,
//      +0x27c int, +0x280 bool (also touched later, unrecovered), +0x284
//      pointer. Declaring them as int/int/bool/int*5/bool/int/bool/pointer
//      in that order reproduces every offset via natural alignment with NO
//      manual padding - verified against the model in
//      Code/GameEngine/Source/Common/Bfme5BasedListCtor.cpp.
//  - +0x284 is a list<T>::list()-style sentinel: allocate(0x44), then
//    node->next=node; node->prev=node (matches the established idiom in
//    Bfme5BasedListCtor.cpp / BfmeTreeSingletonYN.cpp). The allocator call
//    must go through bfmeAllocNode (plain __cdecl, already pinned at
//    0x0082E540) and NOT through _STL::__new_alloc::allocate from the
//    vendored <vector>/<list> headers this TU already includes for other
//    members - the vendored one compiles to an indirect (ff 15, dllimport)
//    call; retail's is a direct e8 call to the same address, and only
//    bfmeAllocNode reproduces that.
//  - The eleven fscommand registrations (RVA +0x00b2 to +0x049c) are
//    TODAY'S LEVER applied cleanly: one shared holder type
//    (Rva0056D9B0FunctorHolder, ctor already pinned at 0x0096D9B0 -
//    ??0Rva0056D9B0FunctorHolder@@QAE@UFunctorBinding@@@Z,0x0096D9B0) with
//    a REAL (non-inline) primary ctor, an INLINE throw() copy ctor, and a
//    declared-undefined dtor; each registration builds the holder BY VALUE
//    in the argument area and calls _bfme_AptGameWindow::_bfme_showAptScreen
//    (address 0x000338ED, the SAME retail address DisconnectScreen already
//    uses for its own holder type - one real function, many address-derived
//    C++ names, same as QuitMenu/Disconnect's showAptScreenWithArg sharing
//    0x0000ACFE). Needs ONE NEW pin for THIS holder-type overload's mangled
//    name at that same address (see "new pins needed" below); the ctor pin
//    itself already exists.
//  - The eleven strings, read directly off the retail image at the pushed
//    literal addresses (0x110a7f8 down to 0x110a6c8): OnInitialized,
//    OnClosed, Load, Save, Delete, Back, SelectCampaign, SelectSkirmish,
//    SelectReplay, ConfirmationOk, ConfirmationCancel - all prefixed
//    "AptSaveLoad::". This matches the earlier blocked note's list exactly
//    (confirmation, selection, back/delete/save/load, close/init) plus a
//    twelfth "AptSaveLoad::InitGadgets" NOT modelled here (below).
//
// New pins this attempt would need before landing (none added to
// reverse/symbols.csv yet - left for the next agent to verify independently
// per AGENTS.md, since a wrong pin still byte-matches and proves nothing):
//   ?_bfme_showAptScreen@_bfme_AptGameWindow@@QAEXABVAsciiString@@VRva0056D9B0FunctorHolder@@@Z,0x000338ED
//   (an overload of the existing pin at the same address for
//   Rva0050F8B0FunctorHolder; address reuse is the established pattern here)
//   BfmeAptScreenSaveLoadVftable   -> data pin at 0x0110A684
//   BfmeAptScreenSaveLoadSecondaryVftable -> data pin at 0x0110A680
//
// What is NOT modelled (retail RVA +0x049c to the end, ~520 of 1719 bytes -
// this is why compiled size stops at 1198/1719 and even the matched-looking
// prefix above drifts once the missing locals change the compiler's frame
// size/register allocation - a partial implementation of a mid-sized /O2
// function generally can't byte-match its own prefix either, since frame
// size and register choice are whole-function decisions):
//
//  - A twelfth fscommand, "AptSaveLoad::InitGadgets", registered through
//    _bfme_setAptScreenRef (like DisconnectScreen's InitGadgets) but with
//    its wrapper built MANUALLY inline (operator new @0xc81f30, vtable
//    0x110a570, refcount fields set by hand) rather than through a pinned
//    Holder ctor - i.e. the OLDER forceinline-everything pattern from the
//    reverse/attempts/0x00557c00.cpp (BfmeOnlineProfileScreen) attempt, not
//    today's three-part recipe. Its NAME is not a literal: it's looked up
//    via `movsx edx, ax` after `call 0x443cbb` (unidentified - a language/
//    locale query?) indexing a table at 0x012B7E60 (4 bytes/entry, close
//    to but distinct from the fixed pointer at 0x012B7E30 QuitMenu's ctor
//    reads directly for its own "hasFocus" fscommand name).
//  - Immediately before that, an obfuscated-value encode: a real call to
//    Rva0056DEC0(0, 0) (BigObfHookWrappers.cpp family - see
//    Code/GameEngine/Source/Common/ObfuscatedValueOperators.cpp for the
//    pattern), whose result is compared against sentinel 0x993ba311 (NOT
//    the 0xA590217B sentinel that file's three recovered wrapper types use -
//    a fourth, unrecovered instance of the same family, same shared hook
//    slot g_Slot012BF440 at 0x012BF440).
//  - Two TheBfmeGameLogic (0x012F0898, already named via an existing pin)
//    calls, thunks 0x00022c96 (0 args, returns bool in AL, stored to
//    +0x260) and 0x00006f50 (1 bool arg); a third call through
//    g_theWindowManager (0x012F19E8, already named) reads its own private
//    m_bfmePendingBackgroundKind member (+0x1b8, already modelled in
//    AptScreenFactories.cpp's WindowManager class) and conditionally calls
//    thunk 0x00009494. None of these three callees have recovered names.
//
// Do not re-derive the header/registration/member-layout work above; start
// the next attempt from the unmodelled RVA +0x049c tail.

typedef int Int;

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)( void );

struct FunctorBinding
{
	FunctorBinding( FunctorMethod method, FunctorTarget *target )
		: m_target( target ), m_method( method ) {}

	FunctorTarget *m_target;
	unsigned int m_unmodelled;
	FunctorMethod m_method;
};

// SaveLoad.apt registration holder: retail 0x0096D9B0, address-derived name;
// already pinned (??0Rva0056D9B0FunctorHolder@@QAE@UFunctorBinding@@@Z).
// Today's three-part recipe: real ctor, inline throw() copy ctor, declared-
// undefined dtor.
class Rva0056D9B0FunctorHolder
{
public:
	explicit Rva0056D9B0FunctorHolder( FunctorBinding binding );
	Rva0056D9B0FunctorHolder( const Rva0056D9B0FunctorHolder &other ) throw()
		: m_ptr( other.m_ptr ) {}
	~Rva0056D9B0FunctorHolder();

private:
	void *m_ptr;
};

// Rva0050F8B0FunctorHolder is the type DisconnectScreen's own
// _bfme_showAptScreen overload already uses at this same registry address
// (0x000338ED) - kept here only so the "one address, two holder-type
// overloads" shape is visible without opening AptScreenFactories.cpp.
class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class BfmeAptFunctorMarker {};

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( void *context );
	virtual ~_bfme_AptGameWindow();
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
	void _bfme_showAptScreen( const AsciiString &name,
		Rva0056D9B0FunctorHolder callback );

private:
	char m_unmodelled[ 0x254 ];
};

extern void *g_bfmeReadyAG;   // 0x012F4B44, already pinned

// list<T>::list() sentinel idiom - see Bfme5BasedListCtor.cpp. bfmeAllocNode
// is the already-pinned plain-__cdecl alias for retail 0x0082E540 that
// compiles to a direct call, unlike the vendored (dllimport) __new_alloc.
void *bfmeAllocNode( unsigned int bytes );

struct BfmeSaveLoadSlotNode
{
	BfmeSaveLoadSlotNode *m_next;			// +0x00
	BfmeSaveLoadSlotNode *m_prev;			// +0x04
	char m_unmodelledValue[ 0x44 - 8 ];		// +0x08, unrecovered slot record
};

extern const void *BfmeAptScreenSaveLoadVftable[];
extern const void *BfmeAptScreenSaveLoadSecondaryVftable[];

class __declspec(novtable) __multiple_inheritance BfmeAptScreenSaveLoad
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenSaveLoad( void *context );

	void _bfme_onInitialized();
	void _bfme_onClosed();
	void _bfme_onLoad();
	void _bfme_onSave();
	void _bfme_onDelete();
	void _bfme_onBack();
	void _bfme_onSelectCampaign();
	void _bfme_onSelectSkirmish();
	void _bfme_onSelectReplay();
	void _bfme_onConfirmationOk();
	void _bfme_onConfirmationCancel();

private:
	int m_field258;
	int m_field25C;
	bool m_field260;
	int m_field264;
	int m_field268;
	int m_field26C;
	int m_field270;
	int m_field274;
	bool m_field278;
	int m_field27C;
	bool m_field280;
	BfmeSaveLoadSlotNode *m_pSlotListHead;
};

BfmeAptScreenSaveLoad::BfmeAptScreenSaveLoad( void *context )
	: _bfme_AptGameWindow( context )
{
	*(const void ***)( (char *)this ) = BfmeAptScreenSaveLoadVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenSaveLoadSecondaryVftable;
	m_field258 = 0;
	m_field25C = 0;
	m_field264 = 0;
	m_field268 = 0;
	m_field26C = 0;
	m_field270 = 0;
	m_field274 = 0;
	m_field278 = false;
	m_field27C = 0;
	m_field280 = false;

	m_pSlotListHead = 0;
	BfmeSaveLoadSlotNode *node = (BfmeSaveLoadSlotNode *)
		bfmeAllocNode( sizeof( BfmeSaveLoadSlotNode ) );
	node->m_next = node;
	node->m_prev = node;
	m_pSlotListHead = node;

	if( g_bfmeReadyAG == 0 )
	{
		g_bfmeReadyAG = this;
		_bfme_AptGameWindow *registry =
			(_bfme_AptGameWindow *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onInitialized;
			AsciiString name( "AptSaveLoad::OnInitialized" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onClosed;
			AsciiString name( "AptSaveLoad::OnClosed" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onLoad;
			AsciiString name( "AptSaveLoad::Load" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSave;
			AsciiString name( "AptSaveLoad::Save" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onDelete;
			AsciiString name( "AptSaveLoad::Delete" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onBack;
			AsciiString name( "AptSaveLoad::Back" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectCampaign;
			AsciiString name( "AptSaveLoad::SelectCampaign" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectSkirmish;
			AsciiString name( "AptSaveLoad::SelectSkirmish" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectReplay;
			AsciiString name( "AptSaveLoad::SelectReplay" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onConfirmationOk;
			AsciiString name( "AptSaveLoad::ConfirmationOk" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onConfirmationCancel;
			AsciiString name( "AptSaveLoad::ConfirmationCancel" );
			registry->_bfme_showAptScreen( name,
				Rva0056D9B0FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		// PARTIAL: retail continues here - see the header comment above.
	}
}

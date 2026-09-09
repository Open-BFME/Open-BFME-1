// ??0BfmeAptScreenInGameChat@@QAE@PAX@Z
// partial score=0.87 date=2026-09-09
//
// Land target: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp,
// splice in place of the current BfmeAptScreenInGameChat stub (char
// m_unmodelled[0x2A4]) -- all shared infra (_bfme_AptGameWindow,
// FunctorBinding, BfmeAptFunctorMarker, AsciiString, g_theWindowManager)
// already lives earlier in that file.
//
// Object layout confirmed byte-for-byte (unchanged from the 0.91 prior
// session): m_field258(int)/pad25C(4)/m_field260/264/268(int)/pad26C(4)/
// InGameChatSlot m_firstControl@0x270/InGameChatSlot m_secondControl@0x280/
// 6 bool fields 0x290..0x295/pad(2)/m_field298/29C/2A0(int) = 0x2A4 total.
// New pins needed (verified against retail this session; re-derive from
// `python3 tools/dis_retail.py 0x005160E0 987` if this drifts):
//   ?BfmeAptScreenInGameChatVftable@@3PAPBXA          0x01105384
//   ?BfmeAptScreenInGameChatSecondaryVftable@@3PAPBXA 0x01105380
//   ??0InGameChatRefHolder@@QAE@UFunctorBinding@@@Z   0x00026E45
//   ??0InGameChatShowHolder@@QAE@UFunctorBinding@@@Z  0x0000F84E
//   ??0InGameChatArgHolder@@QAE@UFunctorBinding@@@Z   0x00039D38
//   ?_bfme_setAptScreenRef@@YAXABVAsciiString@@VInGameChatRefHolder@@@Z 0x0003DF14 (shared ILT alias)
//   ?showAptScreen@InGameChatRegistry@@QAEXABVAsciiString@@VInGameChatShowHolder@@@Z 0x000338ED (shared ILT alias)
//   ?showAptScreenWithArg@InGameChatRegistry@@QAEXABVAsciiString@@PAXVInGameChatArgHolder@@@Z 0x0000ACFE (shared ILT alias)
//   ?bfmeBaseTC@InGameChatSlot@@QAEXXZ 0x00021FFD (same target as the
//     already-landed BfmeThingTC::bfmeBaseTC in BfmeThreeHundredFortyTwo.cpp
//     -- reuse the address, new name, since THIS class also declares a dtor
//     the other one doesn't)
// Already existing, reused verbatim, do not rename:
//   ?bfmeBaseTC@BfmeThingTC@@QAEXXZ 0x00021FFD (do NOT reuse the class name
//     BfmeThingTC here -- see below, this needs a dtor and that landed one
//     proves a plain non-destructible model at the same address)
//   extern "C" const void *_bfmeVftTC[]; (control vftable)
//   ?g_Rva005127A0InGameChat@@3PAVRva005127A0InGameChat@@A 0x012F4988 (singleton)
//   _bfme_AptGameWindow::_bfme_showAptScreen (0x000338ED) /
//   _bfme_showAptScreenWithArg (0x0000ACFE) / _bfme_setAptScreenRef (0x0003DF14)
//
// THIS SESSION'S FINDING -- the destructor identity, and four dead ends
// that narrow the search for whoever picks this up next:
//
//   The state1/state2 unwind funclets (`add ecx,0x270`/`0x280; jmp <dtor>`)
//   resolve, after chasing THREE layers of incremental-link ILT (0xd5e9 ->
//   0x5111e0 -> 0x4598f), to an address that a PRIOR session had ALREADY
//   correctly identified and pinned:
//     ??1InGameChatSlot@@QAE@XZ,0x0004598F,"ILT of the 0x10-byte InGameChat
//     slot destructor used at this+0x270 and +0x280"
//   -- i.e. the two control sub-objects DO need a real (non-virtual --
//   "QAE@XZ", not "UAE@XZ") destructor in THIS class, even though the
//   already-landed BfmeThingTC in BfmeThreeHundredFortyTwo.cpp (same vft/
//   gap/what layout, same bfmeBaseTC() target 0x00021FFD, byte-verified)
//   has NO destructor at all -- the two must be modelled as DIFFERENT C++
//   classes in this TU (InGameChatSlot here, not BfmeThingTC) even though
//   they're binary-identical, because ONE has a destructor pin and the
//   other doesn't. Renamed the class to InGameChatSlot for that reason and
//   declared `~InGameChatSlot();` (undefined, external, pinned).
//
//   That alone was NOT enough to reproduce retail's unwind states, and
//   four constructions of "how the object becomes alive" were tried this
//   session, disassembling the compiled .obj with capstone each time
//   (objdump on this macOS host mis-decodes right after unresolved
//   relocations -- read the .obj symbol bytes via build.read_object_symbol_bytes
//   and feed them straight to capstone instead, as this session did):
//     1. raw buffer + plain `first->bfmeBaseTC()` call (no ctor at all,
//        the ORIGINAL 0.91 stash's shape) + declaring `~InGameChatSlot()`
//        on the class: compiled size UNCHANGED at 910B, zero new EH state
//        instructions anywhere -- a plain method call on a reinterpreted
//        raw buffer does not make MSVC think an object's lifetime began.
//     2. real typed members (`InGameChatSlot m_firstControl;` instead of
//        `char m_firstControl[0x10]`), keeping the plain bfmeBaseTC() call:
//        910B -> 920B, and EH machinery DOES appear, but both controls'
//        state is set to its FINAL value (2) in ONE instruction immediately
//        after the base-class ctor call, before ANY field zeroing -- because
//        real members are ALWAYS constructed (via their implicit default
//        ctor, even a no-op one) before the enclosing constructor BODY
//        starts, so both controls become "alive" simultaneously at the top
//        instead of incrementally (0->1 after the first bfmeBaseTC() call,
//        1->2 after the second, which is retail's actual shape -- confirmed
//        by ehmap: state1's funclet destroys ONLY the first control, and
//        state2's chains to state1, meaning retail keeps them as two
//        SEPARATE incremental risk windows, not one combined one). This is
//        the best byte count reached this session (920B) and is what's
//        left in this stash, but the SHAPE is still wrong for the reason
//        above -- it is progress, not a fix.
//     3. raw buffer + EXPLICIT non-placement ctor-call syntax on a
//        TRIVIAL inline-empty constructor (`InGameChatSlot() {}`, called
//        via `first->InGameChatSlot::InGameChatSlot();`, mirroring the
//        trick that worked for OptionPreferences at 0x00563370): compiled
//        back down to 910B, IDENTICAL to variant 1 -- the compiler proves
//        the empty ctor is trivial and elides the whole EH-tracked-lifetime
//        marking, explicit-call syntax or not.
//     4. raw buffer + explicit ctor-call syntax on an UNDEFINED/external
//        constructor pinned to the SAME address as bfmeBaseTC (i.e.
//        treating retail's single `call 0x21ffd` as the object's real
//        constructor rather than a separately-named init method, removing
//        the redundant bfmeBaseTC() call entirely): still 910B, and the
//        disassembled .obj confirms the call survives (not eliminated) but
//        STILL carries no EH state-set instruction around it. So even an
//        opaque, unconstant-foldable external constructor call, reached via
//        the ctor-call trick, does NOT reliably get lifetime tracking here
//        -- meaning OptionPreferences' 0x00563370 win (state1 tracking a
//        raw-buffer explicit ctor-call) needs re-verification too; this
//        session did not have time to re-check that one after this finding.
//
//   Net effect: none of the four single-mechanism attempts reproduce
//   retail's INCREMENTAL two-state shape. The likely fix is some
//   combination not tried yet -- e.g. real typed members but with a
//   user-provided (non-implicit) default constructor on InGameChatSlot
//   that does something non-trivial-looking (not just `{}`) so the
//   compiler can't prove simultaneous construction is safe to fold into
//   one state transition; or accept variant 2's shape as what retail
//   actually reduces to under some other flag and instead chase the
//   remaining 67 bytes (987-920) as a REGISTER/CONSTANT-hoisting
//   difference in the registration blocks the way 0x00563370 shows,
//   which is a much shorter remaining gap than either prior session left.
//
// STILL UNRESOLVED at t=45 (this session, after the 0.91 prior session):
//  compiled body is 920 bytes vs retail's 987 (67 short, improved from the
//  0.91 stash's 77). The ebp/ebx register-color swap documented in the
//  prior stash is still present and, per AGENTS.md, likely unreachable.

extern const void *BfmeAptScreenInGameChatVftable[];
extern const void *BfmeAptScreenInGameChatSecondaryVftable[];
extern "C" const void *_bfmeVftTC[];

class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;   // 0x012F4988

class InGameChatSlot
{
public:
	void bfmeBaseTC();
	~InGameChatSlot();

	void *m_bfmeVft;
	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
};

class InGameChatRefHolder
{
public:
	InGameChatRefHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class InGameChatShowHolder
{
public:
	InGameChatShowHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

class InGameChatArgHolder
{
public:
	InGameChatArgHolder( FunctorBinding binding );

private:
	void *m_ptr;
};

void _bfme_setAptScreenRef( const AsciiString &name, InGameChatRefHolder callback );

class InGameChatRegistry
{
public:
	void showAptScreen( const AsciiString &name, InGameChatShowHolder callback );
	void showAptScreenWithArg( const AsciiString &name, void *argument,
		InGameChatArgHolder callback );
};

// InGameChat.apt, retail 0x001050C0, object 0x2A4 bytes.
class __declspec(novtable) __multiple_inheritance BfmeAptScreenInGameChat
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenInGameChat( void *context );
	void _bfme_initGadgets();
	void _bfme_onInitialized();
	void _bfme_onClosed();
	void _bfme_close();
	void _bfme_send();
	void _bfme_onBttnAddFriend();
	void _bfme_onBttnRemoveFriend();

private:
	int m_field258;
	char m_padding25C[ 4 ];
	int m_field260;
	int m_field264;
	int m_field268;
	char m_padding26C[ 4 ];
	InGameChatSlot m_firstControl;
	InGameChatSlot m_secondControl;
	bool m_field290;
	bool m_field291;
	bool m_field292;
	bool m_field293;
	bool m_field294;
	bool m_field295;
	char m_padding296[ 2 ];
	int m_field298;
	int m_field29C;
	int m_field2A0;
};

BfmeAptScreenInGameChat::BfmeAptScreenInGameChat( void *context )
	: _bfme_AptGameWindow( context )
{
	InGameChatRegistry *registry =
		(InGameChatRegistry *)( (char *)this + 0x218 );

	*(const void ***)( (char *)this ) = BfmeAptScreenInGameChatVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenInGameChatSecondaryVftable;
	m_field258 = 0;
	m_field260 = 0;
	m_field264 = 0;
	m_field268 = 0;
	InGameChatSlot *first = &m_firstControl;
	first->bfmeBaseTC();
	first->m_bfmeVft = (void *)_bfmeVftTC;
	first->m_bfmeWhat = (void *)4;
	InGameChatSlot *second = &m_secondControl;
	second->bfmeBaseTC();
	second->m_bfmeVft = (void *)_bfmeVftTC;
	second->m_bfmeWhat = (void *)4;
	m_field290 = true;
	m_field291 = false;
	m_field292 = true;
	m_field293 = false;
	m_field294 = true;
	m_field295 = false;
	m_field298 = 0;
	m_field29C = 0;
	m_field2A0 = 0;

	if( g_Rva005127A0InGameChat == 0 )
	{
		g_Rva005127A0InGameChat = (Rva005127A0InGameChat *)this;

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_initGadgets;
			AsciiString name( "AptInGameChat::InitGadgets" );
			_bfme_setAptScreenRef( name,
				InGameChatRefHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_onInitialized;
			AsciiString name( "AptInGameChat::OnInitialized" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_onClosed;
			AsciiString name( "AptInGameChat::OnClosed" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_close;
			AsciiString name( "AptInGameChat::Close" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_send;
			AsciiString name( "AptInGameChat::Send" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_onBttnAddFriend;
			AsciiString name( "AptInGameChat::OnBttnAddFriend" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_onBttnRemoveFriend;
			AsciiString name( "AptInGameChat::OnBttnRemoveFriend" );
			registry->showAptScreen( name,
				InGameChatShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenInGameChat::_bfme_onBttnRemoveFriend;
			AsciiString name( "ScreenType" );
			registry->showAptScreenWithArg( name, (void *)0,
				InGameChatArgHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}
	}
}

// ?createAptScreenInGameChat@@YGPAXPAX@Z
void * __stdcall createAptScreenInGameChat( void *context )
{
	return new BfmeAptScreenInGameChat( context );
}

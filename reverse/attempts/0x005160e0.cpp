// ??0BfmeAptScreenInGameChat@@QAE@PAX@Z
// partial score=0.97 date=2026-09-09
//
// Land target: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp,
// splice in place of the current BfmeAptScreenInGameChat stub (char
// m_unmodelled[0x2A4]) -- all shared infra (_bfme_AptGameWindow,
// FunctorBinding, BfmeAptFunctorMarker, AsciiString, g_theWindowManager)
// already lives earlier in that file.
//
// Object layout confirmed byte-for-byte (unchanged since the 0.91 session):
// m_field258(int)/pad25C(4)/m_field260/264/268(int)/pad26C(4)/
// InGameChatSlot m_firstControl@0x270/InGameChatSlot m_secondControl@0x280/
// 6 bool fields 0x290..0x295/pad(2)/m_field298/29C/2A0(int) = 0x2A4 total.
// New pins needed (unchanged from the 0.97 session; re-derive from
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
//   ??1InGameChatSlot@@QAE@XZ,0x0004598F (already pinned by a prior session --
//     ILT of the 0x10-byte InGameChat slot destructor used at this+0x270/+0x280)
//
// THIS SESSION (t=40, sonnet) -- tried the fifth variant the 0.97 session
// proposed but ran out of time for: give InGameChatSlot a REAL, NON-TRIVIAL,
// user-provided default constructor that itself performs the work retail's
// bfmeBaseTC() call site does:
//
//   class InGameChatSlot
//   {
//   public:
//       InGameChatSlot()
//       {
//           bfmeBaseTC();
//           m_bfmeVft = (void *)_bfmeVftTC;
//           m_bfmeWhat = (void *)4;
//       }
//       ~InGameChatSlot();          // declared only, pinned to 0x0004598F
//       void bfmeBaseTC();
//       void *m_bfmeVft;
//       unsigned char m_bfmeGap[8];
//       void *m_bfmeWhat;
//   };
//
// with m_firstControl/m_secondControl kept as REAL typed members (not a raw
// buffer -- confirmed again this session that a raw buffer + explicit
// ctor-call syntax, variants 3/4 from the 0.87 stash, generates NO EH state
// tracking at all regardless of how non-trivial the called ctor looks; only
// a genuine typed member triggers the compiler's per-sub-object unwind
// bookkeeping here).
//
// RESULT: this DOES fix the shape bug the 0.97 stash flagged -- the compiled
// object now sets the EH state marker at [esp+0x30] INCREMENTALLY, exactly
// like retail: `mov dword ptr [esp+0x30], ebp` (ebp=0) immediately before the
// FIRST bfmeBaseTC() call, then `mov byte ptr [esp+0x30], 1` immediately
// before the SECOND call -- confirmed via a raw (unresolved-relocation)
// capstone disassembly of the compiled .obj bytes so the 0/1 immediates are
// not an artifact of the target-byte-copy the DIR32-relocation comparison
// does (build.compile_function's resolve() copies retail's bytes over any
// DIR32 relocation site in the "resolved" view explain_mismatch prints, so
// only the RAW pre-resolve object bytes prove this -- read them with
// build.read_object_symbol_bytes directly, not through explain_mismatch).
// This is a genuine, verified improvement over the prior 0.97 session's
// shape (which jumped straight to state=2 in one instruction).
//
// BUT total compiled size is STILL 984B vs retail's 987 (3 short) -- the
// SAME number the 0.97 (wrong-shape) session reached, because a NEW, more
// specific residue appears in its place: MSVC recognizes that both inlined
// instantiations of InGameChatSlot's constructor write the SAME literal
// constant (4) to m_bfmeWhat, and hoists it into a shared register (ebx) it
// reuses across both stores instead of encoding two immediate stores:
//   mine:   bb 04 00 00 00       mov ebx, 4        (5B, once)
//           89 5f 0c             mov [edi+0xc], ebx (3B, first control)
//           ...
//           89 5f 0c             mov [edi+0xc], ebx (3B, second control)
//                                 = 11B total for both stores
//   retail: c7 43 0c 04 00 00 00 mov dword ptr [ebx+0xc], 4  (7B, first)
//           c7 43 0c 04 00 00 00 mov dword ptr [ebx+0xc], 4  (7B, second)
//                                 = 14B total, no register ever loaded
// 14 - 11 = exactly the 3-byte gap. Retail's two `mov [x+0xc], 4` stores are
// literal immediates both times; it never materializes the constant in a
// register at all. This is the AGENTS.md "small-constant register-fed vs
// immediate-literal" class of residue ("that difference is unreachable, log
// it") -- confirmed unreachable THIS session via three targeted attempts,
// all reverted, none left in this stash:
//   1. `void * volatile m_bfmeWhat;` on just that one member -- no byte
//      change at all (984B, identical diff position). Volatile pins STORES,
//      not the compiler's choice of register-vs-immediate for the value
//      being stored (see docs/lessons.md "Volatile pins stores, not
//      constants").
//   2. Moving the vft/what assignment OUT of InGameChatSlot's constructor
//      into BfmeAptScreenInGameChat's body (after both members are already
//      implicitly constructed, so both bfmeBaseTC() calls now run back to
//      back before ANY vft/what store) -- this does NOT reproduce retail's
//      per-member interleaving (call1/vft1/what1/call2/vft2/what2) and,
//      worse, the compiler no longer hoists the constant at all once the
//      two stores are separated from the (still-inlined) member ctors,
//      regressing to 994B (7B OVER retail, not under) -- confirms the
//      current all-inside-the-ctor placement is the better structure to
//      keep even though it doesn't close the gap.
//   3. `#pragma optimize( "g", off )` wrapped around just
//      BfmeAptScreenInGameChat::BfmeAptScreenInGameChat (matched by
//      `#pragma optimize( "", on )` after) to try to suppress just the CSE
//      that drives the hoist -- MSVC 13.10 treats "g" off as also disabling
//      inlining for that scope: InGameChatSlot's ctor and FunctorBinding's
//      ctor both stopped inlining entirely, the function ballooned to
//      1592B and left two unresolved REL32 calls
//      (??0InGameChatSlot@@QAE@XZ, ??0FunctorBinding@@...). Far worse; not
//      a viable lever here.
//
// Net: this session traded one known-unreachable-class residue (wrong EH
// state SHAPE, from the 0.97/variant-2 stash) for a different
// known-unreachable-class residue (register-hoisted constant, matching the
// AGENTS.md-documented pattern precisely) at the SAME total byte count
// (984/987). The current source below is a strictly more correct MODEL of
// retail's construction order (real incremental per-member EH lifetime,
// matching ehmap's two separate funclets) even though it does not close the
// remaining 3 bytes. Recommend whoever picks this up next does NOT re-try
// the volatile/split-body/pragma-optimize levers (all confirmed dead ends
// this session) and instead either (a) accepts the 3B gap as unreachable
// register-choice residue per AGENTS.md and moves this to `blocked`/closes
// the family, or (b) tries feeding the constant through two DIFFERENT
// looking but value-4 expressions that might defeat MSVC's CSE pass
// specifically (untried: e.g. computing one of the two via a volatile
// intermediate int, or via inline asm for just that one store) -- low
// confidence this changes a backend CSE decision, but not yet ruled out.
//
extern const void *BfmeAptScreenInGameChatVftable[];
extern const void *BfmeAptScreenInGameChatSecondaryVftable[];
extern "C" const void *_bfmeVftTC[];

class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;   // 0x012F4988

class InGameChatSlot
{
public:
	InGameChatSlot()
	{
		bfmeBaseTC();
		m_bfmeVft = (void *)_bfmeVftTC;
		m_bfmeWhat = (void *)4;
	}
	~InGameChatSlot();

	void bfmeBaseTC();

	void *m_bfmeVft;
	unsigned char m_bfmeGap[ 8 ];
	void *m_bfmeWhat;
};

class InGameChatRefHolder
{
public:
	InGameChatRefHolder( FunctorBinding binding );
	InGameChatRefHolder( const InGameChatRefHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
	}
	~InGameChatRefHolder();

private:
	void *m_ptr;
};

class InGameChatShowHolder
{
public:
	InGameChatShowHolder( FunctorBinding binding );
	InGameChatShowHolder( const InGameChatShowHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
	}
	~InGameChatShowHolder();

private:
	void *m_ptr;
};

class InGameChatArgHolder
{
public:
	InGameChatArgHolder( FunctorBinding binding );
	InGameChatArgHolder( const InGameChatArgHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
	}
	~InGameChatArgHolder();

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

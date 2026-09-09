// ??0BfmeAptScreenOptions@@QAE@PAX@Z
// partial score=0.93 date=2026-09-09
//
// Land target: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp.
// Splice in right after createAptScreenDisconnectScreen()'s closing brace
// (before "// SaveLoad.apt"); remove the early stub
// `class BfmeAptScreenOptions { char m_unmodelled[0x310]; };` +
// `createAptScreenOptions` near the top of the file (same pattern the
// landed DisconnectScreen/CampaignReview/SpellStore/QuickMatchMenu bodies
// already follow -- stub removed, real body placed near the shared
// _bfme_AptGameWindow/FunctorBinding/AsciiString/UnicodeString infra it
// needs). Requires the six new symbols.csv pins below (verified compile
// clean this session; drop them again if you park without landing --
// re-derive from `python3 tools/dis_retail.py 0x00563370 1073` if retail
// moves):
//   ?showAptScreen@OptionsRegistry@@QAEXABVAsciiString@@VOptionsShowHolder@@@Z 0x000338ED (shared ILT, same target as DisconnectScreen/CampaignReview/SpellStore/QuitMenu's showAptScreen)
//   ?optionsSetAptScreenRef@@YAXABVAsciiString@@VOptionsInitHolder@@@Z 0x0003DF14 (shared ILT, same target as _bfme_setAptScreenRef/campaignReviewSetAptScreenRef)
//   ??0OptionsShowHolder@@QAE@UFunctorBinding@@@Z 0x00031C41
//   ??0OptionsInitHolder@@QAE@UFunctorBinding@@@Z 0x000323A3
//   ?getUnicodeVersion@OptionsVersionView@@QAE?AVUnicodeString@@XZ 0x00030E63
//   ?g_optionsVersion@@3PAVOptionsVersionView@@A 0x012ED644
//   ?BfmeAptScreenOptionsVftable@@3PAPBXA 0x0110912C
//   ?BfmeAptScreenOptionsSecondaryVftable@@3PAPBXA 0x01109128
//   ?g_optionsScreenLayout@@3PAXA 0x012F4AD4 (SAME address as the existing
//     g_quitMenuLayout pin -- confirmed by dis_retail.py resolving the
//     `cmp dword ptr [0x12f4ad4],ebp` singleton check to that name; add a
//     second name at the same address, do not rename the existing pin)
// Already-existing pins reused, no action needed:
//   ??0OptionPreferences@@QAE@XZ 0x0003713C  (line 3154 in symbols.csv)
//   ??1OptionPreferences@@UAE@XZ 0x00001307  (line 8860 -- note the "U":
//     PUBLIC VIRTUAL destructor, see below)
//
// THIS SESSION'S FINDING (the structural piece the earlier 0.85/940B stash
// was missing -- got it to 973B, still 100B short of 1073, but the EH
// state COUNT now matches retail's 11 states exactly, confirmed via
// build/ehmap.py on both this function and the already-landed sibling
// BfmeAptScreenQuitMenuConstructor.cpp for comparison):
//
//   ??1OptionPreferences@@UAE@XZ is a PUBLIC VIRTUAL destructor (mangling
//   "UAE@XZ", "U" = public+virtual). The class genuinely has a vtable
//   (sizeof 0x10 = 4-byte vfptr + 0xC bytes of data, not 0x10 flat bytes).
//   Because it has a non-trivial destructor, /EHsc gives the constructor
//   call an EH unwind state -- that's retail's state 1 (map: state1->0,
//   action funclet = `add ecx,0x260; jmp <OptionPreferences dtor ILT>`,
//   ecx being the outer `this` saved at [ebp-0x20]). ALL SIX registration
//   blocks' states (2..7, one per `AsciiString name(...)` local) chain
//   back to state 1, not to state 0 -- i.e. retail keeps OptionPreferences
//   "open" (needs its own cleanup on unwind) for the whole rest of the
//   constructor body, only closing it (chaining to 0/-1) at the very end.
//   The earlier stash declared OptionPreferences with NO destructor at
//   all (`char m_unmodelled[0x10]`, no ctor/dtor pair) -- a trivially
//   destructible type never gets an unwind state regardless of how it's
//   constructed, which is why that version compiled with zero EH state
//   machinery and came in short. Fix: declare `virtual ~OptionPreferences()`
//   (undefined, resolves via the pin above) and shrink the opaque buffer
//   to 0xC so sizeof stays 0x10 with the compiler's own implicit vfptr.
//   Keep constructing it via the SAME explicit non-placement syntax the
//   0.85 stash proved reproduces retail's plain `call` with no null check:
//     ( (OptionPreferences *)m_optionsBuffer )->OptionPreferences::OptionPreferences();
//   (placement `new (buf) OptionPreferences()` still adds a spurious
//   `if(ptr)` check in this TU -- no local placement-new override without
//   colliding with <list>/<vector>'s.)
//
//   Also confirmed via ehmap: retail's tail
//     UnicodeString version = g_optionsVersion->getUnicodeVersion();
//     AsciiString versionName( "APT:VersionNum" );
//     g_theWindowManager->bfme_setAptText( versionName, version );
//   is NOT what retail compiles (that shape only gives 2 more states,
//   8 and 9, total maxState 10). Retail's unwind map has ELEVEN states
//   (0..10); state 10's funclet destroys a UnicodeString (dtor target
//   0x43b304, same as state 8's) at a THIRD, DISTINCT stack slot,
//   reached via the copy constructor ??0?$StringBase@G@@AAE@ABV0@@Z
//   (0xc88400) -- i.e. retail makes an explicit extra copy of `version`
//   before calling bfme_setAptText, even though bfme_setAptText's real
//   parameter is `const UnicodeString&` (no copy should be needed for a
//   plain by-ref pass). Write it explicitly to match:
//     UnicodeString version = g_optionsVersion->getUnicodeVersion();
//     AsciiString versionName( "APT:VersionNum" );
//     UnicodeString versionArg( version );
//     g_theWindowManager->bfme_setAptText( versionName, versionArg );
//   This closed the state-count gap (compiled body now walks states
//   1..9 the same way retail's map shows, confirmed by grepping
//   `mov byte ptr [esp+...], N` sequences in the compiled .obj).
//
//   Also recovered: the earlier stash's four m_fields2XX zero blocks
//   compiled correctly EXCEPT it forgot the memset() fix on m_fields274
//   documented in ITS OWN prior comment (individual `m_fields274[i]=0`
//   assignments merge into the m_fields284 store run and erase the gap
//   at 0x298/0x2A4 that retail leaves uninitialized) -- ans that
//   0x270..0x274 padding dword between the OptionPreferences sub-object
//   and m_fields274 was dropped entirely in a rewrite this session and
//   had to be re-added (`int m_pad270;`). Both are back in this version.
//
// STILL OPEN at t=45 (this session): compiled body is 973B vs retail's
// 1073B (100B short), all eleven EH states now present and in the right
// chain shape, but the registration-block byte count per block still
// runs shorter than retail's -- likely retail keeps TWO live constant
// registers across the six blocks (ebp=0 AND bl=1, reused as the "back to
// state 1" store operand -- `mov byte ptr [state_slot], bl` is 4 bytes
// vs `mov byte ptr [state_slot], 1` at 5 bytes, times ~7 uses) where this
// build's allocator only keeps one (ebx=0), which AGENTS.md says is
// generally not source-controllable register/constant-hoisting residue,
// not a real behavioural gap -- but the 100B total is too large to be
// register choice alone, so there is probably one more source-expressible
// difference in how the six FunctorBinding blocks are built (retail's
// ptr-to-member is assembled via two `mov [addr],imm`+`mov [addr+4],eax`
// stores into a stack FunctorBinding before the OptionsShowHolder call;
// worth re-diffing block-by-block against dis_retail.py once picked back
// up, since relocations make objdump's raw byte view unreliable right
// after each `call` -- read via capstone on the .obj's read symbol bytes
// instead, as this session did).

//
// THIS SESSION (t=45, sonnet): applied the FunctorHolder in-place-argument-
// area recipe from the fleet brief (real value ctor, INLINE throw() copy
// ctor, DECLARED-BUT-UNDEFINED dtor on both OptionsShowHolder and
// OptionsInitHolder -- the value ctor itself stays declaration-only, since
// retail genuinely calls it out-of-line at 0x00031C41/0x000323A3, unlike
// the fully-inlined OnlineProfileScreen family). This alone took the
// compiled body from 973B to 1013B (100B short -> 60B short), confirming
// the assignment's hint that the earlier 0.85/0.90 stashes were missing
// the in-place construction shape, not just register residue.
//
// Spliced into Code/GameEngine/Source/GameClient/AptScreenFactories.cpp
// (stub BfmeAptScreenOptions + createAptScreenOptions near the top removed;
// real class+ctor inserted right after createAptScreenDisconnectScreen()'s
// closing brace, per this stash's own original placement note) to reuse
// the file's existing FunctorTarget/FunctorBinding/_bfme_AptGameWindow/
// BfmeAptFunctorMarker/AsciiString/UnicodeString/WindowManager
// infrastructure -- do NOT redeclare those locally, add to that file.
// All nine new symbols.csv pins listed above this comment block were
// verified free (pin_consistency.py) and added; drop them again if
// parking without landing.
//
// STILL OPEN: compiled 1013B vs retail 1073B (60B short). Two remaining
// symptoms, not yet disentangled:
//   1. Retail keeps the zero-fill constant in EBP (`xor ebp,ebp` at +0x39c,
//      ~35 `mov [esi+N],ebp` stores through the whole body) plus a SEPARATE
//      zero in CL for m_field308 (`mov byte ptr[esi+0x308],cl`, from the
//      xor ecx,ecx used to zero m_fields274). This build's allocator picks
//      EBX for the same role throughout -- looks like the standard
//      unreachable register-choice/argument-shuttle residue (see
//      docs/lessons.md, argument-shuttle-register), do not re-sweep flags
//      or hoist locals for this alone.
//   2. Frame is `sub esp,0x24` here vs retail's `sub esp,0x1c` -- 8 bytes
//      MORE than retail (opposite direction from the 0.85 stash's original
//      940B-vs-1073B gap, which was frame-too-small). This 8-byte excess
//      is a REAL structural difference (not just register choice) and is
//      the more promising lead: something in this build reserves one more
//      stack dword than retail across the whole function. Next session
//      should bisect it by temporarily stripping the six registration
//      blocks one at a time (or reverting just the OptionsInitHolder half,
//      which is only used once) to see which one shifts the frame size,
//      rather than re-deriving the whole body from scratch.
//
extern const void *BfmeAptScreenOptionsVftable[];
extern const void *BfmeAptScreenOptionsSecondaryVftable[];
extern void *g_optionsScreenLayout;   // 0x012F4AD4, same slot as g_quitMenuLayout

class OptionPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();

private:
	char m_unmodelled[ 0xC ];
};

class OptionsVersionView
{
public:
	UnicodeString getUnicodeVersion();
};

extern OptionsVersionView *g_optionsVersion;   // 0x012ED644

class OptionsShowHolder
{
public:
	OptionsShowHolder( FunctorBinding binding );
	OptionsShowHolder( const OptionsShowHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
	}
	~OptionsShowHolder();

private:
	void *m_ptr;
};

class OptionsInitHolder
{
public:
	OptionsInitHolder( FunctorBinding binding );
	OptionsInitHolder( const OptionsInitHolder &other ) throw()
	{
		m_ptr = other.m_ptr;
	}
	~OptionsInitHolder();

private:
	void *m_ptr;
};

class OptionsRegistry
{
public:
	void showAptScreen( const AsciiString &name, OptionsShowHolder callback );
};

void optionsSetAptScreenRef( const AsciiString &name, OptionsInitHolder callback );

// Options.apt, retail 0x00104CC0, object 0x310 bytes.
class __declspec(novtable) __multiple_inheritance BfmeAptScreenOptions
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	BfmeAptScreenOptions( void *context );
	void _bfme_onInitialized();
	void _bfme_save();
	void _bfme_reset();
	void _bfme_cancel();
	void _bfme_refreshNat();
	void _bfme_initGadgets();

private:
	int m_field258;
	int m_field25C;
	char m_optionsBuffer[ 0x10 ];
	int m_pad270;
	int m_fields274[ 4 ];
	int m_fields284[ 5 ];
	int m_fields298;
	int m_fields29C[ 2 ];
	int m_fields2A4;
	int m_fields2A8[ 24 ];
	bool m_field308;
	int m_field30C;
};

BfmeAptScreenOptions::BfmeAptScreenOptions( void *context )
	: _bfme_AptGameWindow( context )
{
	*(const void ***)( (char *)this ) = BfmeAptScreenOptionsVftable;
	*(const void ***)( (char *)this + 0x218 ) =
		BfmeAptScreenOptionsSecondaryVftable;
	m_field258 = 0;
	m_field25C = 0;
	( (OptionPreferences *)m_optionsBuffer )->OptionPreferences::OptionPreferences();
	memset( m_fields274, 0, sizeof( m_fields274 ) );
	m_fields284[ 0 ] = 0;
	m_fields284[ 1 ] = 0;
	m_fields284[ 2 ] = 0;
	m_fields284[ 3 ] = 0;
	m_fields284[ 4 ] = 0;
	m_fields29C[ 0 ] = 0;
	m_fields29C[ 1 ] = 0;
	m_fields2A8[ 0 ] = 0;
	m_fields2A8[ 1 ] = 0;
	m_fields2A8[ 2 ] = 0;
	m_fields2A8[ 3 ] = 0;
	m_fields2A8[ 4 ] = 0;
	m_fields2A8[ 5 ] = 0;
	m_fields2A8[ 6 ] = 0;
	m_fields2A8[ 7 ] = 0;
	m_fields2A8[ 8 ] = 0;
	m_fields2A8[ 9 ] = 0;
	m_fields2A8[ 10 ] = 0;
	m_fields2A8[ 11 ] = 0;
	m_fields2A8[ 12 ] = 0;
	m_fields2A8[ 13 ] = 0;
	m_fields2A8[ 14 ] = 0;
	m_fields2A8[ 15 ] = 0;
	m_fields2A8[ 16 ] = 0;
	m_fields2A8[ 17 ] = 0;
	m_fields2A8[ 18 ] = 0;
	m_fields2A8[ 19 ] = 0;
	m_fields2A8[ 20 ] = 0;
	m_fields2A8[ 21 ] = 0;
	m_fields2A8[ 22 ] = 0;
	m_fields2A8[ 23 ] = 0;
	m_field308 = false;
	m_field30C = -1;

	if( g_optionsScreenLayout == 0 )
	{
		g_optionsScreenLayout = this;
		OptionsRegistry *registry =
			(OptionsRegistry *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_onInitialized;
			AsciiString name( "AptOptions::OnInitialized" );
			registry->showAptScreen( name,
				OptionsShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_save;
			AsciiString name( "AptOptions::Save" );
			registry->showAptScreen( name,
				OptionsShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_reset;
			AsciiString name( "AptOptions::Reset" );
			registry->showAptScreen( name,
				OptionsShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_cancel;
			AsciiString name( "AptOptions::Cancel" );
			registry->showAptScreen( name,
				OptionsShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_refreshNat;
			AsciiString name( "AptOptions::RefreshNat" );
			registry->showAptScreen( name,
				OptionsShowHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenOptions::_bfme_initGadgets;
			AsciiString name( "AptOptions::InitGadgets" );
			optionsSetAptScreenRef( name,
				OptionsInitHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		UnicodeString version = g_optionsVersion->getUnicodeVersion();
		AsciiString versionName( "APT:VersionNum" );
		UnicodeString versionArg( version );
		g_theWindowManager->bfme_setAptText( versionName, versionArg );
	}
}

// ?createAptScreenOptions@@YGPAXPAX@Z
void * __stdcall createAptScreenOptions( void *context )
{
	return new BfmeAptScreenOptions( context );
}

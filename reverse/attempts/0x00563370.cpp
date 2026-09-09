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
// needs). Requires the nine new symbols.csv pins below (verified compile
// clean again this session; drop them again if you park without landing --
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
// PRIOR SESSION'S FINDING (still valid, unchanged): ??1OptionPreferences@@UAE@XZ
// is a PUBLIC VIRTUAL destructor (mangling "UAE@XZ"). The class genuinely
// has a vtable (sizeof 0x10 = 4-byte vfptr + 0xC bytes of data, not 0x10
// flat bytes). Because it has a non-trivial destructor, /EHsc gives the
// constructor call an EH unwind state -- retail's state 1 (map: state1->0,
// funclet `add ecx,0x260; jmp <OptionPreferences dtor ILT>`). ALL SIX
// registration blocks' states (2..7) chain back to state 1, not state 0.
// Declare `virtual ~OptionPreferences()` (undefined, pinned) and shrink the
// opaque buffer to 0xC so sizeof stays 0x10 with the compiler's own
// implicit vfptr. Construct via the explicit non-placement syntax:
//   ( (OptionPreferences *)m_optionsBuffer )->OptionPreferences::OptionPreferences();
// (placement `new` still adds a spurious null check in this TU).
//
// Also confirmed via ehmap (still valid): retail's tail makes THREE distinct
// UnicodeString-shaped stack objects before calling bfme_setAptText (states
// 8, 9, 10 in the unwind map; state 10's funclet destroys a UnicodeString at
// a THIRD, distinct stack slot via the copy ctor ??0?$StringBase@G@@AAE@ABV0@@Z,
// 0xc88400), even though bfme_setAptText's real second parameter is
// `const UnicodeString&` and a plain by-ref pass of the sret result would
// need no extra copy.
//
// THIS SESSION (t=45, sonnet): re-verified the 0.85/0.90/0.93 stashes'
// escalating claims are all still correct (memset fix, m_pad270 gap, the
// virtual-dtor OptionPreferences shape, the FunctorHolder in-place-argument
// recipe on both OptionsShowHolder/OptionsInitHolder) and then chased the
// "extra 8 bytes of frame" lead the 0.93 stash flagged as the more
// promising of its two open symptoms (the other -- retail's ebp/bl vs this
// build's single ebx for the shared zero/one constants across the six
// registration blocks -- is the standard AGENTS.md register-choice residue,
// not re-investigated further, not source-controllable).
//
// FOUND: exactly the shape the fleet brief predicts ("an extra 8 bytes of
// frame usually means a temporary that retail builds in the argument area
// but MSVC gives a named slot"). The prior stash's tail wrote THREE named
// locals for the version text:
//   UnicodeString version = g_optionsVersion->getUnicodeVersion();
//   AsciiString versionName( "APT:VersionNum" );
//   UnicodeString versionArg( version );
//   g_theWindowManager->bfme_setAptText( versionName, versionArg );
// Removing versionArg's NAME -- constructing the copy directly in
// bfme_setAptText's argument list instead of a named local --
//   UnicodeString version = g_optionsVersion->getUnicodeVersion();
//   AsciiString versionName( "APT:VersionNum" );
//   g_theWindowManager->bfme_setAptText( versionName, UnicodeString( version ) );
// moved the compiled frame from `sub esp,0x24` (8 over retail's `sub esp,
// 0x1c`) to `sub esp,0x20` (only 4 over) -- confirmed via a raw
// (unresolved-relocation) capstone disassembly of the compiled .obj, not
// the DIR32-masked explain_mismatch view (build.read_object_symbol_bytes
// directly). The early prologue's ESI-save offset (`mov [esp+0x1c], esi`)
// now matches retail EXACTLY (was off by 4); the incoming-context-arg read
// and the EH state-slot store are both now off by a uniform +4 instead of
// +8. Total compiled size is UNCHANGED at 1013B (the temporary's
// construction still costs 4 bytes of CODE somewhere it didn't need a named
// STACK SLOT for) -- net zero on the headline number, but this is real,
// verified structural progress on the more-promising of the two open leads,
// and narrows "where" the remaining one 4-byte slot lives (allocated but
// unused until later in the body, since the early-prologue offsets now
// match almost everywhere).
//
// Tried and reverted this session -- do NOT retry: also dropping "version"'s
// name (`g_theWindowManager->bfme_setAptText(versionName,
// UnicodeString(g_optionsVersion->getUnicodeVersion()));`, no named local at
// all) collapses the shape too far -- compiled dropped to 976B (function
// SHRANK past retail, meaning this eliminates real EH-state-tracked objects
// ehmap proves retail has, not just a slot). Keep "version" named; only
// "versionArg" collapses safely.
//
// STILL OPEN at t=48 (this session): compiled body is 1013B vs retail's
// 1073B (60B short, unchanged from the prior session's number -- this
// session's fix was structural/frame-alignment, not a byte-count win yet).
// Two threads to pull next, in priority order:
//   1. Find the SECOND extra 4-byte stack slot. The prologue offsets now
//      match retail almost everywhere except a uniform +4, meaning
//      whatever needs it isn't touched until later in the body -- prime
//      suspects: the OptionPreferences buffer/vfptr region, or something
//      in how "callback" (a FunctorMethod pointer-to-member on
//      `__multiple_inheritance FunctorTarget` -- an 8-byte fat
//      pointer-to-member-function under MSVC, not a plain 4-byte pointer)
//      gets staged before each OptionsShowHolder/FunctorBinding
//      construction. Retail's block at +0x15e reads a saved dword from
//      [esp+0x20] mid-block (the callback's second half?) -- worth
//      re-deriving the full first registration block byte-by-byte via
//      dis_retail.py (already partially done this session, see the
//      +0x14a..+0x1a6 range) against this build's compiled .obj (read raw
//      via build.read_object_symbol_bytes, NOT through explain_mismatch's
//      side-by-side view once past the first diff -- that view re-syncs on
//      retail's stream and misrepresents this build's actual bytes, see
//      docs/lessons.md "first diff is not exact").
//   2. Once (1) closes, the remaining gap is very likely the AGENTS.md
//      register-choice residue (retail keeps ebp=0 AND a separate bl=1
//      live across all six registration blocks; this build's allocator
//      picks a single ebx=0 throughout) -- do not chase that with flag
//      sweeps, it is the documented-unreachable class.
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
		g_theWindowManager->bfme_setAptText( versionName, UnicodeString( version ) );
	}
}

// ?createAptScreenOptions@@YGPAXPAX@Z
void * __stdcall createAptScreenOptions( void *context )
{
	return new BfmeAptScreenOptions( context );
}

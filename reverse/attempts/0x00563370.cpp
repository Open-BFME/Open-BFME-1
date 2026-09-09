// ??0BfmeAptScreenOptions@@QAE@PAX@Z
// partial score=0.85 date=2026-09-09
//
// Land target: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp,
// which already has the shared _bfme_AptGameWindow / FunctorBinding /
// AsciiString / UnicodeString / g_theWindowManager infra this needs (see
// the landed BfmeAptScreenDisconnectScreen / CampaignReview / SpellStore
// ctors in that file for the pattern). Only the block below is new; splice
// it in where the current BfmeAptScreenOptions stub (char m_unmodelled[0x310])
// sits, right after `class BfmeAptFunctorMarker {};`.
//
// Fixed vs the earlier 0.89 stash:
//  - the earlier stash's `char m_options[0x14]` implicitly covered the
//    4-byte gap between the OptionPreferences sub-object (0x260..0x270) and
//    m_fields274 (0x274..). This version makes that explicit as
//    m_optionsBuffer[0x10] (leave it 0x14 if you drop the padding member).
//  - OptionPreferences is REALLY constructed via its pinned constructor
//    (??0OptionPreferences@@QAE@XZ, 0x0003713C -- see reverse/symbols.csv),
//    not an invented `.initialize()` method. `new (buf) OptionPreferences();`
//    compiles a spurious `if (ptr) ctor();` null-check in this TU (no local
//    `operator new(size_t,void*)` override available -- one is already
//    declared via <list>/<vector> and re-declaring collides). Use MSVC's
//    explicit-constructor-call syntax instead (already used elsewhere in
//    this file for StringBase's copy ctor):
//        ( (OptionPreferences *)m_optionsBuffer )->OptionPreferences::OptionPreferences();
//    -- this reproduces retail's plain `call` with no check.
//  - the m_fields274[4] quad (0x274..0x284) compiles as 4 direct
//    `mov [esi+off],reg` stores if written as individual assignments;
//    retail computes `lea edx,[esi+0x274]` once and stores through
//    edx+0/4/8/0xc. `memset(m_fields274, 0, sizeof(m_fields274))` (inlined
//    by /O2) reproduces that exact shape -- verified byte-identical for
//    that quad. The remaining fields (m_fields284[5], m_fields2A8[24]) DO
//    match retail's direct-addressing shape when written as individual
//    assignments (no loop -- an explicit `for` costs a stray induction
//    register/stack slot).
//
// STILL UNRESOLVED at t=45 (this session) + t=25 (prior gpt-5 session):
//  Retail holds an explicit zero constant in ebp AND a separate flag/state
//  byte in bl (visible as `mov bl,1` early, reused as the "already
//  constructed" cleanup guard for the six AsciiString callback-name
//  temporaries). This build's register allocator instead uses a single
//  ebx for the zero constant, one fewer live callee-saved value, and the
//  compiled body is 940 bytes vs retail's 1073 (still short after the
//  padding/memset/ctor fixes above -- those recovered ~35 bytes and fixed
//  the shape of the first quad but did not change the register choice or
//  close the remaining size gap). AGENTS.md is explicit that register
//  choice is generally not source-controllable; the size gap likely means
//  the six registration blocks (registry->showAptScreen(name,
//  OptionsShowHolder(FunctorBinding(callback,this))) x5 +
//  optionsSetAptScreenRef(...) x1, then the trailing
//  UnicodeString version = g_optionsVersion->getUnicodeVersion();
//  AsciiString versionName("APT:VersionNum");
//  g_theWindowManager->bfme_setAptText(versionName, version);
//  tail) still don't reproduce retail's per-block EH state-tag byte
//  sequence (2,3,4,5,6,7,8,9,0xa seen in the retail disassembly at
//  esp+0x48/esp+0x38/esp+0x34) the way BfmeAptScreenDisconnectScreen's six
//  blocks do; that tag sequence is worth re-deriving call-by-call against
//  `python3 tools/dis_retail.py 0x00563370 1073` before touching registers
//  again. New symbols.csv pins this session verified compile cleanly
//  (dropped on park, see below) --
//    ?BfmeAptScreenOptionsVftable@@3PAPBXA          0x0110912C
//    ?BfmeAptScreenOptionsSecondaryVftable@@3PAPBXA 0x01109128
//    ?g_optionsScreenLayout@@3PAXA                  0x012F4AD4 (alias of g_quitMenuLayout)
//    ?g_optionsVersion@@3PAVOptionsVersionView@@A   0x012ED644
//    ??0OptionsShowHolder@@QAE@UFunctorBinding@@@Z  0x00031C41
//    ??0OptionsInitHolder@@QAE@UFunctorBinding@@@Z  0x000323A3
//    ?showAptScreen@OptionsRegistry@@QAEXABVAsciiString@@VOptionsShowHolder@@@Z 0x000338ED (shared ILT, same as CampaignReviewRegistry/SpellStoreRegistry)
//    ?optionsSetAptScreenRef@@YAXABVAsciiString@@VOptionsInitHolder@@@Z 0x0003DF14 (shared ILT, same as _bfme_setAptScreenRef/campaignReviewSetAptScreenRef)
//    ?getUnicodeVersion@OptionsVersionView@@QAE?AVUnicodeString@@XZ 0x00030E63
//  all re-derived cheaply from `python3 tools/dis_retail.py 0x00563370 1073`
//  (each unresolved call target's raw REL32) -- re-add them fresh rather
//  than trusting this comment's hex if retail moves.

extern const void *BfmeAptScreenOptionsVftable[];
extern const void *BfmeAptScreenOptionsSecondaryVftable[];
extern void *g_optionsScreenLayout;   // 0x012F4AD4, same slot as g_quitMenuLayout

class OptionPreferences
{
public:
	OptionPreferences();

private:
	char m_unmodelled[ 0x10 ];
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

private:
	void *m_ptr;
};

class OptionsInitHolder
{
public:
	OptionsInitHolder( FunctorBinding binding );

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
	char m_padding270[ 4 ];
	int m_fields274[ 4 ];
	int m_fields284[ 5 ];
	char m_padding298[ 4 ];
	int m_fields29C[ 2 ];
	char m_padding2A4[ 4 ];
	int m_fields2A8[ 24 ];
	bool m_field308;
	char m_padding309[ 3 ];
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
		g_theWindowManager->bfme_setAptText( versionName, version );
	}
}

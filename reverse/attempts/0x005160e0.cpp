// ??0BfmeAptScreenInGameChat@@QAE@PAX@Z
// partial score=0.85 date=2026-09-09
//
// Land target: Code/GameEngine/Source/GameClient/AptScreenFactories.cpp,
// splice in place of the current BfmeAptScreenInGameChat stub (char
// m_unmodelled[0x2A4]) -- all shared infra (_bfme_AptGameWindow,
// FunctorBinding, BfmeAptFunctorMarker, AsciiString, g_theWindowManager)
// already lives earlier in that file (see the landed DisconnectScreen /
// CampaignReview / SpellStore ctors for the established pattern).
//
// Verified against retail this session (python3 tools/dis_retail.py
// 0x005160E0 987):
//  - object layout confirmed byte-for-byte: m_field258(int)/pad25C(4)/
//    m_field260/264/268(int)/pad26C(4)/BfmeThingTC m_firstControl@0x270/
//    BfmeThingTC m_secondControl@0x280/6 bool fields 0x290..0x295/pad(2)/
//    m_field298/29C/2A0(int) = 0x2A4 total.
//  - BfmeThingTC::bfmeBaseTC is ALREADY pinned (?bfmeBaseTC@BfmeThingTC@@QAEXXZ,
//    0x00021FFD) and its vftable is the EXISTING extern "C" pin `_bfmeVftTC`
//    (0x00D051EC) -- do not invent a new "BfmeAptScreenInGameChatControlVftable"
//    name, reuse `extern "C" const void *_bfmeVftTC[];`.
//  - the singleton global at 0x012F4988 is ALSO already pinned as
//    `?g_Rva005127A0InGameChat@@3PAVRva005127A0InGameChat@@A` (an
//    address-derived name from an unrelated forwarder at 0x005127A0) --
//    reuse it verbatim (forward-declare `class Rva005127A0InGameChat;`)
//    rather than inventing g_inGameChatScreen; a duplicate-name pin at the
//    same address was rejected as redundant when this session tried it.
//  - retail calls the SAME free function `_bfme_setAptScreenRef` (already
//    pinned at 0x0003DF14 for other screens) for the InitGadgets
//    registration, and the SAME `_bfme_AptGameWindow::_bfme_showAptScreen`
//    (0x000338ED) / `_bfme_showAptScreenWithArg` (0x0000ACFE) ILTs for the
//    rest -- only the HOLDER TYPES are new per screen (each screen gets its
//    own incremental-link thunk for the holder ctor, same as
//    CampaignReview/SpellStore/QuitMenu already show). New pins needed
//    (verify against retail again if this drifts, don't trust blindly):
//      ?BfmeAptScreenInGameChatVftable@@3PAPBXA          0x01105384
//      ?BfmeAptScreenInGameChatSecondaryVftable@@3PAPBXA 0x01105380
//      ??0InGameChatRefHolder@@QAE@UFunctorBinding@@@Z   0x00026E45
//      ??0InGameChatShowHolder@@QAE@UFunctorBinding@@@Z  0x0000F84E
//      ??0InGameChatArgHolder@@QAE@UFunctorBinding@@@Z   0x00039D38
//      ?_bfme_setAptScreenRef@@YAXABVAsciiString@@VInGameChatRefHolder@@@Z 0x0003DF14 (alias)
//      ?showAptScreen@InGameChatRegistry@@QAEXABVAsciiString@@VInGameChatShowHolder@@@Z 0x000338ED (alias)
//      ?showAptScreenWithArg@InGameChatRegistry@@QAEXABVAsciiString@@PAXVInGameChatArgHolder@@@Z 0x0000ACFE (alias)
//  - the two BfmeThingTC sub-objects MUST be reached through a named local
//    pointer (`BfmeThingTC *first = &m_firstControl; first->bfmeBaseTC(); ...`),
//    not `m_firstControl.bfmeBaseTC()` directly -- the direct-member-call
//    form compiles the vftable/m_bfmeWhat stores through [esi+off] instead
//    of an indexed [reg+off] the way retail does; the named-pointer form
//    recovers retail's exact instruction SHAPE for that block (confirmed
//    this session), it just doesn't fix the register COLOR (next point).
//
// STILL UNRESOLVED at t=40 (this session, after the 0.91 prior session):
//  compiled body is 910 bytes vs retail's 987 (77 short). The block-setup
//  section (control ctors + field zeroing) now matches retail's
//  instruction SHAPE exactly but with ebp/ebx systematically SWAPPED
//  (retail: xor ebp,ebp for the zero constant, lea ebx,[esi+0x270] for the
//  control address; this build picks the opposite pair throughout). Per
//  AGENTS.md this register-color swap is generally not source-controllable
//  and not worth re-chasing directly. Past the six FunctorBinding
//  registration blocks + the ScreenType arg block, this build's code is
//  measurably more COMPACT than retail (the size gap), which likely means
//  retail's compiled EH state-tag byte sequence (the `mov byte
//  ptr[esp+N],K` markers seen throughout, K=2..0xA in
//  `python3 tools/dis_retail.py 0x005160E0 987`) has one more distinct
//  state than this source produces -- worth re-deriving call-by-call
//  against that disassembly (not the register swap) before further work.

extern const void *BfmeAptScreenInGameChatVftable[];
extern const void *BfmeAptScreenInGameChatSecondaryVftable[];
extern "C" const void *_bfmeVftTC[];

class Rva005127A0InGameChat;
extern Rva005127A0InGameChat *g_Rva005127A0InGameChat;   // 0x012F4988

class BfmeThingTC
{
public:
	void bfmeBaseTC();
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
	BfmeThingTC m_firstControl;
	BfmeThingTC m_secondControl;
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
	BfmeThingTC *first = &m_firstControl;
	first->bfmeBaseTC();
	first->m_bfmeVft = (void *)_bfmeVftTC;
	first->m_bfmeWhat = (void *)4;
	BfmeThingTC *second = &m_secondControl;
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

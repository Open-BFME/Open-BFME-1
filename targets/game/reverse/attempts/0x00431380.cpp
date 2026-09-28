// ??1GameClient@@UAE@XZ
// partial score=1.0 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// GameClient::~GameClient -- retail RVA 0x00431380 (1046 bytes; ret at +0x415).
// Identity: the body installs vtables 0x010F37F0 / 0x010F37DC and then the
// Snapshot vtable 0x01073744 before ~SubsystemInterface.  0x010F37F0 is the
// Zero Hour GameClient vtable: its slots hold the matched GameClient::reset
// (0x00431900), setFrame (0x004318A0), registerDrawable (0x0042E530),
// findDrawableByID (0x00430AF0), firstDrawable (0x004318B0),
// iterateDrawablesInRegion (0x0042E570), destroyDrawable (0x00431110) and
// getFrame (0x004318C0) in Zero Hour's declaration order.  The body is Zero
// Hour's ~GameClient (GameClient.cpp) with BFME's subsystem set, followed by
// the member destructors of BFME's layout.
// Zero Hour's GameClient.h has a different member layout, so the class here
// is the BFME layout this body and the matched siblings witness.
//
// STATUS (opus-5.5, 2026-09-28): EXACT modulo relocations at 1046 bytes
// (probe --size 1046; the ledger scaffold says 1040 and cuts the epilogue).
// Not landed: ??1GameClient@@UAE@XZ is claimed at 0x00596500
// (GameClientDestructor.cpp), a different class (vtable 0x0110C2D8: 12 slots,
// pure holes at 9/10, members out to +0x488) that AptPalantir derives from.
// Landing needs that family renamed first: 0x00596500 GameClientDestructor.cpp,
// 0x00597680 GameClientDeletingDestructor.cpp (??_GGameClient), the AptPalantir
// destructor 0x0079D1D0 and constructor TUs (GUI/AptPalantirDestructor.cpp,
// GUI/AptPalantirConstructor.cpp), funclets uw_00C51B50/uw_00C51BE0, and the
// ??0GameClient pin 0x00597FC0 / update@GameClient 0x00598950 /
// bfmeReset00592B80@GameClient claims.  Then land with --replace-rva
// 0x00431380 and --boundary-evidence (ret +0x415, int3 after).
// Levers that closed it: /D_STLP_USE_STATIC_LIB (inline node_alloc
// threshold), an undefined explicit specialisation of the drawable
// hashtable destructor (retail calls 0x00430CA0 out of line), and a plain
// `delete TheDrawGroupInfo` (no Zero Hour if).

#include "string_base.h"
template<> inline StringBase<char>::~StringBase() { releaseBuffer(); }
#include "ascii_string.h"
#include <list>
#include <vector>
#include <hash_map>

typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef int Int;
typedef UnsignedInt TranslatorID;

enum { MAX_CLIENT_TRANSLATORS = 32 };

class Drawable
{
public:
	Drawable *getNextDrawable() const { return m_nextDrawable; }
	char m_unmodelled_000[0x104];
	Drawable *m_nextDrawable;
};

// Same drawable lookup instantiation as the matched GameClient::reset TU.
struct Gen_t_00430ca0_p12cd { int a[3]; };
typedef _STL::pair<const int, Gen_t_00430ca0_p12cd> GameClientDrawableHashPair;
typedef _STL::hashtable<GameClientDrawableHashPair, int, _STL::hash<int>,
	_STL::_Select1st<GameClientDrawableHashPair>, _STL::equal_to<int>,
	_STL::allocator<GameClientDrawableHashPair> > GameClientDrawableHash;
// Retail calls this instantiation's destructor out of line (0x00430CA0).
template<> GameClientDrawableHash::~hashtable();

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	char *m_name;
};

class Xfer;
class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc( Xfer *xfer ) = 0;
	virtual void xfer( Xfer *xfer ) = 0;
	virtual void loadPostProcess( void ) = 0;
};

class MessageStream
{
public:
	void removeTranslator( TranslatorID id );
};
extern MessageStream *TheMessageStream;

struct DrawGroupInfo
{
	AsciiString m_fontName;
};
extern DrawGroupInfo *TheDrawGroupInfo;

#define BFME_DELETABLE(T) class T { public: virtual ~T(); };
BFME_DELETABLE(CampaignManager)
BFME_DELETABLE(RayEffectSystem)
BFME_DELETABLE(HotKeyManager)
BFME_DELETABLE(InGameUI)
BFME_DELETABLE(Shell)
BFME_DELETABLE(IMEManager)
BFME_DELETABLE(GameWindowManager)
BFME_DELETABLE(Mouse)
BFME_DELETABLE(AnimationSoundClientBehaviorGlobal)
BFME_DELETABLE(TerrainVisual)
BFME_DELETABLE(Display)
BFME_DELETABLE(LanguageFilter)
BFME_DELETABLE(VideoPlayer)
BFME_DELETABLE(Anim2DCollection)
BFME_DELETABLE(ImageCollection)
BFME_DELETABLE(Keyboard)
BFME_DELETABLE(Rva0048EC80Manager)
BFME_DELETABLE(SnowManager)
BFME_DELETABLE(CloudEffectSystem)
BFME_DELETABLE(CloudSystem)
#undef BFME_DELETABLE

class FontLibrary
{
public:
	virtual ~FontLibrary();
	virtual void init();
	virtual void slot08();
	virtual void slot0c();
	virtual void reset();			// +0x10
};

// Retail 0x012F19E8: only its slot +0x24 is called here; identity unproven.
struct Rva00579160Manager
{
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
};

// Header template manager: non-virtual destructor 0x0048C5B0 (ledger name).
class Gen_0048C5B0
{
public:
	~Gen_0048C5B0();
};

extern CampaignManager *TheCampaignManager;
extern RayEffectSystem *TheRayEffects;
extern HotKeyManager *TheHotKeyManager;
extern InGameUI *TheInGameUI;
extern Shell *TheShell;
extern IMEManager *TheIMEManager;
extern Rva00579160Manager *Rva00579160TheManager;
extern GameWindowManager *TheWindowManager;
extern FontLibrary *TheFontLibrary;
extern Mouse *TheMouse;
extern AnimationSoundClientBehaviorGlobal *g_animationSoundClientBehaviorGlobal;
extern TerrainVisual *TheTerrainVisual;
extern Display *TheDisplay;
extern Gen_0048C5B0 *TheHeaderTemplateManager;
extern LanguageFilter *TheLanguageFilter;
extern VideoPlayer *TheVideoPlayer;
extern Anim2DCollection *TheAnim2DCollection;
extern ImageCollection *TheMappedImageCollection;
extern Keyboard *TheKeyboard;
extern Rva0048EC80Manager *Rva0048EC80TheManager;
extern SnowManager *TheSnowManager;
extern CloudEffectSystem *TheCloudEffectSystem;
extern CloudSystem *TheCloudSystem;

void Gen_00510b50();	// 0x00510B50, BFME shutdown step run first

class CommandTranslator;

class GameClient : public SubsystemInterface, public Snapshot
{
public:
	struct DrawableTOCEntry
	{
		AsciiString name;
		UnsignedShort id;
	};
	typedef _STL::list<DrawableTOCEntry> DrawableTOCList;

	virtual ~GameClient();
	virtual void destroyDrawable( Drawable *draw );

	UnsignedInt m_frame;					// +0x0c
	Drawable *m_drawableList;				// +0x10
	GameClientDrawableHash m_drawableHash;			// +0x14
	UnsignedInt m_nextDrawableID;				// +0x28
	TranslatorID m_translators[ MAX_CLIENT_TRANSLATORS ];	// +0x2c
	UnsignedInt m_numTranslators;				// +0xac
	CommandTranslator *m_commandTranslator;			// +0xb0
	UnsignedInt m_rva00431380Field0B4;			// +0xb4
	AsciiString m_rva00431380String0B8;			// +0xb8
	char m_unmodelled_0bc[0xe0 - 0xbc];
	_STL::list<Drawable *> m_rva00431380List0E0;		// +0xe0
	_STL::vector<Drawable *> m_rva00431380Vector0E4;	// +0xe4
	DrawableTOCList m_drawableTOC;				// +0xf0
	_STL::list<Drawable *> m_rva00431380Lists0F4[ 10 ];	// +0xf4
};

// ??1GameClient@@UAE@XZ
GameClient::~GameClient()
{
	Gen_00510b50();

	delete TheDrawGroupInfo;
	TheDrawGroupInfo = NULL;

	// clear any drawable TOC we might have
	m_drawableTOC.clear();

	if(TheCampaignManager)
		delete TheCampaignManager;
	TheCampaignManager = NULL;

	// destroy all Drawables
	Drawable *draw, *nextDraw;
	for( draw = m_drawableList; draw; draw = nextDraw )
	{
		nextDraw = draw->getNextDrawable();
		destroyDrawable( draw );
	}
	m_drawableList = NULL;

	delete TheRayEffects;
	TheRayEffects = NULL;

	delete TheHotKeyManager;
	TheHotKeyManager = NULL;

	delete TheInGameUI;
	TheInGameUI = NULL;

	delete TheShell;
	TheShell = NULL;

	delete TheIMEManager;
	TheIMEManager = NULL;

	if (Rva00579160TheManager)
		Rva00579160TheManager->slot24();

	delete TheWindowManager;
	TheWindowManager = NULL;

	if (TheFontLibrary)
	{
		TheFontLibrary->reset();
		delete TheFontLibrary;
		TheFontLibrary = NULL;
	}

	delete TheMouse;
	TheMouse = NULL;

	delete g_animationSoundClientBehaviorGlobal;
	g_animationSoundClientBehaviorGlobal = NULL;

	delete TheTerrainVisual;
	TheTerrainVisual = NULL;

	delete TheDisplay;
	TheDisplay = NULL;

	delete TheHeaderTemplateManager;
	TheHeaderTemplateManager = NULL;

	delete TheLanguageFilter;
	TheLanguageFilter = NULL;

	delete TheVideoPlayer;
	TheVideoPlayer = NULL;

	// destroy all translators
	for( UnsignedInt i = 0; i < m_numTranslators; i++ )
		TheMessageStream->removeTranslator( m_translators[ i ] );
	m_numTranslators = 0;
	m_commandTranslator = NULL;

	delete TheAnim2DCollection;
	TheAnim2DCollection = NULL;

	delete TheMappedImageCollection;
	TheMappedImageCollection = NULL;

	delete TheKeyboard;
	TheKeyboard = NULL;

	delete Rva0048EC80TheManager;
	Rva0048EC80TheManager = NULL;

	delete TheSnowManager;
	TheSnowManager = NULL;

	delete TheCloudEffectSystem;
	TheCloudEffectSystem = NULL;

	delete TheCloudSystem;
	TheCloudSystem = NULL;
}

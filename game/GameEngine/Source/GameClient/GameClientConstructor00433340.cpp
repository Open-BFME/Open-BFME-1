// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// GameClient::GameClient -- retail RVA 0x00433340 (612 bytes; ret at +0x249).
// Identity: the body constructs SubsystemInterface, installs the Snapshot
// vtable 0x01073744 and then the GameClient vtables 0x010F37F0 / 0x010F37DC,
// the same pair the matched GameClient::~GameClient (0x00431380) removes;
// 0x010F37F0's slots hold the matched GameClient::reset, registerDrawable,
// findDrawableByID and destroyDrawable.  Its only caller is the derived
// constructor at 0x006FB500.  The body is Zero Hour's GameClient::GameClient
// (translator list, m_drawableTOC.clear(), m_nextDrawableID = 1,
// TheDrawGroupInfo = new DrawGroupInfo) with BFME's members initialised in
// the constructor's initializer list, on the layout the matched destructor
// witnesses (GameClientDestructor00431380.cpp).  Members that no matched body
// names keep address tokens.
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
	SubsystemInterface();
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

// DrawGroupInfo::DrawGroupInfo is the 0x2C-byte constructor at 0x00421B80
// ("Arial", size 10), still filed under its ledger name.
class Gen_00421B80
{
public:
	Gen_00421B80(void);
	char m_bytes[0x2c];
};

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

	GameClient();
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
	bool m_rva00433340Flag0BC;				// +0xbc
	bool m_rva00433340Flag0BD;				// +0xbd
	UnsignedInt m_rva00433340Field0C0;			// +0xc0
	bool m_rva00433340Flag0C4;				// +0xc4
	bool m_rva00433340Flag0C5;				// +0xc5
	bool m_rva00433340Flag0C6;				// +0xc6
	UnsignedInt m_rva00433340Field0C8;			// +0xc8
	UnsignedInt m_rva00433340Field0CC;			// +0xcc
	UnsignedInt m_rva00433340Field0D0;			// +0xd0
	UnsignedInt m_rva00433340Field0D4;			// +0xd4
	UnsignedInt m_rva00433340Field0D8;			// +0xd8
	UnsignedInt m_rva00433340Field0DC;			// +0xdc
	_STL::list<Drawable *> m_rva00431380List0E0;		// +0xe0
	_STL::vector<Drawable *> m_rva00431380Vector0E4;	// +0xe4
	DrawableTOCList m_drawableTOC;				// +0xf0
	_STL::list<Drawable *> m_rva00431380Lists0F4[ 10 ];	// +0xf4
};


// ??0GameClient@@QAE@XZ
GameClient::GameClient()
	: m_frame( 0 ),
	  m_drawableList( NULL ),
	  m_drawableHash( 100, _STL::hash<int>(), _STL::equal_to<int>(), _STL::allocator<GameClientDrawableHashPair>() ),
	  m_nextDrawableID( 1 ),
	  m_numTranslators( 0 ),
	  m_commandTranslator( NULL ),
	  m_rva00431380Field0B4( 0 ),
	  m_rva00431380String0B8( "" ),
	  m_rva00433340Flag0BC( false ),
	  m_rva00433340Flag0BD( false ),
	  m_rva00433340Field0C0( 0 ),
	  m_rva00433340Flag0C4( false ),
	  m_rva00433340Flag0C5( false ),
	  m_rva00433340Flag0C6( false ),
	  m_rva00433340Field0C8( 0 ),
	  m_rva00433340Field0CC( 0 ),
	  m_rva00433340Field0D0( 0 ),
	  m_rva00433340Field0D4( 0 ),
	  m_rva00433340Field0D8( 0 ),
	  m_rva00433340Field0DC( 0 )
{
	// zero our translator list
	for( Int i = 0; i < MAX_CLIENT_TRANSLATORS; i++ )
		m_translators[ i ] = (TranslatorID)-1;

	m_drawableTOC.clear();

	TheDrawGroupInfo = (DrawGroupInfo *)new Gen_00421B80;
}

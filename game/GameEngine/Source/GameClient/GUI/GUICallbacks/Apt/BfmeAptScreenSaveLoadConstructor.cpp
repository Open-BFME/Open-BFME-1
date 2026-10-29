// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// SaveLoad screen construction and callback registration.

#include <list>
#include "ascii_string.h"
#include "unicode_string.h"
#include "game/GameEngine/Include/GameClient/BfmeAptScreenBaseLayout.h"
class GameWindow;
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding {
    FunctorBinding(FunctorMethod method, FunctorTarget *target):m_target(target),m_method(method) {}
    FunctorTarget *m_target; unsigned m_unmodelled; FunctorMethod m_method;
};
class Rva0056D9B0FunctorHolder { public: Rva0056D9B0FunctorHolder(FunctorBinding); private: void *m_ptr; };
class FunctorWrapperHead { public: FunctorWrapperHead():m_refCount(0) {} virtual ~FunctorWrapperHead(); int m_refCount; };
class Rva0050F8B0FunctorHolder;
class _bfme_AptGameWindow
{
public:
    _bfme_AptGameWindow(void *);
    virtual ~_bfme_AptGameWindow();
    void _bfme_showAptScreen(const AsciiString &,Rva0050F8B0FunctorHolder);
private:
    BfmeAptScreenBaseLayout<> m_storage;
};
class __declspec(novtable) BfmeAptScreenSaveLoadSecondary
{
public:
    virtual void slot00()=0;
private:
    char m_storage[0x3C];
};
typedef _bfme_AptGameWindow BfmeAptScreenSaveLoadConstructorBase;
class BfmeAptFunctorMarker {};
class Rva0050F8B0FunctorHolder { public: void *m_ptr; Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &); ~Rva0050F8B0FunctorHolder(); };
typedef _bfme_AptGameWindow BfmeSaveLoadAptRegistry;
typedef void (_bfme_AptGameWindow::*BfmeSaveLoadShow0056E980)(const AsciiString &,Rva0056D9B0FunctorHolder);
class Rva0050F920FunctorHolder;
class WindowManager { public: void bfme_showBackground(int); void bindShownWithArg(const AsciiString &,void *,Rva0050F920FunctorHolder); };
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
class BfmeAptScreenSaveLoad;
extern BfmeAptScreenSaveLoad *TheAptSaveLoad;
#define g_bfmeReadyAG reinterpret_cast<void *&>(TheAptSaveLoad)
extern void *bfmeAllocNode( unsigned int bytes );

__declspec(noinline) int Rva0056DEC0(int,int);
__declspec(noinline) int Rva0056DF40(int,int);
__declspec(noinline) int Rva0056DFC0(int,int);
// Inline adapters retain the bank's helper names and canonical call targets.
__forceinline int bfmeMake_0056E900(int a, int b) { return Rva0056DEC0(a,b); }
__forceinline int bfmeSaveLoadObfuscatedStep(int a, unsigned int b) { return Rva0056DF40(a,(int)b); }
typedef int (__cdecl *BigObfHook)( void *, void *, __int64 );

struct BigObfSlot
{
	BigObfHook  m_hook;
	BigObfHook  m_alt;
	char        m_pad[ 0x80 ];
	void       *m_a;
	void       *m_b;
};

#define BFME_OBF_SLOT( BASE )                                             \
	extern BigObfSlot g_Slot##BASE;

#define BFME_OBF_STATE( ADDR )                                            \
	class Obf##ADDR                                                       \
	{                                                                     \
	public:                                                               \
		Obf##ADDR( int *a, int *b );                                      \
		unsigned int m_bits[ 8 ];                                         \
	};

struct BigObfSelectorRecord
{
	unsigned int m_key[ 5 ];
	unsigned int m_seed[ 5 ];
};

// The matched constructor uses an ESP-derived two-bit selector.
// The final two receiver words are read before being overwritten.

#define BFME_OBF_RECORD( ADDR )                                           \
	extern BigObfSelectorRecord g_ObfRecord##ADDR;

#define BFME_OBF_CTOR_BODY( ADDR, RECORD, SELECTOR, C1, C2, C3 )          \
	inline Obf##ADDR::Obf##ADDR( int *a, int *b )                                \
	{                                                                     \
		unsigned int selector = 0;                                         \
		SELECTOR                                                           \
		unsigned int index = selector & 3;                                 \
		unsigned int key = RECORD.m_key[ index ];                          \
		m_bits[ 0 ] = RECORD.m_seed[ index ];                              \
		m_bits[ 1 ] = C1;                                                  \
		m_bits[ 2 ] = C2;                                                  \
		m_bits[ 3 ] = C3;                                                  \
		m_bits[ 4 ] = *a;                                                  \
		m_bits[ 5 ] = *b;                                                  \
		m_bits[ 1 ] ^= key * key;                                          \
		m_bits[ 2 ] ^= m_bits[ 1 ] * key;                                 \
		m_bits[ 3 ] ^= m_bits[ 2 ] * key;                                 \
		m_bits[ 4 ] ^= m_bits[ 3 ] * key;                                 \
		m_bits[ 5 ] ^= m_bits[ 4 ] * key;                                 \
		m_bits[ 6 ] ^= m_bits[ 5 ] * key;                                 \
		m_bits[ 7 ] ^= m_bits[ 6 ] * key;                                 \
	}

#define BFME_OBF_SELECT_STACK __asm { mov selector, esp }

#define BFME_OBF_FALLBACK( ADDR )                                         \
	int __cdecl Gen##ADDR( int a, int b );

#define BFME_OBF_WRAPPER( NAME, SLOT, STATE, FALLBACK )                   \
	inline int __cdecl NAME( int a, int b )                                      \
	{                                                                     \
		BigObfHook hook = SLOT.m_hook;                                    \
		if ( hook )                                                       \
			goto hot;                                                     \
		if ( SLOT.m_alt )                                                 \
		{                                                                 \
	hot:                                                                  \
			struct Args { void *pa; void *pb; };                           \
			Args args = { SLOT.m_a, SLOT.m_b };                            \
			STATE o( &a, &b );                                            \
			return hook( args.pa, args.pb, (__int64)(int)&o );                      \
		}                                                                 \
		return FALLBACK( a, b );                                          \
	}

BFME_OBF_SLOT( 012BF440 )
BFME_OBF_STATE( 0056D5E0 )
BFME_OBF_RECORD( 012B7E70 )
BFME_OBF_CTOR_BODY( 0056D5E0, g_ObfRecord012B7E70, BFME_OBF_SELECT_STACK, 0x0C281240, 0x48000A06, 0x14A8024B )
BFME_OBF_FALLBACK( 0056C3F0 )
BFME_OBF_WRAPPER( Rva0056DE40, g_Slot012BF440, Obf0056D5E0, Gen0056C3F0 )

struct Rva0056E980EncodedValue
{
    int m_value;
    __forceinline Rva0056E980EncodedValue(short v):m_value(bfmeMake_0056E900(v,v)) {}
    __forceinline operator short() const { return (short)Rva0056DFC0(m_value,m_value); }
    __forceinline bool pending() const { return Rva0056DE40(m_value,0xB83453E7) != (int)0x993BA311; }
    __forceinline void advance() { m_value=bfmeSaveLoadObfuscatedStep(m_value,0xBA792210u); }
};
class Rva0056C9F0FunctorWrapper : public FunctorWrapperHead
{
public:
	__forceinline Rva0056C9F0FunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

// These local converting constructors build the receiver-specific wrappers.
// The canonical holder parameters remain one owned pointer.
class Rva0050F920FunctorHolder
{
public:
	template<class Binding>
    __forceinline Rva0050F920FunctorHolder( Binding binding )
	{
		m_ptr = new Rva0056C9F0FunctorWrapper( binding );
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	Rva0050F920FunctorHolder( const Rva0050F920FunctorHolder & );
	~Rva0050F920FunctorHolder()
    {
        FunctorWrapperHead *p=m_ptr;
        if(p && (p->m_refCount=p->m_refCount-1)<=0)
            delete p;
    }
	Rva0056C9F0FunctorWrapper *m_ptr;
};

class Rva0056CA40FunctorWrapper : public FunctorWrapperHead
{
public:
	__forceinline Rva0056CA40FunctorWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class Rva0050F840FunctorHolder
{
public:
	template<class Binding>
    __forceinline Rva0050F840FunctorHolder( Binding binding )
	{
		m_ptr = new Rva0056CA40FunctorWrapper( binding );
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder & );
	~Rva0050F840FunctorHolder()
    {
        FunctorWrapperHead *p=m_ptr;
        if(p && (p->m_refCount=p->m_refCount-1)<=0)
            delete p;
    }
	Rva0056CA40FunctorWrapper *m_ptr;
};

typedef Rva0056C9F0FunctorWrapper BfmeSaveLoadShownWithArgWrapper;
typedef Rva0056CA40FunctorWrapper BfmeSaveLoadInitGadgetWrapper;
typedef Rva0050F920FunctorHolder BfmeSaveLoadShownWithArgHolder;
typedef Rva0050F840FunctorHolder BfmeSaveLoadInitGadgetHolder;
typedef WindowManager BfmeSaveLoadWindowManager;
void _bfme_setAptScreenRef(const AsciiString &,Rva0050F840FunctorHolder);
#define rva004628E0 _bfme_setAptScreenRef

class BfmeGameLogicPause
{
public:
	bool isGamePaused();
	void setGamePaused( bool paused, int pauseMode, bool affectMouse );
};

class GameLogic;
extern GameLogic *TheGameLogic;
extern const char *g_saveLoadRegistrations012B7E60[];
#define BfmeSaveLoadCallbackNames g_saveLoadRegistrations012B7E60

class SaveGameInfo
{
public:
    SaveGameInfo(const SaveGameInfo &);
    ~SaveGameInfo();
    AsciiString saveGameMapName;
    AsciiString pristineMapName;
    AsciiString mapLabel;
    unsigned char m_date[0x10];
    AsciiString campaignSide;
    int missionNumber;
    UnicodeString description;
    int saveFileType;
    AsciiString missionMapName;
};
struct AvailableGameInfo
{
    AvailableGameInfo(const AvailableGameInfo &);
    ~AvailableGameInfo();
    AsciiString filename;
    SaveGameInfo saveGameInfo;
    AvailableGameInfo *next;
    AvailableGameInfo *prev;
};
typedef AvailableGameInfo Z1Elem0056D960;
typedef _STL::list<AvailableGameInfo> BfmeSaveLoadSlotList;

// Retail binds a code pointer and zero receiver adjustment.
// The canonical callback owners use a four-byte member-pointer view.
template<class Method>
__forceinline FunctorMethod rva0056E980MemberView(Method method)
{
    typedef char FourByteMethod[sizeof(Method)==4 ? 1 : -1];
    typedef char EightByteBinding[sizeof(FunctorMethod)==8 ? 1 : -1];
    union View { struct { Method method; int adjustment; } raw; FunctorMethod callback; } value;
    value.raw.method=method;
    value.raw.adjustment=0;
    return value.callback;
}

class Rva0056A830 { public: void apply(int); };
class Rva56E070StateOwner { public: void beginState(int); void dispatchLateState(int); };
class BfmeThingME { public: void bfmeGoME(int); };
class Rva0056C090 { public: void update(int); };
class Rva56A8StateOwner { public: void applyGlobalCall(int); void applyZeroState(int); void applyDefaultState(int); void applyFourState(int); };
class Rva0056A930 { public: void apply(int); };

class __multiple_inheritance BfmeAptScreenSaveLoad
	: public _bfme_AptGameWindow, public BfmeAptScreenSaveLoadSecondary
{
public:
	BfmeAptScreenSaveLoad( void *context );
    virtual ~BfmeAptScreenSaveLoad();
	__forceinline static FunctorMethod _bfme_onInitialized() { return rva0056E980MemberView(&Rva0056A830::apply); }
	void _bfme_onClosed(const char *);
	__forceinline static FunctorMethod _bfme_onLoad() { return rva0056E980MemberView(&Rva56E070StateOwner::beginState); }
	__forceinline static FunctorMethod _bfme_onSave() { return rva0056E980MemberView(&BfmeThingME::bfmeGoME); }
	__forceinline static FunctorMethod _bfme_onDelete() { return rva0056E980MemberView(&Rva0056C090::update); }
	__forceinline static FunctorMethod _bfme_onBack() { return rva0056E980MemberView(&Rva56A8StateOwner::applyGlobalCall); }
	__forceinline static FunctorMethod _bfme_onSelectCampaign() { return rva0056E980MemberView(&Rva56A8StateOwner::applyZeroState); }
	__forceinline static FunctorMethod _bfme_onSelectSkirmish() { return rva0056E980MemberView(&Rva56A8StateOwner::applyDefaultState); }
	__forceinline static FunctorMethod _bfme_onSelectReplay() { return rva0056E980MemberView(&Rva56A8StateOwner::applyFourState); }
	__forceinline static FunctorMethod _bfme_onConfirmationOk() { return rva0056E980MemberView(&Rva56E070StateOwner::dispatchLateState); }
	__forceinline static FunctorMethod _bfme_onConfirmationCancel() { return rva0056E980MemberView(&Rva0056A930::apply); }
	void _bfme_onInitGadget( const char *name, void *argument, GameWindow *window );
	void _bfme_provide( const char *selector, void *value, bool setting );

private:
	int m_field258;
	AvailableGameInfo *m_field25C;
	bool m_field260;
	int m_field264;
	int m_field268;
	int m_field26C;
	int m_field270;
	int m_field274;
	bool m_field278;
	int m_field27C;
	bool m_field280;
	BfmeSaveLoadSlotList m_field284;
};

typedef char BfmeSaveLoadObjectExtent[sizeof(BfmeAptScreenSaveLoad)==0x288 ? 1 : -1];
typedef char BfmeSaveLoadBindingExtent[sizeof(FunctorBinding)==0x10 ? 1 : -1];
typedef char BfmeSaveLoadWrapperExtent[sizeof(Rva0056C9F0FunctorWrapper)==0x18 ? 1 : -1];
typedef char BfmeSaveLoadHolderExtent[sizeof(Rva0050F920FunctorHolder)==4 ? 1 : -1];
typedef char BfmeSaveLoadValueExtent[sizeof(AvailableGameInfo)==0x3C ? 1 : -1];

// ??0BfmeAptScreenSaveLoad@@QAE@PAX@Z
BfmeAptScreenSaveLoad::BfmeAptScreenSaveLoad( void *context )
	: _bfme_AptGameWindow( context ), m_field258(0), m_field25C(0), m_field264(0), m_field268(0), m_field26C(0), m_field270(0), m_field274(0), m_field278(false), m_field27C(0), m_field280(false)
{
	if( g_bfmeReadyAG == 0 )
	{
		g_bfmeReadyAG = this;
		BfmeSaveLoadAptRegistry *registry =
			(BfmeSaveLoadAptRegistry *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onInitialized();
			AsciiString name( "AptSaveLoad::OnInitialized" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onClosed;
			AsciiString name( "AptSaveLoad::OnClosed" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onLoad();
			AsciiString name( "AptSaveLoad::Load" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onSave();
			AsciiString name( "AptSaveLoad::Save" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onDelete();
			AsciiString name( "AptSaveLoad::Delete" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onBack();
			AsciiString name( "AptSaveLoad::Back" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onSelectCampaign();
			AsciiString name( "AptSaveLoad::SelectCampaign" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onSelectSkirmish();
			AsciiString name( "AptSaveLoad::SelectSkirmish" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onSelectReplay();
			AsciiString name( "AptSaveLoad::SelectReplay" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onConfirmationOk();
			AsciiString name( "AptSaveLoad::ConfirmationOk" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				BfmeAptScreenSaveLoad::_bfme_onConfirmationCancel();
			AsciiString name( "AptSaveLoad::ConfirmationCancel" );
			(registry->*reinterpret_cast<BfmeSaveLoadShow0056E980>(&_bfme_AptGameWindow::_bfme_showAptScreen))( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		Rva0056E980EncodedValue obfValue(0);
		while( obfValue.pending() )
		{
			{
				FunctorMethod callback =
					(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_provide;
				short nameIndex = (short)obfValue;
				AsciiString name( BfmeSaveLoadCallbackNames[ nameIndex ] );
				( (BfmeSaveLoadWindowManager *)g_theWindowManager )
					->bindShownWithArg( name, (void *)(int)(short)obfValue,
						Rva0050F920FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
			}
			obfValue.advance();
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onInitGadget;
			AsciiString initGadgets( "AptSaveLoad::InitGadgets" );
			rva004628E0( initGadgets, Rva0050F840FunctorHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		m_field260 = ((BfmeGameLogicPause *)TheGameLogic)->isGamePaused();
		((BfmeGameLogicPause *)TheGameLogic)->setGamePaused( true, 2, true );
		m_field280 = *(int *)( (char *)g_theWindowManager + 0x1B8 ) == 0;
		if( m_field280 )
			g_theWindowManager->bfme_showBackground( 1 );
	}
}


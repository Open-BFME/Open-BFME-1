// ??0BfmeAptScreenSaveLoad@@QAE@PAX@Z
// partial score=0.8237 date=2026-10-03
// ??0BfmeAptScreenSaveLoad@@QAE@PAX@Z
// cl: /I. /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Experimental bank, NOT a production conversion. Derived from the served stash.
// Loop/ownership repairs and the native StringBase header improve raw bytes.
// The inherited SaveLoad semantic owner/callback names, synthetic base/vptr writes,
// registry/holder identities, data bindings, and frame still require reconciliation.
// Obf0056D5E0 and Rva0056DE40 below are the existing BigObfHookWrappers.cpp
// definitions. The one ESP read is that independently verified constructor's
// established compiler-machinery exception; the caller contains no assembly.

#include <list>
#include "ascii_string.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
class GameWindow;
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)(void);
struct FunctorBinding {
    FunctorBinding(FunctorMethod method, FunctorTarget *target):m_target(target),m_method(method) {}
    FunctorTarget *m_target; unsigned m_unmodelled; FunctorMethod m_method;
};
class Rva0056D9B0FunctorHolder { public: Rva0056D9B0FunctorHolder(FunctorBinding); private: void *m_ptr; };
class FunctorWrapperHead { public: FunctorWrapperHead():m_refCount(0) {} virtual ~FunctorWrapperHead(); int m_refCount; };
class _bfme_AptGameWindow { public: _bfme_AptGameWindow(void *); virtual ~_bfme_AptGameWindow(); private: char m_unmodelled[0x254]; };
class BfmeAptFunctorMarker {};
class BfmeSaveLoadAptRegistry { public: void _bfme_showAptScreen(const AsciiString &,Rva0056D9B0FunctorHolder); };
class WindowManager { public: void bfme_showBackground(int); };
extern WindowManager *g_theWindowManager;
extern void *g_bfmeReadyAG;
extern void *bfmeAllocNode( unsigned int bytes );
extern const void *BfmeAptScreenSaveLoadVftable[];
extern const void *BfmeAptScreenSaveLoadSecondaryVftable[];

__declspec(noinline) int Rva0056DEC0(int,int);
__declspec(noinline) int Rva0056DF40(int,int);
__declspec(noinline) int Rva0056DFC0(int,int);
// Preserve inherited bank helper spellings as inline adapters, not new pins.
// Retail routes establish the canonical called bodies; these are not EA names.
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

// The constructors use the same two-bit selector helpers already recovered in
// Q3SelectorRecordReaders.cpp and R3SelectorRecordReadersEbp.cpp.  VC7.1 has
// no intrinsic for rdtsc, and neither esp nor ebp can be read as a C++ value,
// so these one-instruction selectors are the only non-C++ part of the bodies.
// The xor chain is ordinary C++; its final two inputs are intentionally the
// pre-existing object words, as the retail anti-tamper code reads them before
// writing them.

#define BFME_OBF_RECORD( ADDR )                                           \
	extern BigObfSelectorRecord g_ObfRecord##ADDR;

#define BFME_OBF_CTOR_BODY( ADDR, RECORD, SELECTOR, C1, C2, C3 )          \
	Obf##ADDR::Obf##ADDR( int *a, int *b )                                \
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
#define BFME_OBF_SELECT_FRAME __asm { mov selector, ebp }
#define BFME_OBF_SELECT_TIMESTAMP __asm { rdtsc } __asm { mov selector, eax }

#define BFME_OBF_FALLBACK( ADDR )                                         \
	int __cdecl Gen##ADDR( int a, int b );

#define BFME_OBF_WRAPPER( NAME, SLOT, STATE, FALLBACK )                   \
	int __cdecl NAME( int a, int b )                                      \
	{                                                                     \
		BigObfHook hook = SLOT.m_hook;                                    \
		if ( hook )                                                       \
			goto hot;                                                     \
		if ( SLOT.m_alt )                                                 \
		{                                                                 \
	hot:                                                                  \
			void *pa = SLOT.m_a;                                          \
			void *pb = SLOT.m_b;                                          \
			STATE o( &a, &b );                                            \
			return hook( pa, pb, (__int64)(int)&o );                      \
		}                                                                 \
		return FALLBACK( a, b );                                          \
	}

BFME_OBF_SLOT( 012BF440 )
BFME_OBF_STATE( 0056D5E0 )
BFME_OBF_RECORD( 012B7E70 )
BFME_OBF_CTOR_BODY( 0056D5E0, g_ObfRecord012B7E70, BFME_OBF_SELECT_STACK, 0x0C281240, 0x48000A06, 0x14A8024B )
BFME_OBF_FALLBACK( 0056C3F0 )
BFME_OBF_WRAPPER( Rva0056DE40, g_Slot012BF440, Obf0056D5E0, Gen0056C3F0 )





class BfmeSaveLoadShownWithArgWrapper : public FunctorWrapperHead
{
public:
	__forceinline BfmeSaveLoadShownWithArgWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class BfmeSaveLoadShownWithArgHolder
{
public:
	__forceinline BfmeSaveLoadShownWithArgHolder( FunctorBinding binding )
	{
		m_ptr = new BfmeSaveLoadShownWithArgWrapper( binding );
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	BfmeSaveLoadShownWithArgHolder( const BfmeSaveLoadShownWithArgHolder & );
	~BfmeSaveLoadShownWithArgHolder() { if (m_ptr && --m_ptr->m_refCount <= 0) delete m_ptr; }
	BfmeSaveLoadShownWithArgWrapper *m_ptr;
};

class BfmeSaveLoadInitGadgetWrapper : public FunctorWrapperHead
{
public:
	__forceinline BfmeSaveLoadInitGadgetWrapper( const FunctorBinding &binding )
		: m_binding( binding ) {}

	FunctorBinding m_binding;
};

class BfmeSaveLoadInitGadgetHolder
{
public:
	__forceinline BfmeSaveLoadInitGadgetHolder( FunctorBinding binding )
	{
		m_ptr = new BfmeSaveLoadInitGadgetWrapper( binding );
		if( m_ptr )
			++m_ptr->m_refCount;
	}

	BfmeSaveLoadInitGadgetHolder( const BfmeSaveLoadInitGadgetHolder & );
	~BfmeSaveLoadInitGadgetHolder() { if (m_ptr && --m_ptr->m_refCount <= 0) delete m_ptr; }
	BfmeSaveLoadInitGadgetWrapper *m_ptr;
};

class BfmeSaveLoadWindowManager
{
public:
	void bindShownWithArg( const AsciiString &name, void *argument,
		BfmeSaveLoadShownWithArgHolder callback );
};

void rva004628E0( const AsciiString &, BfmeSaveLoadInitGadgetHolder );

class BfmeGameLogicPause
{
public:
	bool isGamePaused();
	void setGamePaused( bool paused, int pauseMode, bool affectMouse );
};

class GameLogic;
extern GameLogic *TheGameLogic;
extern const char *BfmeSaveLoadCallbackNames[];

// EH state 1 calls the list-base destructor at 0x56E160 on this +0x284 member.
// Its 0x44 node has two pointer links; the element payload is 0x3C bytes.
struct Z1Elem0056D960
{
	~Z1Elem0056D960();
	char m_unmodelled[ 0x3C ];
};

typedef _STL::list<Z1Elem0056D960,
	_STL::allocator<Z1Elem0056D960> > BfmeSaveLoadSlotList;

// SaveLoad.apt, retail 0x00104DC0, object 0x288 bytes.
class __declspec( novtable ) BfmeAptScreenSaveLoadConstructorBase
	: public _bfme_AptGameWindow
{
public:
	__forceinline BfmeAptScreenSaveLoadConstructorBase( void *context )
		: _bfme_AptGameWindow( context )
	{
		*(const void ***)this = BfmeAptScreenSaveLoadVftable;
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
		_ReadWriteBarrier();
	}

protected:
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
};

class __declspec( novtable ) __multiple_inheritance BfmeAptScreenSaveLoad
	: public BfmeAptScreenSaveLoadConstructorBase,
	  public BfmeAptFunctorMarker
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
	void _bfme_onInitGadget( const char *name, void *argument, GameWindow *window );
	void _bfme_provide( const char *selector, void *value, bool setting );

private:
	BfmeSaveLoadSlotList m_field284;
};

BfmeAptScreenSaveLoad::BfmeAptScreenSaveLoad( void *context )
	: BfmeAptScreenSaveLoadConstructorBase( context )
{
	if( g_bfmeReadyAG == 0 )
	{
		g_bfmeReadyAG = this;
		BfmeSaveLoadAptRegistry *registry =
			(BfmeSaveLoadAptRegistry *)( (char *)this + 0x218 );

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onInitialized;
			AsciiString name( "AptSaveLoad::OnInitialized" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onClosed;
			AsciiString name( "AptSaveLoad::OnClosed" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onLoad;
			AsciiString name( "AptSaveLoad::Load" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSave;
			AsciiString name( "AptSaveLoad::Save" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onDelete;
			AsciiString name( "AptSaveLoad::Delete" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onBack;
			AsciiString name( "AptSaveLoad::Back" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectCampaign;
			AsciiString name( "AptSaveLoad::SelectCampaign" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectSkirmish;
			AsciiString name( "AptSaveLoad::SelectSkirmish" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onSelectReplay;
			AsciiString name( "AptSaveLoad::SelectReplay" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onConfirmationOk;
			AsciiString name( "AptSaveLoad::ConfirmationOk" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}
		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onConfirmationCancel;
			AsciiString name( "AptSaveLoad::ConfirmationCancel" );
			registry->_bfme_showAptScreen( name,
				FunctorBinding( callback, (FunctorTarget *)this ) );
		}

		int obfValue = bfmeMake_0056E900( 0, 0 );
		while( Rva0056DE40( obfValue, 0xB83453E7 ) != (int)0x993BA311 )
		{
			{
				FunctorMethod callback =
					(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_provide;
				short nameIndex = (short)Rva0056DFC0( obfValue, obfValue );
				AsciiString name( BfmeSaveLoadCallbackNames[ nameIndex ] );
				( (BfmeSaveLoadWindowManager *)g_theWindowManager )
					->bindShownWithArg( name, (void *)(int)(short)Rva0056DFC0( obfValue, obfValue ),
						BfmeSaveLoadShownWithArgHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
			}
			obfValue = bfmeSaveLoadObfuscatedStep( obfValue, 0xBA792210u );
		}

		{
			FunctorMethod callback =
				(FunctorMethod)&BfmeAptScreenSaveLoad::_bfme_onInitGadget;
			AsciiString initGadgets( "AptSaveLoad::InitGadgets" );
			rva004628E0( initGadgets, BfmeSaveLoadInitGadgetHolder( FunctorBinding( callback, (FunctorTarget *)this ) ) );
		}

		m_field260 = ((BfmeGameLogicPause *)TheGameLogic)->isGamePaused();
		((BfmeGameLogicPause *)TheGameLogic)->setGamePaused( true, 2, true );
		m_field280 = *(int *)( (char *)g_theWindowManager + 0x1B8 ) == 0;
		if( m_field280 )
			g_theWindowManager->bfme_showBackground( 1 );
	}
}


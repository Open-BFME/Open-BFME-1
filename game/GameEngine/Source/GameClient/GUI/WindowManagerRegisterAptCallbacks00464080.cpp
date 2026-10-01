// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00464080, 1502 B, SEH frame.  Called from WindowManager::init
// (WindowManagerInit.cpp) through ILT 0x00039F1D, straight after its sibling
// registerAptCallbacks0046FD40.  Registers the built-in gadget callbacks on
// g_rva012F19E8WindowManager (0x012F19E8): the ten gadget class names (retail string
// literals 0x010F7038-0x010F70AC), nine of which share one handler, then
// DisableComponents, EnableComponents and BinkMovieInit.  It then seeds two
// .wnd paths in the map at 0x012F19CC and creates the load screen.
//
// The three registration callees are the pinned ILT thunks 0x00026328
// (registerAptCallback, wrapper vtable 0x010F6F84), 0x00023083 (bindShown,
// wrapper vtable 0x010F6F90) and 0x0003DF14 (_bfme_setAptScreenRef, wrapper
// vtable 0x010F6F9C); the wrappers are the one-dword functor wrappers of
// FunctorBindSlotWrapperCtors.cpp, whose constructors retail inlines here.
// The map subscript is the STLport operator[] at 0x00463D50 (ILT 0x00024EDD);
// the factory is createAptScreenLoadScreen (ILT 0x00015E6F).  The handlers
// are ILT thunks whose identities are not recovered, so they keep their
// address names.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

typedef void (__cdecl *AptCallback)();

class FunctorSlotWrapperHead
{
public:
	FunctorSlotWrapperHead() : m_refCount( 0 ) {}

	virtual void functorSlotWrapperAnchor();

	unsigned int m_refCount;
};

class Rva0045ED70FunctorSlotWrapper : public FunctorSlotWrapperHead
{
public:
	Rva0045ED70FunctorSlotWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class Rva0045EDD0FunctorSlotWrapper : public FunctorSlotWrapperHead
{
public:
	Rva0045EDD0FunctorSlotWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class Rva0045EE10FunctorSlotWrapper : public FunctorSlotWrapperHead
{
public:
	Rva0045EE10FunctorSlotWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class AptMapPreviewFunctorHolder
{
public:
	AptMapPreviewFunctorHolder( AptCallback callback )
	{
		m_ptr = new Rva0045ED70FunctorSlotWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	AptMapPreviewFunctorHolder( const AptMapPreviewFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~AptMapPreviewFunctorHolder() {}

	Rva0045ED70FunctorSlotWrapper *m_ptr;
};

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( AptCallback callback )
	{
		m_ptr = new Rva0045EDD0FunctorSlotWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~Rva0050F8B0FunctorHolder() {}

	Rva0045EDD0FunctorSlotWrapper *m_ptr;
};

class Rva0050F840FunctorHolder
{
public:
	Rva0050F840FunctorHolder( AptCallback callback )
	{
		m_ptr = new Rva0045EE10FunctorSlotWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~Rva0050F840FunctorHolder() {}

	Rva0045EE10FunctorSlotWrapper *m_ptr;
};

class WindowManager
{
public:
	void registerAptCallback( const AsciiString &name,
		AptMapPreviewFunctorHolder callback );
	void bindShown( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );
};

void _bfme_setAptScreenRef( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

// STLport map<AsciiString, Rva00461630Mapped>, declared only as far as the
// out-of-line operator[] this body calls (RvaMapIndexAsciiString.cpp).
namespace _STL
{
template <class T> struct less;
template <class T1, class T2> struct pair;
template <class T> class allocator;
template <class K, class V, class C, class A> class map
{
public:
	V &operator[]( const K &key );
};
}

enum Rva00461630Mapped { Rva00461630MappedZero = 0 };

typedef _STL::map<AsciiString, Rva00461630Mapped, _STL::less<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva00461630Mapped> > > Rva00461630Map;

// Thirteen dwords handed to the load screen factory; only the second is
// non-zero.
struct AptScreenContext00464080
{
	AptScreenContext00464080()
		: m_word00( 0 ), m_word04( 0 ), m_word08( 0 ), m_word0C( 0 ),
		  m_word10( 0 ), m_word14( 0 ), m_word18( 0 ), m_word1C( 0 ),
		  m_word20( 0 ), m_word24( 0 ), m_word28( 0 ), m_word2C( 0 ),
		  m_word30( 0 ) {}

	unsigned int m_word00;
	unsigned int m_word04;
	unsigned int m_word08;
	unsigned int m_word0C;
	unsigned int m_word10;
	unsigned int m_word14;
	unsigned int m_word18;
	unsigned int m_word1C;
	unsigned int m_word20;
	unsigned int m_word24;
	unsigned int m_word28;
	unsigned int m_word2C;
	unsigned int m_word30;
};

void * __stdcall createAptScreenLoadScreen( void *context );

extern WindowManager *g_rva012F19E8WindowManager;
extern Rva00461630Map g_rva012F19CCMap;
extern void *g_rva012F198CLoadScreen;

extern void j_0000ed59();
extern void j_00031980();
extern void j_00049c47();
extern void j_0003dca3();
extern void j_00029b63();

void registerAptCallbacks00464080()
{
	{
		AsciiString name( "GameWindow" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "HorzSlider" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "ComboBox" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "ImageComboBox" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "CheckBox" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "TextEntry" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "ListBox" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "PushButton" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "BinkMovie" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_0000ed59 );
	}
	{
		AsciiString name( "View3D" );
		g_rva012F19E8WindowManager->registerAptCallback( name, j_00031980 );
	}
	{
		AsciiString name( "DisableComponents" );
		g_rva012F19E8WindowManager->bindShown( name, j_00049c47 );
	}
	{
		AsciiString name( "EnableComponents" );
		g_rva012F19E8WindowManager->bindShown( name, j_0003dca3 );
	}
	{
		AsciiString name( "BinkMovieInit" );
		_bfme_setAptScreenRef( name, j_00029b63 );
	}

	g_rva012F19CCMap[ AsciiString( "apt/combobox.wnd" ) ] = Rva00461630MappedZero;
	g_rva012F19CCMap[ AsciiString( "apt/horzslider.wnd" ) ] = Rva00461630MappedZero;

	AptScreenContext00464080 context;
	context.m_word04 = 0x08000000;
	g_rva012F198CLoadScreen = createAptScreenLoadScreen( &context );
}

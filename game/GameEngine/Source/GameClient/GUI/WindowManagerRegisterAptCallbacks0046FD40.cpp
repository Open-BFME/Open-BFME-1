// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0046FD40, 1228 B, SEH frame.  Called from WindowManager::init
// (WindowManagerInit.cpp) through ILT 0x00025086.  Registers eleven Apt
// callbacks on g_theWindowManager (0x012F19E8); the callback names are the
// retail string literals at 0x010F7424-0x010F74D0.  The three registration
// overloads are the pinned ILT thunks 0x00023083 (bindShown, wrapper vtable
// 0x010F6F90), 0x0003A0BC (bindShownWithArg, wrapper vtable 0x010F7348) and
// 0x00026328 (registerAptCallback, wrapper vtable 0x010F6F84), the same
// wrapper/holder shapes AptGuiFXRegisterCallbacks.cpp and
// AptPalantirRegisterCallbacks.cpp land.  The handlers are ILT thunks whose
// identities are not recovered, so they keep their address names.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

typedef void (__cdecl *AptCallback)();

class AptCallbackHead
{
public:
	AptCallbackHead() : m_refCount( 0 ) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class BannerAptCallbackWrapper : public AptCallbackHead
{
public:
	BannerAptCallbackWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class PalantirPlayerSideWrapper : public AptCallbackHead
{
public:
	PalantirPlayerSideWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class PalantirCallbackWrapper : public AptCallbackHead
{
public:
	PalantirCallbackWrapper( AptCallback callback ) : m_callback( callback ) {}

	AptCallback m_callback;
};

class BannerAptCallbackHolder
{
public:
	BannerAptCallbackHolder( AptCallback callback )
	{
		m_ptr = new BannerAptCallbackWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	BannerAptCallbackHolder( const BannerAptCallbackHolder &other )
		: m_ptr( other.m_ptr ) {}

	~BannerAptCallbackHolder() {}

	BannerAptCallbackWrapper *m_ptr;
};

class PalantirPlayerSideHolder
{
public:
	PalantirPlayerSideHolder( AptCallback callback )
	{
		m_ptr = new PalantirPlayerSideWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	PalantirPlayerSideHolder( const PalantirPlayerSideHolder &other )
		: m_ptr( other.m_ptr ) {}

	~PalantirPlayerSideHolder() {}

	PalantirPlayerSideWrapper *m_ptr;
};

class PalantirCallbackHolder
{
public:
	PalantirCallbackHolder( AptCallback callback )
	{
		m_ptr = new PalantirCallbackWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	PalantirCallbackHolder( const PalantirCallbackHolder &other )
		: m_ptr( other.m_ptr ) {}

	~PalantirCallbackHolder() {}

	PalantirCallbackWrapper *m_ptr;
};

class WindowManager
{
public:
	void registerAptCallback( const BFMERetailAsciiString &name,
		BannerAptCallbackHolder callback );
	void registerPalantirPlayerSide( const BFMERetailAsciiString &name,
		int unknown, PalantirPlayerSideHolder callback );
	void registerPalantirCallback( const BFMERetailAsciiString &name,
		PalantirCallbackHolder callback );
};

extern WindowManager *g_theWindowManager;

extern void j_00026111();
extern void j_000480b3();
extern void j_00002e0f();
extern void j_0000cd5b();
extern void j_00035f5d();
extern void j_00028cb3();
extern void j_000183f4();
extern void j_0004aae8();
extern void j_0001d8a4();
extern void j_00008f71();
extern void j_00003fa8();

void registerAptCallbacks0046FD40()
{
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "MouseSetVisibility" );
		g_theWindowManager->registerAptCallback( name, j_00026111 );
	}
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "CloseWindow" );
		g_theWindowManager->registerAptCallback( name, j_000480b3 );
	}
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "PlaySound" );
		g_theWindowManager->registerAptCallback( name, j_00002e0f );
	}
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "OnClickThroughPress" );
		g_theWindowManager->registerAptCallback( name, j_0000cd5b );
	}
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "OnClickThroughRelease" );
		g_theWindowManager->registerAptCallback( name, j_00035f5d );
	}
	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "SetBackground" );
		g_theWindowManager->registerAptCallback( name, j_00028cb3 );
	}
	{
		BFMERetailAsciiString name( "InGame" );
		g_theWindowManager->registerPalantirPlayerSide( name, 0, j_000183f4 );
	}
	{
		BFMERetailAsciiString name( "DoTrace" );
		g_theWindowManager->registerPalantirPlayerSide( name, 0, j_0004aae8 );
	}
	{
		BFMERetailAsciiString name( "RenderImage" );
		g_theWindowManager->registerPalantirCallback( name, j_0001d8a4 );
	}
	{
		BFMERetailAsciiString name( "RenderImageDisabled" );
		g_theWindowManager->registerPalantirCallback( name, j_00008f71 );
	}
	{
		BFMERetailAsciiString name( "TimerOverlay" );
		g_theWindowManager->registerPalantirCallback( name, j_00003fa8 );
	}
}

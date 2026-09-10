// ?d_00510fa0@@YAXXZ
// partial score=0.84 date=2026-09-10
// Address-derived APT GuiFX initializer, retail 0x00510FA0 (354 bytes).
// The retail strings identify the GuiFX.apt setup and its OnInitialized and
// ToolTipText callback registrations.  No original source spelling is claimed
// for this body; the generated d_00510fa0 name remains its honest identity.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline

#include "../../../../reference/shims/stringinline/StringInline.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString();

	void *m_data;
};

typedef void (__cdecl *AptGuiFxCallback)();

class GuiFxCallbackHead
{
public:
	GuiFxCallbackHead() : m_refCount( 0 ) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class GuiFxInitializedWrapper : public GuiFxCallbackHead
{
public:
	GuiFxInitializedWrapper( AptGuiFxCallback callback ) : m_callback( callback ) {}

	AptGuiFxCallback m_callback;
};

class GuiFxTooltipWrapper : public GuiFxCallbackHead
{
public:
	GuiFxTooltipWrapper( AptGuiFxCallback callback ) : m_callback( callback ) {}

	AptGuiFxCallback m_callback;
};

class BannerAptCallbackHolder
{
public:
	BannerAptCallbackHolder( AptGuiFxCallback callback )
	{
		m_ptr = new GuiFxInitializedWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	BannerAptCallbackHolder( const BannerAptCallbackHolder &other )
		: m_ptr( other.m_ptr ) {}

	~BannerAptCallbackHolder() {}

	GuiFxInitializedWrapper *m_ptr;
};

class AptMapPreviewFunctorHolder
{
public:
	AptMapPreviewFunctorHolder( AptGuiFxCallback callback )
	{
		m_ptr = new GuiFxTooltipWrapper( callback );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	AptMapPreviewFunctorHolder( const AptMapPreviewFunctorHolder &other )
		: m_ptr( other.m_ptr ) {}

	~AptMapPreviewFunctorHolder() {}

	GuiFxTooltipWrapper *m_ptr;
};

class WindowManager
{
public:
	#define WINDOW_MANAGER_SLOT( n ) virtual void windowManagerSlot##n() = 0
	WINDOW_MANAGER_SLOT( 0 ); WINDOW_MANAGER_SLOT( 1 ); WINDOW_MANAGER_SLOT( 2 );
	WINDOW_MANAGER_SLOT( 3 ); WINDOW_MANAGER_SLOT( 4 ); WINDOW_MANAGER_SLOT( 5 );
	WINDOW_MANAGER_SLOT( 6 ); WINDOW_MANAGER_SLOT( 7 ); WINDOW_MANAGER_SLOT( 8 );
	WINDOW_MANAGER_SLOT( 9 ); WINDOW_MANAGER_SLOT( 10 ); WINDOW_MANAGER_SLOT( 11 );
	WINDOW_MANAGER_SLOT( 12 ); WINDOW_MANAGER_SLOT( 13 ); WINDOW_MANAGER_SLOT( 14 );
	#undef WINDOW_MANAGER_SLOT
	virtual int loadAptWindow( AsciiString directory, AsciiString file,
		int unknown1, int unknown2, int unknown3 ) = 0;
	void registerAptCallback( const BFMERetailAsciiString &name,
		BannerAptCallbackHolder callback );
	void registerAptCallback( const BFMERetailAsciiString &name,
		AptMapPreviewFunctorHolder callback );
};

#pragma comment(linker, "/alternatename:?registerAptCallback@WindowManager@@QAEXABVBFMERetailAsciiString@@VBannerAptCallbackHolder@@@Z=?j_00023083@@YAXXZ")
#pragma comment(linker, "/alternatename:?registerAptCallback@WindowManager@@QAEXABVBFMERetailAsciiString@@VAptMapPreviewFunctorHolder@@@Z=?j_00026328@@YAXXZ")

extern WindowManager *g_theWindowManager;
extern int g_guiFxWindowHandle;
extern AsciiString g_guiFxFile;
extern unsigned char g_guiFxLoaded;
extern void construct00510AC0();

// ?d_00510fa0@@YAXXZ
void d_00510fa0()
{
	if( g_theWindowManager == 0 )
		return;

	g_guiFxLoaded = 0;
	g_guiFxWindowHandle = g_theWindowManager->loadAptWindow(
		g_guiFxFile, AsciiString( "GuiFX.apt" ), 1, 0, 11 );

	if( g_theWindowManager != 0 )
	{
		BFMERetailAsciiString name( "AptGuiFX::OnInitialized" );
		g_theWindowManager->registerAptCallback( name,
			BannerAptCallbackHolder(
				reinterpret_cast<AptGuiFxCallback>( 0x004279DF ) ) );
	}

	{
		BFMERetailAsciiString name( "ToolTipText" );
		g_theWindowManager->registerAptCallback( name,
			AptMapPreviewFunctorHolder(
				reinterpret_cast<AptGuiFxCallback>( 0x0043EF8B ) ) );
	}

	construct00510AC0();
}

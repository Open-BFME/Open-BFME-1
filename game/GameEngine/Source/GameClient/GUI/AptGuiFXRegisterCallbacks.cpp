// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
//
// GuiFX.apt window load plus its OnInitialized and ToolTipText callback
// registrations.  Retail strings identify the window and both callbacks.

#include "StringInline.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
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
	void registerAptCallback( const AsciiString &name,
		AptMapPreviewFunctorHolder callback );
};

extern void j_00023083();

extern WindowManager *g_rva012F19E8WindowManager;
extern int g_guiFxWindowHandle;
AsciiString g_guiFxFile( "GuiFX.apt" );
unsigned char g_guiFxLoaded = 0;
extern void construct00510AC0();
extern void j_000279df();
extern void j_0003ef8b();

void registerGuiFXCallbacks00510FA0()
{
	if( g_rva012F19E8WindowManager == 0 )
		return;

	g_guiFxLoaded = 0;
	g_guiFxWindowHandle = g_rva012F19E8WindowManager->loadAptWindow(
		"Apt\\", g_guiFxFile, 1, 0, 11 );

	if( g_rva012F19E8WindowManager != 0 )
	{
		BFMERetailAsciiString name( "AptGuiFX::OnInitialized" );
		typedef void (WindowManager::*Register)( const BFMERetailAsciiString &,
			BannerAptCallbackHolder );
		union { void (*fn)(); Register call; } reg = { j_00023083 };
		( g_rva012F19E8WindowManager->*reg.call )( name,
			BannerAptCallbackHolder(
				j_000279df ) );
	}

	{
		AsciiString name( "ToolTipText" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			AptMapPreviewFunctorHolder(
				j_0003ef8b ) );
	}

	construct00510AC0();
}

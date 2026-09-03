// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// AptPalantir's one-time callback registration.  The callback names and
// handlers are retained from the retail string/data cross-references; the
// address-derived registration thunks are kept as call-site pins until their
// owning WindowManager overloads acquire names.

#include "../../../../reference/shims/stringinline/StringInline.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

typedef void (__cdecl *BannerAptCallback)();

class BannerAptCallbackHolder
{
public:
	BannerAptCallbackHolder( BannerAptCallback callback );

private:
	void *m_callback;
};

struct PalantirFunctorSlot
{
	PalantirFunctorSlot( void *slot ) : m_slot( slot ) {}

	void *m_slot;
};

class PalantirFunctorWrapperHead
{
public:
	PalantirFunctorWrapperHead() : m_refCount( 0 ) {}
	virtual void anchor();

	unsigned int m_refCount;
};

class PalantirCallbackWrapper : public PalantirFunctorWrapperHead
{
public:
	__forceinline PalantirCallbackWrapper( const PalantirFunctorSlot &slot )
		: m_slot( slot ) {}

	PalantirFunctorSlot m_slot;
};

class PalantirCallbackHolder
{
public:
	__forceinline PalantirCallbackHolder( const PalantirFunctorSlot &binding )
	{
		m_ptr = new PalantirCallbackWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	PalantirCallbackWrapper *m_ptr;
};

class PalantirPlayerSideWrapper : public PalantirFunctorWrapperHead
{
public:
	__forceinline PalantirPlayerSideWrapper( const PalantirFunctorSlot &slot )
		: m_slot( slot ) {}

	PalantirFunctorSlot m_slot;
};

class PalantirPlayerSideHolder
{
public:
	__forceinline PalantirPlayerSideHolder( const PalantirFunctorSlot &binding )
	{
		m_ptr = new PalantirPlayerSideWrapper( binding );
		if( m_ptr != 0 )
			m_ptr->m_refCount++;
	}

	PalantirPlayerSideWrapper *m_ptr;
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
	void setupPalantir();
	void registerPalantirCallback( const BFMERetailAsciiString &name,
		PalantirCallbackHolder callback );
	void registerPalantirPlayerSide( const BFMERetailAsciiString &name,
		int unknown, PalantirPlayerSideHolder callback );
};

#pragma comment(linker, "/alternatename:?setupPalantir@WindowManager@@QAEXXZ=?j_00043ad6@@YAXXZ")
#pragma comment(linker, "/alternatename:?registerPalantirCallback@WindowManager@@QAEXABVBFMERetailAsciiString@@VPalantirCallbackHolder@@@Z=?j_00026328@@YAXXZ")
#pragma comment(linker, "/alternatename:?registerPalantirPlayerSide@WindowManager@@QAEXABVBFMERetailAsciiString@@HVPalantirPlayerSideHolder@@@Z=?j_0003a0bc@@YAXXZ")

extern WindowManager *g_theWindowManager;

void d_00565f30()
{
	if( g_theWindowManager == 0 ||
		*reinterpret_cast<volatile unsigned char *>( 0x012F4AFC ) != 0 )
		return;

	int windowIndex = g_theWindowManager->loadAptWindow(
		"Apt\\",
		*reinterpret_cast<AsciiString *>( 0x012F4B00 ), 0, 0, -1 );
	*reinterpret_cast<volatile int *>( 0x012B7D80 ) = windowIndex;
	if( windowIndex == -1 )
		return;

	g_theWindowManager->setupPalantir();

	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnInitialized" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0041F62C ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnClosed" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x00434022 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnAlert" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x004127BA ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnCommand" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x00401942 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnRollOverBttnCommand" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x00420428 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSkillUpgrade" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0043B0C5 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSpell" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0043F6E8 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSpellStore" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x00441597 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnOptions" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x00448C07 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnHeroSelect" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0044A606 ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnSpellBookUIShown" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0042F01D ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnRegionPortraitClosed" );
		g_theWindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( 0x0041CFF3 ) );
	}

	{
		const char *playerSide = *reinterpret_cast<const char **>( 0x012B7D7C );
		BFMERetailAsciiString name( playerSide );
		g_theWindowManager->registerPalantirPlayerSide( name, 0,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x00415253 ) ) );
	}

	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderRadar" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x00444544 ) ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderRadarViewBox" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x00419501 ) ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::ClipRadar" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x0043E4E6 ) ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderMovie" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x0041A0F0 ) ) );
	}
	if( g_theWindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderGlobe" );
		g_theWindowManager->registerPalantirCallback( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( 0x0042D09C ) ) );
	}

	*reinterpret_cast<volatile unsigned char *>( 0x012F4AFD ) = 0;
	*reinterpret_cast<volatile unsigned char *>( 0x012F4AFE ) = 0;
	*reinterpret_cast<volatile unsigned char *>( 0x012B7D84 ) = 1;
	*reinterpret_cast<volatile unsigned char *>( 0x012F4AFC ) = 1;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// AptPalantir's one-time callback registration.  The callback names and
// handlers are retained from the retail string/data cross-references; the
// address-derived registration thunks are named directly at the call sites, as
// retail reaches them through ILT thunks.

#include "../../../../inputs/reference/shims/stringinline/StringInline.h"

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
};

// Retail calls these three registration entry points through ILT thunks, so the
// call sites name the thunks directly instead of a member of WindowManager.
extern void j_00043ad6();
extern void j_00026328();
extern void j_0003a0bc();

extern WindowManager *g_rva012F19E8WindowManager;

// Globals the retail image holds at fixed addresses.  dir32_addresses.csv
// records the names below for these addresses; none of them is a literal
// cast any more, so the linked build resolves them by name.
extern unsigned char g_bfmeFlagMD;					// retail 0x012F4AFC
extern unsigned char g_aptPalantirJewelBrightened;		// retail 0x012F4AFD
extern bool g_bfmeFlagDMc;							// retail 0x012F4AFE
extern const char *volatile g_012B7D7C;	// retail 0x012B7D7C, player-side name; volatile keeps retail's eax load
extern int g_aptPalantirWindow;						// retail 0x012B7D80
extern unsigned char g_aptPalantirInitialized;		// retail 0x012B7D84

// retail 0x012F4B00: ?TheBfmeObject_00C701F0@@3VGen_00C701F0Target@@A
class Gen_00C701F0Target;
extern Gen_00C701F0Target TheBfmeObject_00C701F0;

// Apt callback entry points.  None has a recorded name, so each keeps the
// address in its name rather than a guessed one.
void g_0041F62C();		// retail 0x0041F62C, OnInitialized
void g_00434022();		// retail 0x00434022, OnClosed
void g_004127BA();		// retail 0x004127BA, OnBttnAlert
void g_00401942();		// retail 0x00401942, OnBttnCommand
void g_00420428();		// retail 0x00420428, OnRollOverBttnCommand
void g_0043B0C5();		// retail 0x0043B0C5, OnBttnSkillUpgrade
void g_0043F6E8();		// retail 0x0043F6E8, OnBttnSpell
void g_00441597();		// retail 0x00441597, OnBttnSpellStore
void g_00448C07();		// retail 0x00448C07, OnBttnOptions
void g_0044A606();		// retail 0x0044A606, OnBttnHeroSelect
void g_0042F01D();		// retail 0x0042F01D, OnSpellBookUIShown
void g_0041CFF3();		// retail 0x0041CFF3, OnRegionPortraitClosed
void g_00415253();		// retail 0x00415253, player-side functor
void g_00444544();		// retail 0x00444544, RenderRadar functor
void g_00419501();		// retail 0x00419501, RenderRadarViewBox functor
void g_0043E4E6();		// retail 0x0043E4E6, ClipRadar functor
void g_0041A0F0();		// retail 0x0041A0F0, RenderMovie functor
void g_0042D09C();		// retail 0x0042D09C, RenderGlobe functor

void d_00565f30()
{
	if( g_rva012F19E8WindowManager == 0 || g_bfmeFlagMD != 0 )
		return;

	int windowIndex = g_rva012F19E8WindowManager->loadAptWindow(
		"Apt\\",
		*reinterpret_cast<AsciiString *>( &TheBfmeObject_00C701F0 ), 0, 0, -1 );
	g_aptPalantirWindow = windowIndex;
	if( windowIndex == -1 )
		return;

	typedef void (WindowManager::*SetupPalantirFn)();
	union { void (*fn)(); SetupPalantirFn call; } setupPalantir = { j_00043ad6 };
	(g_rva012F19E8WindowManager->*setupPalantir.call)();

	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnInitialized" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0041F62C ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnClosed" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_00434022 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnAlert" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_004127BA ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnCommand" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_00401942 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnRollOverBttnCommand" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_00420428 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSkillUpgrade" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0043B0C5 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSpell" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0043F6E8 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnSpellStore" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_00441597 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnOptions" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_00448C07 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnBttnHeroSelect" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0044A606 ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnSpellBookUIShown" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0042F01D ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::OnRegionPortraitClosed" );
		g_rva012F19E8WindowManager->registerAptCallback( name,
			reinterpret_cast<BannerAptCallback>( &g_0041CFF3 ) );
	}

	{
		const char *playerSide = g_012B7D7C;
		BFMERetailAsciiString name( playerSide );
		typedef void (WindowManager::*RegisterPalantirPlayerSideFn)(
			const BFMERetailAsciiString &, int, PalantirPlayerSideHolder );
		union { void (*fn)(); RegisterPalantirPlayerSideFn call; }
			registerPalantirPlayerSide = { j_0003a0bc };
		(g_rva012F19E8WindowManager->*registerPalantirPlayerSide.call)( name, 0,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_00415253 ) ) );
	}

	typedef void (WindowManager::*RegisterPalantirCallbackFn)(
		const BFMERetailAsciiString &, PalantirCallbackHolder );
	union { void (*fn)(); RegisterPalantirCallbackFn call; }
		registerPalantirCallback = { j_00026328 };

	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderRadar" );
		(g_rva012F19E8WindowManager->*registerPalantirCallback.call)( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_00444544 ) ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderRadarViewBox" );
		(g_rva012F19E8WindowManager->*registerPalantirCallback.call)( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_00419501 ) ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::ClipRadar" );
		(g_rva012F19E8WindowManager->*registerPalantirCallback.call)( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_0043E4E6 ) ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderMovie" );
		(g_rva012F19E8WindowManager->*registerPalantirCallback.call)( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_0041A0F0 ) ) );
	}
	if( g_rva012F19E8WindowManager )
	{
		BFMERetailAsciiString name( "AptPalantir::RenderGlobe" );
		(g_rva012F19E8WindowManager->*registerPalantirCallback.call)( name,
			PalantirFunctorSlot( reinterpret_cast<void *>( &g_0042D09C ) ) );
	}

	g_aptPalantirJewelBrightened = 0;
	g_bfmeFlagDMc = false;
	g_aptPalantirInitialized = 1;
	g_bfmeFlagMD = 1;
}

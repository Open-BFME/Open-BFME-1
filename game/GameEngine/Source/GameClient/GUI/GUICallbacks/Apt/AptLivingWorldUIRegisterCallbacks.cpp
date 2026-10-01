// ?registerAptLivingWorldUICallbacks@@YAXXZ
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x0051AB40, 805 B, SEH frame. Registers the Living-World Apt
// screen's callbacks with WindowManager, twin of the simpler
// registerBannerAptCallbacks (BannerUIRegisterCallbacks.cpp) but with an
// extra leading block that computes g_aptLivingWorldWindowIndex (0x012F49A8) from a
// five-argument WindowManager virtual (slot 0xF, two by-value strings built in the
// argument area) fed to the bfmeMakeEYA thunk retail calls at ILT 0x0000FC4A; then
// eight registerAptCallback(name, holder) calls for
// the AptLivingWorldUI::On* callback family (string literals at
// 0x01105c98-0x01105dec confirm the class/callback names).

template <class T> class StringBase
{
protected:
	StringBase( const StringBase &other );
	StringBase( const T *text );
	T *m_data;
};

class BFMERetailAsciiString : public StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other ) : StringBase<char>( other ) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
};

typedef void (__cdecl *BannerAptCallback)();

class BannerAptCallbackHolder
{
public:
	BannerAptCallbackHolder( BannerAptCallback callback );

private:
	void *m_callback;
};

class WindowManager
{
public:
	virtual void _pad00(); virtual void _pad01(); virtual void _pad02();
	virtual void _pad03(); virtual void _pad04(); virtual void _pad05();
	virtual void _pad06(); virtual void _pad07(); virtual void _pad08();
	virtual void _pad09(); virtual void _pad10(); virtual void _pad11();
	virtual void _pad12(); virtual void _pad13(); virtual void _pad14();
	virtual int resolveAptWindow( BFMERetailAsciiString prefix,
		BFMERetailAsciiString name, int a, int b, int c );	// vtable slot 0xF (+0x3c)

	void registerAptCallback( const BFMERetailAsciiString &name,
		BannerAptCallbackHolder callback );
};

extern WindowManager *g_rva012F19E8WindowManager;
extern bool g_aptLivingWorldGuardA;			// 0x0012F499D
extern bool g_aptLivingWorldGuardB;			// 0x0012F499C
extern BFMERetailAsciiString g_aptLivingWorldCachedName;	// 0x0012F49A0
extern void *g_aptLivingWorldWindowIndex;		// 0x0012F49A8 (g_bfmeV1064)

void *bfmeMakeEYA( unsigned int low, unsigned int high );

extern void __cdecl bfmeAptLivingWorldOnInitialized();
extern void __cdecl bfmeAptLivingWorldOnRegionPopupOpen();
extern void __cdecl bfmeAptLivingWorldOnRegionPopupClosed();
extern void __cdecl bfmeAptLivingWorldOnRollOverRegionBttn();
extern void __cdecl bfmeAptLivingWorldOnRollOutRegionBttn();
extern void __cdecl bfmeAptLivingWorldOnPressRegionBttn();
extern void __cdecl bfmeAptLivingWorldOnReleaseRegionBttn();
extern void __cdecl bfmeAptLivingWorldOnRegionConqueredNoticeClosed();

void registerAptLivingWorldUICallbacks()
{
	if( !g_aptLivingWorldGuardA && g_rva012F19E8WindowManager )
	{
		g_aptLivingWorldGuardA = false;
		g_aptLivingWorldGuardB = false;
		int idx = g_rva012F19E8WindowManager->resolveAptWindow( BFMERetailAsciiString( "Apt\\" ),
			BFMERetailAsciiString( g_aptLivingWorldCachedName ), 0, 0, -1 );
		g_aptLivingWorldWindowIndex = bfmeMakeEYA( idx, idx );

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnInitialized" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnInitialized );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnRegionPopupOpen" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnRegionPopupOpen );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnRegionPopupClosed" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnRegionPopupClosed );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnRollOverRegionBttn" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnRollOverRegionBttn );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnRollOutRegionBttn" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnRollOutRegionBttn );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnPressRegionBttn" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnPressRegionBttn );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnReleaseRegionBttn" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnReleaseRegionBttn );
		}

		if( g_rva012F19E8WindowManager )
		{
			BFMERetailAsciiString name( "AptLivingWorldUI::OnRegionConqueredNoticeClosed" );
			g_rva012F19E8WindowManager->registerAptCallback( name, bfmeAptLivingWorldOnRegionConqueredNoticeClosed );
		}
	}
}

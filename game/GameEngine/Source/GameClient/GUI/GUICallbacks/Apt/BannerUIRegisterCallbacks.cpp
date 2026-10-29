// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME registers two global callbacks for BannerUI.apt once the window manager
// exists.  The callback holder owns the retail ref-counted wrapper created by
// the one-argument constructor at 0x0085FC20.

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

class WindowManager
{
public:
	void registerAptCallback( const BFMERetailAsciiString &name,
		BannerAptCallbackHolder callback );
};

// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
extern bool g_bannerAptCallbacksRegistered;
extern void __cdecl bannerAptOnInitialized();
extern void __cdecl bannerAptOnButton();

void registerBannerAptCallbacks()
{
	if( g_theWindowManager && !g_bannerAptCallbacksRegistered )
	{
		{
			BFMERetailAsciiString name( "AptBannerUI::OnInitialized" );
			g_theWindowManager->registerAptCallback(
				name, bannerAptOnInitialized );
		}

		if( g_theWindowManager )
		{
			BFMERetailAsciiString name( "AptBannerUI::OnBttnBanner" );
			g_theWindowManager->registerAptCallback(
				name, bannerAptOnButton );
		}

		g_bannerAptCallbacksRegistered = true;
	}
}

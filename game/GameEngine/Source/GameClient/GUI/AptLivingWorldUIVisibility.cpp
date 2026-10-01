// BFME's Living World screen is an APT window.  These paired helpers preserve
// the screen's one-time show/hide state around WindowManager's indexed API.

class WindowManager
{
public:
	bool showAptWindow( int index );
	bool hideAptWindow( int index );
};

// Retail global 0x012F19E8. EA's own name for this pointer; see
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp for the definition.
extern WindowManager *g_rva012F19E8WindowManager;
extern bool g_aptLivingWorldVisible;
extern bool g_aptLivingWorldClosing;
extern int g_aptLivingWorldWindowIndex;

int AptLivingWorldWindowIndex( int low, int high );

void showAptLivingWorldUI()
{
	if( !g_aptLivingWorldVisible )
	{
		g_rva012F19E8WindowManager->showAptWindow(
			AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex,
				g_aptLivingWorldWindowIndex ) );
		g_aptLivingWorldVisible = true;
	}
}

void hideAptLivingWorldUI()
{
	if( g_aptLivingWorldVisible )
	{
		g_rva012F19E8WindowManager->hideAptWindow(
			AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex,
				g_aptLivingWorldWindowIndex ) );
		g_aptLivingWorldVisible = false;
		g_aptLivingWorldClosing = false;
	}
}

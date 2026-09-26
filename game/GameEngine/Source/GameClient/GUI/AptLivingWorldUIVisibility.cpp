// BFME's Living World screen is an APT window.  These paired helpers preserve
// the screen's one-time show/hide state around WindowManager's indexed API.

class WindowManager
{
public:
	bool showAptWindow( int index );
	bool hideAptWindow( int index );
};

extern WindowManager *g_theWindowManager;
extern bool g_aptLivingWorldVisible;
extern bool g_aptLivingWorldClosing;
extern int g_aptLivingWorldWindowIndex;

int AptLivingWorldWindowIndex( int low, int high );

void showAptLivingWorldUI()
{
	if( !g_aptLivingWorldVisible )
	{
		g_theWindowManager->showAptWindow(
			AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex,
				g_aptLivingWorldWindowIndex ) );
		g_aptLivingWorldVisible = true;
	}
}

void hideAptLivingWorldUI()
{
	if( g_aptLivingWorldVisible )
	{
		g_theWindowManager->hideAptWindow(
			AptLivingWorldWindowIndex( g_aptLivingWorldWindowIndex,
				g_aptLivingWorldWindowIndex ) );
		g_aptLivingWorldVisible = false;
		g_aptLivingWorldClosing = false;
	}
}

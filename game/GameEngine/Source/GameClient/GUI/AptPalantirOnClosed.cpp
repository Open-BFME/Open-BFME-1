// callees.py 0x00563980 32: the call goes through ILT 0x0002144A to
// 0x00467460, matched as WindowManager::hideAptWindow(int)
// (WindowManager_hideAptWindow.cpp); the result is unused here.
class WindowManager
{
public:
	bool hideAptWindow( int window );
};

// Retail global at 0x012F19E8.
extern WindowManager *g_rva012F19E8WindowManager;

// Retail 0x012B7D80; canonical spelling `int g_aptPalantirWindow`
// (?g_aptPalantirWindow@@3HA), defined in
// game/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptPalantir.cpp.
extern int g_aptPalantirWindow;
extern unsigned char g_aptPalantirClosed;
extern unsigned char g_aptPalantirCloseRequested;

// ?aptPalantirOnClosed@@YAXXZ
void aptPalantirOnClosed()
{
	g_rva012F19E8WindowManager->hideAptWindow( g_aptPalantirWindow );
	g_aptPalantirClosed = 1;
	g_aptPalantirCloseRequested = 0;
}

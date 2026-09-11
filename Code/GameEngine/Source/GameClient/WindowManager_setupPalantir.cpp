// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// WindowManager::setupPalantir, retail 0x00467510, 112 bytes.
// AptPalantirRegisterCallbacks.cpp calls this method after loading the
// Palantir screen.  The method loads the shared Background.apt movie and
// stores its window index at WindowManager+0x1C0.

#include "../../../../reference/shims/stringinline/StringInline.h"

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
	void setupPalantir();

private:
	unsigned char m_unmodelled[ 0x1BC ];
	int m_backgroundWindow;
};

void WindowManager::setupPalantir()
{
	m_backgroundWindow = loadAptWindow(
		"Apt\\", "Background.apt", 1, 0, -1 );
}

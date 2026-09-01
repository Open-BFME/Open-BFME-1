// ?hideAptWindow@WindowManager@@QAE_NH@Z
// partial score=0.98 date=2026-08-31
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// BFME's Living World screen is an APT window.  These paired helpers preserve
// the screen's one-time show/hide state around WindowManager's indexed API.
#include "Common/UnicodeString.h"

struct RGBColor;

class Mouse
{
public:
	void setCursorTooltip( UnicodeString tooltip, int delay, const RGBColor *color, float width );
};

extern Mouse *TheMouse;

struct AptWindowSlot
{
	char m_unmodelled[ 0x10 ];
	unsigned int m_flags;
};

class WindowManager
{
public:
	bool showAptWindow( int index );
	bool hideAptWindow( int index );

private:
	bool hideAptWindowInternal( int index );
	char m_unmodelled[ 0xA8 ];
	AptWindowSlot m_aptWindows[ 12 ];
};

extern WindowManager *g_theWindowManager;
extern bool g_aptLivingWorldVisible;
extern bool g_aptLivingWorldClosing;
extern int g_aptLivingWorldWindowIndex;

int AptLivingWorldWindowIndex( int low, int high );

bool WindowManager::hideAptWindow( int index )
{
	if( static_cast<unsigned int>( index ) >= 12 )
		return false;

	AptWindowSlot &window = m_aptWindows[ index ];
	if( TheMouse )
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, 0, 0, 1.0f );

	if( !(window.m_flags & 2) )
		return false;

	return hideAptWindowInternal( index );
}

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

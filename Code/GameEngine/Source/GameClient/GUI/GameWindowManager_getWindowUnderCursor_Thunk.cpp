// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/gamewindowlist /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport

#include "PreRTS.h"
#include "Common/Debug.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindow.h"

// ?getWindowUnderCursor@GameWindowManager@@UAEPAVGameWindow@@HH_N@Z
GameWindow *GameWindowManager::getWindowUnderCursor( Int x, Int y, Bool ignoreEnabled )
{
	if( m_mouseCaptor )
	{
		return m_mouseCaptor->winPointInChild( x, y, ignoreEnabled );
	}

	if( m_grabWindow )
	{
		return m_grabWindow->winPointInChild( x, y, ignoreEnabled );
	}

	GameWindow *window = NULL;
	if( m_modalHead && m_modalHead->window )
	{
		return m_modalHead->window->winPointInChild( x, y, ignoreEnabled );
	}
	else
	{
		for( window = m_windowList; window; window = window->m_next )
		{
			if( BitTest( window->m_status, WIN_STATUS_ABOVE ) &&
					!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
					x >= window->m_region.lo.x &&
					x <= window->m_region.hi.x &&
					y >= window->m_region.lo.y &&
					y <= window->m_region.hi.y )
			{
				if( BitTest( window->m_status, WIN_STATUS_ENABLED ) || ignoreEnabled )
				{
					window = window->winPointInChild( x, y, ignoreEnabled );
					break;
				}
			}
		}

		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( !BitTest( window->m_status, WIN_STATUS_ABOVE |
																				 WIN_STATUS_BELOW |
																				 WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y )
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED ) || ignoreEnabled )
					{
						window = window->winPointInChild( x, y, ignoreEnabled );
						break;
					}
				}
			}
		}

		if( window == NULL )
		{
			for( window = m_windowList; window; window = window->m_next )
			{
				if( BitTest( window->m_status, WIN_STATUS_BELOW ) &&
						!BitTest( window->m_status, WIN_STATUS_HIDDEN ) &&
						x >= window->m_region.lo.x &&
						x <= window->m_region.hi.x &&
						y >= window->m_region.lo.y &&
						y <= window->m_region.hi.y )
				{
					if( BitTest( window->m_status, WIN_STATUS_ENABLED ) || ignoreEnabled )
					{
						window = window->winPointInChild( x, y, ignoreEnabled );
						break;
					}
				}
			}
		}
	}

	if( window )
	{
		if( BitTest( window->m_status, WIN_STATUS_NO_INPUT ) )
		{
			window = NULL;
		}
		else if( ignoreEnabled && !( BitTest( window->m_status, WIN_STATUS_ENABLED ) ) )
		{
			window = NULL;
		}
	}

	return window;
}

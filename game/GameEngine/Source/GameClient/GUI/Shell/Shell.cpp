// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: Shell.cpp ////////////////////////////////////////////////////////////////////////////////
// Author: Colin Day, September 2001
// Description: Shell menu representations
///////////////////////////////////////////////////////////////////////////////////////////////////

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/RandomValue.h"
#include "GameClient/Shell.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GameWindowTransitions.h"
#include "GameClient/IMEManager.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ShellMenuScheme.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"

#include <rts/profile.h>

// PUBLIC DATA ////////////////////////////////////////////////////////////////////////////////////
Shell *TheShell = NULL;  ///< the shell singleton definition

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

// PUBLIC FUNCTIONS ///////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/Shell_ctor_Thunk.cpp
// ??0Shell@@QAE@XZ present-unmatched
Shell::Shell( void )
{
	Int i;

	m_screenCount = 0;
	for( i = 0; i < MAX_SHELL_STACK; i++ )
		m_screenStack[ i ] = NULL;

	m_pendingPush = FALSE;
	m_pendingPop = FALSE;
	m_pendingPushName.set( "" );
	m_isShellActive = TRUE;
	m_shellMapOn = FALSE;
	m_background = NULL;
	m_clearBackground = FALSE;
	m_animateWindowManager = NEW AnimateWindowManager;
	m_schemeManager = NEW ShellMenuSchemeManager;
	m_saveLoadMenuLayout = NULL;
	m_popupReplayLayout = NULL;
	//Added By Sadullah Nader
	//Initializations
	m_optionsLayout = NULL;
	m_screenCount = 0;
	//

}  // end Shell

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/Shell/ShellDestructor.cpp
// ??1Shell@@UAE@XZ present-unmatched
Shell::~Shell( void )
{
	WindowLayout *newTop = top();
	while(newTop)
	{
		popImmediate();
		newTop = top();
	}

	if(m_background)
	{
		m_background->destroyWindows();
		m_background->deleteInstance();
		m_background = NULL;
	}

	if(m_animateWindowManager)
		delete m_animateWindowManager;
	m_animateWindowManager = NULL;

	if(m_schemeManager)
		delete m_schemeManager;
	m_schemeManager = NULL;

	// delete the save/load menu if present
	if( m_saveLoadMenuLayout )
	{

		m_saveLoadMenuLayout->destroyWindows();
		m_saveLoadMenuLayout->deleteInstance();
		m_saveLoadMenuLayout = NULL;

	}  //end if

	// delete the replay save menu if present
	if( m_popupReplayLayout )
	{

		m_popupReplayLayout->destroyWindows();
		m_popupReplayLayout->deleteInstance();
		m_popupReplayLayout = NULL;

	}  //end if

	// delete the options menu if present.
	if (m_optionsLayout != NULL) {
		m_optionsLayout->destroyWindows();
		m_optionsLayout->deleteInstance();
		m_optionsLayout = NULL;
	}

}  // end ~Shell

//-------------------------------------------------------------------------------------------------
/** Initialize the shell system */
//-------------------------------------------------------------------------------------------------
// ?init@Shell@@UAEXXZ
// BFME: no ShellMenuScheme.ini path strings in retail; scheme manager init is a no-op.
// Body is if (m_schemeManager) m_schemeManager->init(); @ 0x57F0A0 (vtable slot 1).
void Shell::init( void )
{
	if( m_schemeManager )
		m_schemeManager->init();

}  // end init

//-------------------------------------------------------------------------------------------------
/** Reset the shell system to a clean state just as though init had
	* just been called and ready to re-use */
//-------------------------------------------------------------------------------------------------
// ?reset@Shell@@UAEXXZ present-unmatched
void Shell::reset( void )
{
	
	if (TheIMEManager)
		TheIMEManager->detatch();

	// pop all screens
	while( m_screenCount )
		pop();

	m_animateWindowManager->reset();

}  // end reset

//-------------------------------------------------------------------------------------------------
/** Update shell system cycle.  All windows are updated that are on the stack, starting
	* with the top layout and progressing to the bottom one */
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
/** Find a screen via the .wnd script filename loaded */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/GUI/Shell/Shell_findScreenByFilename.cpp
// ?findScreenByFilename@Shell@@QAEPAVWindowLayout@@VAsciiString@@@Z present-unmatched
WindowLayout *Shell::findScreenByFilename( AsciiString filename )
{

	if (filename.isEmpty())
		return NULL;

	// search screen list
	WindowLayout *screen;
	Int i;
	for( i = 0; i < MAX_SHELL_STACK; i++ )
	{

		screen = m_screenStack[ i ];
		if( screen && filename.compareNoCase(screen->getFilename()) == 0 )
			return screen;

	}  // end for i

	return NULL;

}  // end findScreenByFilename

//-------------------------------------------------------------------------------------------------
/** Hide or unhide all window layouts loaded */
//-------------------------------------------------------------------------------------------------
// byte-exact reconstruction: game/GameEngine/Source/GameClient/Shell_hide.cpp
// ?hide@Shell@@QAEX_N@Z present-unmatched
void Shell::hide( Bool hide )
{
	Int i;

	for( i = 0; i < MAX_SHELL_STACK; i++ )
		if( m_screenStack[ i ] )
			m_screenStack[ i ]->hide( hide );

	if (TheIMEManager)
		TheIMEManager->detatch();

}  // end hide

//-------------------------------------------------------------------------------------------------
/** Push layout onto shell */
//-------------------------------------------------------------------------------------------------
// Shell::push (retail 0x00580080) is matched in Shell_push_Thunk.cpp.

//-------------------------------------------------------------------------------------------------
/** Pop top layout of the stack.  Note that we don't actually do the pop right here,
	* we instead run the layout shutdown.  That shutdown() in turn notifies the
	* shell when the shutdown is complete and at that point we do the actual pop */
//-------------------------------------------------------------------------------------------------
namespace
{
// BFME's WindowLayout callback is a virtual slot at +0x0c.  The public ZH
// declaration exposes the callback member instead, so keep this reconstruction
// TU-local and use the retail vtable order established by the body.
class BfmeShellPopWindowLayout
{
public:
	virtual void slot00( void * ) = 0;
	virtual void slot04( void * ) = 0;
	virtual void slot08( void * ) = 0;
	virtual void runShutdown( void * ) = 0;
};

// BFME's IME manager detatch entry is the tenth virtual slot (+0x28).
class BfmeShellPopIMEManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void detatch() = 0;
};

struct BfmeShellPopLayout
{
	unsigned char padding[0x4d];
	Bool pendingPop;
};
}

void Shell::pop( void )
{
	WindowLayout *screen = top();
	if(TheGameSpyInfo)
			GameSpyCloseAllOverlays();


	// sanity
	if( screen == NULL )
		return;

#ifdef DEBUG_LOGGING
	DEBUG_LOG(("Shell:pop() - stack was\n"));
	for (Int i=0; i<m_screenCount; ++i)
	{
		DEBUG_LOG(("\t\t%s\n", m_screenStack[i]->getFilename().str()));
	}
#endif

	// set a pop as pending
	reinterpret_cast<BfmeShellPopLayout *>(this)->pendingPop = TRUE;

	//
	// run the shutdown function for the screen, when it's actually shutdown it
	// will call Shell::shutdownComplete(), where the pending pop will be seen
	// and the actual pop will occur
	//
	Bool immediatePop = FALSE;
	reinterpret_cast<BfmeShellPopWindowLayout *>(screen)->runShutdown( &immediatePop );

	if (TheIMEManager)
		reinterpret_cast<BfmeShellPopIMEManager *>(TheIMEManager)->detatch();

}  // end pop

//-------------------------------------------------------------------------------------------------
/** When you need to immediately pop a screen off the stack use this method.  It
	* gives the screen the opportunity to shutdown and tells the shutdown
	* method that an immediate pop is going to take place.  When control returns
	* from the shutdown() for the screen, it will be immediately popped off
	* the stack */
//-------------------------------------------------------------------------------------------------
// ?popImmediate@Shell@@QAEXXZ present-unmatched
void Shell::popImmediate( void )
{
	WindowLayout *screen = top();

	// sanity
	if( screen == NULL )
		return;

#ifdef DEBUG_LOGGING
	DEBUG_LOG(("Shell:popImmediate() - stack was\n"));
	for (Int i=0; i<m_screenCount; ++i)
	{
		DEBUG_LOG(("\t\t%s\n", m_screenStack[i]->getFilename().str()));
	}
#endif

	// do NOT set pending pop, we are going to force a pop after the shutdown is run
	m_pendingPop = FALSE;

	// run the shutdown
	Bool immediatePop = TRUE;
	screen->runShutdown( &immediatePop );

	// pop the screen of the stack
	doPop( FALSE );

	if (TheIMEManager)
		TheIMEManager->detatch();

}  // end popImmediate

//-------------------------------------------------------------------------------------------------
/** Run the initialize function for the top of the stack just as though it was pushed
	* on the stack.  We want this behavior when we want to act like the top was just
	* pushed on the stack, but it's already there (ie going from in game back to the
	* pre-game shell menus */
//-------------------------------------------------------------------------------------------------
// Shell::showShell: retail body (0x00580150) in Shell_showShell_Thunk.cpp.

// byte-exact reconstruction: game/GameEngine/Source/Common/Shell_showShellMapMethodThunk.cpp
// ?showShellMap@Shell@@QAEX_N@Z present-unmatched
void Shell::showShellMap(Bool useShellMap )
{
	// we don't want any of this to show if we're loading straight into a file
	if(TheGlobalData->m_initialFile.isNotEmpty() || !TheGameLogic )
		return;
	if(useShellMap && TheGlobalData->m_shellMapOn)
	{
		// we're already in a shell game, return
		if(TheGameLogic->isInGame() && TheGameLogic->getGameMode() == GAME_SHELL)
			return;
		// we're in some other kind of game, clear it out foo!
		if(TheGameLogic->isInGame())
			TheMessageStream->appendMessage( GameMessage::MSG_CLEAR_GAME_DATA );

		TheWritableGlobalData->m_pendingFile = TheGlobalData->m_shellMapName;
		InitGameLogicRandom(0);
		GameMessage *msg = TheMessageStream->appendMessage( GameMessage::MSG_NEW_GAME );
		msg->appendIntegerArgument(GAME_SHELL);
		m_shellMapOn = TRUE;
	}
	else
	{
		// we're in a shell game, stop it!
		if(TheGameLogic->isInGame() && TheGameLogic->getGameMode() == GAME_SHELL)
			TheMessageStream->appendMessage( GameMessage::MSG_CLEAR_GAME_DATA );

		// if the shell is active,we need a background
		if(!m_isShellActive)
			return;
		if(!m_background)
			m_background = TheWindowManager->winCreateLayout("Menus/BlankWindow.wnd");
		
		DEBUG_ASSERTCRASH(m_background,("We Couldn't Load Menus/BlankWindow.wnd"));
		m_background->getFirstWindow()->winSetStatus(WIN_STATUS_IMAGE);
		m_background->hide(FALSE);
		if (top())
			top()->bringForward();
		m_shellMapOn = FALSE;
		m_clearBackground = FALSE;
	}
}

//-------------------------------------------------------------------------------------------------
/** Run the shutdown() function for the top of the stack just like we're going to pop
	* it off but DO NOT pop it off the stack.  We want this behavior when leaving the
	* pre-game menus and entering the game and want the shell to still exist and contain
	* the stack information but don't want it to go away */
//-------------------------------------------------------------------------------------------------
// ?hideShell@Shell@@QAEXXZ present-unmatched
void Shell::hideShell( void )
{
	// If we have the 3d background running, mark it to close
	m_clearBackground = TRUE;

	DEBUG_LOG(("Shell:hideShell() - %s\n", (top())?top()->getFilename().str():"no top screen"));

	WindowLayout *layout = top();

	if( layout )
	{
		Bool immediatePop = TRUE;

		layout->runShutdown( &immediatePop );

	}  // end if

	if (TheIMEManager)
		TheIMEManager->detatch();

	// Mark that the shell is no longer up.
	m_isShellActive = FALSE;

}  // end hideShell

//-------------------------------------------------------------------------------------------------
/** Return the top layout on the stack */
//-------------------------------------------------------------------------------------------------
WindowLayout *Shell::top( void )
{

	// emtpy stack
	if( m_screenCount == 0 )
		return NULL;

	// top layout is at count index
	return m_screenStack[ m_screenCount - 1 ];

}  // end top

// PRIVATE FUNCTIONS //////////////////////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------
/** Add screen to our list */
//-------------------------------------------------------------------------------------------------
void Shell::linkScreen( WindowLayout *screen )
{

	// sanity
	if( screen == NULL )
		return;

	// check to see if at top already
	if( m_screenCount == MAX_SHELL_STACK )
	{

		DEBUG_CRASH(( "No room in shell stack for screen\n" ));
		return;

	}  // end if

	// add to array at top index
	m_screenStack[ m_screenCount++ ] = screen;

}  // end linkScreen

//-------------------------------------------------------------------------------------------------
/** Remove screen from our list */
//-------------------------------------------------------------------------------------------------
void Shell::unlinkScreen( WindowLayout *screen )
{
	
	// sanity
	if( screen == NULL )
		return;

	DEBUG_ASSERTCRASH( m_screenStack[ m_screenCount - 1 ] == screen, 
										 ("Screen not on top of stack\n") );

	// remove reference to screen and decrease count
	if( m_screenStack[ m_screenCount - 1 ] == screen )
		m_screenStack[ --m_screenCount ] = NULL;

}  // end unlinkScreen

//-------------------------------------------------------------------------------------------------
/** Actually do the work for a push */
//-------------------------------------------------------------------------------------------------
// ?doPush@Shell@@IAEXVAsciiString@@@Z present-unmatched
void Shell::doPush( AsciiString layoutFile )
{
	if(TheGameSpyInfo)
			GameSpyCloseAllOverlays();
	WindowLayout *newScreen;
	
	// create new layout and load from window manager
	newScreen = TheWindowManager->winCreateLayout( layoutFile );
	DEBUG_ASSERTCRASH( newScreen != NULL, ("Shell unable to load pending push layout\n") );

	// link screen to the top
	linkScreen( newScreen );

	if (TheIMEManager)
		TheIMEManager->detatch();

	// run the init function automatically
	newScreen->runInit( NULL );
	newScreen->bringForward();


}  // end doPush

//-------------------------------------------------------------------------------------------------
/** Actually do the work for a pop */
//-------------------------------------------------------------------------------------------------
// ?doPop@Shell@@IAEX_N@Z present-unmatched
void Shell::doPop( Bool impendingPush )
{
	WindowLayout *currentTop = top();

	// there better be a top of the stack since we're popping
	DEBUG_ASSERTCRASH( currentTop, ("Shell: No top of stack and we want to pop!\n") );
		
	// remove this screen from our list
	unlinkScreen( currentTop );

	// delete all the windows in the screen
	currentTop->destroyWindows();

	// release the screen object back to the memory pool
	currentTop->deleteInstance();

	// run the init for the new top of the stack if present
	WindowLayout *newTop = top();
	if( newTop && !impendingPush )
	{
		newTop->runInit( NULL );
		//newTop->bringForward();
	}

	if (TheIMEManager)
		TheIMEManager->detatch();

}  // end doPop

//-------------------------------------------------------------------------------------------------
/** This is called when a layout has finished its shutdown process.  Layouts are
	* shutdown when a new screen is being pushed on the stack, or when we are
	* popping the current screen off the top of the stack.  It is here that we
	* can look for any pending push or pop operations and actually do them
	*
	* NOTE: It is possible for the screen parameter to be NULL when we are
	*       short circuiting the shutdown logic because there is no layout
	*				to actually shutdown (ie, the stack is empty and we push) */
//-------------------------------------------------------------------------------------------------
// Shell::shutdownComplete (retail 0x0057FD80) is matched in Shell_shutdownComplete.cpp.


void Shell::registerWithAnimateManager( GameWindow *win, AnimTypes animType, Bool needsToFinish, UnsignedInt delayMS)
{
	if(!m_animateWindowManager)
	{
		DEBUG_CRASH(("We called registerWithAnimateManager and we don't have an Animate Manager created"));
		return;
	}
	if (*(const Bool*)((const char*)TheGlobalData + 0xBC4))
		m_animateWindowManager->registerGameWindow(win,animType,needsToFinish, 500,delayMS);
}

Bool Shell::isAnimFinished( void )
{
	// check the new way also.
	if (!TheTransitionHandler->isFinished())
		return FALSE;

	if(!m_animateWindowManager)
	{
		DEBUG_CRASH(("We called registerWithAnimateManager and we don't have an Animate Manager created"));
		return TRUE;
	}
	if (*(const Bool*)((const char*)TheGlobalData + 0xBC4))
		return m_animateWindowManager->isFinished();
	else
		return TRUE;
}

void Shell::reverseAnimatewindow( void )
{
	if(!m_animateWindowManager)
	{
		DEBUG_CRASH(("We called registerWithAnimateManager and we don't have an Animate Manager created"));
		return;
	}
	if (*(const Bool*)((const char*)TheGlobalData + 0xBC4))
		m_animateWindowManager->reverseAnimateWindow();
}

void Shell::loadScheme( AsciiString name )
{
	if(!m_schemeManager)
		return;

	m_schemeManager->setShellMenuScheme( name );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
WindowLayout *Shell::getSaveLoadMenuLayout( void )
{
	
	WindowLayout *&layout = *reinterpret_cast<WindowLayout **>(reinterpret_cast<char *>(this) + 0x68);
	// if layout has not been created, create it now
	if( layout == NULL )
	   layout = TheWindowManager->winCreateLayout( AsciiString( "Menus/PopupSaveLoad.wnd" ) );

	// sanity
	DEBUG_ASSERTCRASH( layout, ("Unable to create save/load menu layout\n") );

	// return the layout
	return layout;

}  // end getSaveLoadMenuLayout

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
WindowLayout *Shell::getPopupReplayLayout( void )
{
	
	WindowLayout *&layout = *reinterpret_cast<WindowLayout **>(reinterpret_cast<char *>(this) + 0x6c);
	// if layout has not been created, create it now
	if( layout == NULL )
	   layout = TheWindowManager->winCreateLayout( AsciiString( "Menus/PopupReplay.wnd" ) );

	// sanity
	DEBUG_ASSERTCRASH( layout, ("Unable to create replay save menu layout\n") );

	// return the layout
	return layout;

}  // end getSaveLoadMenuLayout

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?getOptionsLayout@Shell@@QAEPAVWindowLayout@@_N@Z present-unmatched
WindowLayout *Shell::getOptionsLayout( Bool create )
{
	// if layout has not been created, create it now
	if ((m_optionsLayout == NULL) && (create == TRUE))
	{
		m_optionsLayout = TheWindowManager->winCreateLayout( AsciiString( "Menus/OptionsMenu.wnd" ) );

		// sanity
		DEBUG_ASSERTCRASH( m_optionsLayout, ("Unable to create options menu layout\n") );
	}

	// return the layout
	return m_optionsLayout;
} // end getOptionsLayout

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
// ?destroyOptionsLayout@Shell@@QAEXXZ present-unmatched
void Shell::destroyOptionsLayout() {
	if (m_optionsLayout != NULL) {
		m_optionsLayout->destroyWindows();
		m_optionsLayout->deleteInstance();
		m_optionsLayout = NULL;
	}
}

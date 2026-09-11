// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

class WindowLayout;

class GameWindowTransitionsHandler
{
public:
	void remove( AsciiString groupName, Bool skipPending );
	void setGroup( AsciiString groupName, Bool immediate );
	Bool isFinished( void );
};

class Glo00EF3330
{
public:
	void h004893E0( void );
	void h00489410( void );
};

class GameWindowTransitionsHandler;
extern GameWindowTransitionsHandler *TheTransitionHandler;

class TransitionHandlerGuard
{
public:
	TransitionHandlerGuard()
	{
		if ( TheTransitionHandler )
			((Glo00EF3330 *)TheTransitionHandler)->h004893E0();
	}

	~TransitionHandlerGuard()
	{
		if ( TheTransitionHandler )
			((Glo00EF3330 *)TheTransitionHandler)->h00489410();
	}
};

class Shell
{
public:
	Bool isAnimFinished( void );
	void shutdownComplete( WindowLayout *layout, Bool impendingPush );
};

extern Shell *TheShell;

void copyReplay( void );
void deleteReplay( void );

static Bool justEntered = false;
static Int initialGadgetDelay = 2;
static Bool callCopy = false;
static Bool callDelete = false;
static Bool isShuttingDown = false;

// ?ReplayMenuUpdate@@YAXPAVWindowLayout@@PAX@Z
void ReplayMenuUpdate( WindowLayout *layout, void *userData )
{
	if ( justEntered )
	{
		if ( initialGadgetDelay == 1 )
		{
			TransitionHandlerGuard guard;
			TheTransitionHandler->remove( "MainMenuDefaultMenuLogoFade", false );
			TheTransitionHandler->setGroup( "ReplayMenuFade", false );
			initialGadgetDelay = 2;
			justEntered = false;
		}
		else
			--initialGadgetDelay;
	}

	if ( callCopy )
		copyReplay();
	if ( callDelete )
		deleteReplay();
	if ( isShuttingDown && TheShell->isAnimFinished() && TheTransitionHandler->isFinished() )
		TheShell->shutdownComplete( layout, false );
}

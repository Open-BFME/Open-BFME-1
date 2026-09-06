// ?parseCommandButton@CommandSet@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.62 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// Open-BFME7: INI field parser at 0x0049C7C0 (207 B): Zero Hour's
// CommandSet::parseCommandButton (reference/CnC_Generals_Zero_Hour/GeneralsMD/
// Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp) with the
// DEBUG_CRASH/INI_INVALID_DATA pair folded into a single thrown INIException,
// following the CrateTemplate/ThingTemplate replace-module pattern: the format
// string at VA 0x10FB7C4 is "Unknown command '%s' found in command set. File:
// %s Line: %d\n" (BFME's own wording/argument order, not ZH's [LINE:...] form).
// TheControlBar (VA 0x012F33F8) is already matched; findCommandButton is its
// declared lookup.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton;

class ControlBar
{
public:
	const CommandButton *findCommandButton( const AsciiString &name );
};

extern ControlBar *TheControlBar;

class CommandSet
{
public:
	static void parseCommandButton( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseCommandButton@CommandSet@@SAXPAVINI@@PAX1PBX@Z
void CommandSet::parseCommandButton( INI *ini, void *instance, void *store, const void *userData )
{
	const char *token = ini->getNextToken();

	const CommandButton *commandButton = TheControlBar->findCommandButton( AsciiString( token ) );
	if( commandButton == NULL )
	{
		throw INIException( 3, "Unknown command '%s' found in command set. File: %s Line: %d\n",
			token, ini->getFilename().str(), ini->getLineNum() );
	}

	const CommandButton **buttonArray = (const CommandButton **)store;
	Int buttonIndex = (Int)userData;
	buttonArray[ buttonIndex ] = commandButton;
}

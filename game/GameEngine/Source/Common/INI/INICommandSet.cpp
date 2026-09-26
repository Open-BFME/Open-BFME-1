// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The CommandSet block.
//
// This address, 0x004A2150, was recorded as ?newCommandButtonOverride@ControlBar@@
// against a MASM dump. It is not: the INI block registry binds the "CommandSet"
// keyword to it, and the function calls the already-matched
// ControlBar::findNonConstCommandSet -- so it is the CommandSet parser, and the
// registry is ground truth for what a keyword parses.
//
// TheControlBar is loaded once into a local and reused for all three calls, which
// is why the source spells it that way.
#include "PreRTS.h"
#include "Common/INI.h"
#include "Common/INIException.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandSet
{
public:
	static const FieldParse m_commandSetFieldParseTable[];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
	friend class INI;
private:
	CommandSet *findNonConstCommandSet( const AsciiString &name );
protected:
	CommandSet *newCommandSet( const AsciiString &name );
	CommandSet *newCommandSetOverride( CommandSet *setToOverride );
};

extern ControlBar *TheControlBar;

// BFME keeps m_loadType at INI+0x08 (docs/ini_loading.md).
static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

// The byte a freshly created set gets when the load is making overrides.
struct RetailOverridable
{
	char m_unknown00[ 0x08 ];
	Bool m_isOverride;			// 0x08
};

void INI::parseCommandSetDefinition( INI* ini )
{
	AsciiString name;
	name = ini->getNextToken();

	ControlBar *controlBar = TheControlBar;
	CommandSet *commandSet = controlBar->findNonConstCommandSet( name );
	if( commandSet == NULL )
	{
		commandSet = controlBar->newCommandSet( name );
		if( retailLoadType( ini ) == INI_LOAD_CREATE_OVERRIDES )
			reinterpret_cast<RetailOverridable *>( commandSet )->m_isOverride = TRUE;
	}
	else if( retailLoadType( ini ) != INI_LOAD_CREATE_OVERRIDES )
	{
		throw INIException( 3, "Duplicate commandset %s found!", name.str() );
	}
	else
	{
		commandSet = controlBar->newCommandSetOverride( commandSet );
	}

	ini->initFromINI( commandSet, CommandSet::m_commandSetFieldParseTable );
}

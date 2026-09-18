// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/iniexception /Ireference/shims/ini_noinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The CommandButton block, the sibling of CommandSet next door. Same three
// helpers, same shape: find, create if absent, take an override if the load
// makes them.
//
// Its override callee was the thing that kept this block unclaimed. It calls
// 0x00027CC3, which the ledger had recorded as ?newOverride@WeaponStore@@ -- a
// WeaponStore method reached with TheControlBar in ecx. What settled it was the
// CommandSet parser: once that was placed at 0x004A2150 by the INI registry, its
// own override branch turned out to call 0x00049ADA, so the two override
// creators are a pair and the one here belongs to CommandButton.
#include "PreRTS.h"
#include "Common/INI.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	static const FieldParse m_commandButtonFieldParseTable[];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
	friend class INI;
protected:
	CommandButton *findNonConstCommandButton( const AsciiString &name );
	CommandButton *newCommandButton( const AsciiString &name );
	CommandButton *newCommandButtonOverride( CommandButton *buttonToOverride );
};

extern ControlBar *TheControlBar;

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

struct RetailOverridable
{
	char m_unknown00[ 0x08 ];
	Bool m_isOverride;			// 0x08
};

void INI::parseCommandButtonDefinition( INI* ini )
{
	AsciiString name( ini->getNextToken() );

	CommandButton *button = TheControlBar->findNonConstCommandButton( name );
	if( button == NULL )
	{
		button = TheControlBar->newCommandButton( name );
		if( retailLoadType( ini ) == INI_LOAD_CREATE_OVERRIDES )
			reinterpret_cast<RetailOverridable *>( button )->m_isOverride = TRUE;
	}
	else if( retailLoadType( ini ) == INI_LOAD_CREATE_OVERRIDES )
	{
		button = TheControlBar->newCommandButtonOverride( button );
	}

	ini->initFromINI( button, CommandButton::m_commandButtonFieldParseTable );
}

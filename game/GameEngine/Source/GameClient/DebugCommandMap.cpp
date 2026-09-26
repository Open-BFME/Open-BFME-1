// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The DebugCommandMap block. It reads the entry name and throws it away, parses
// a full entry into a local, and then discards that too -- so in a release build
// the block validates its own syntax and stores nothing. The retail code really
// is this: getNextToken with the result unused, initFromINI into stack space,
// and two UnicodeString destructors on the way out.
//
// Field names and offsets are the retail table at 0x0110E570
// (docs/ini_schema.md). Nothing writes 0x00-0x07, so that stays a pad.
#include "PreRTS.h"
#include "Common/INI.h"

struct DebugCommandMapEntry
{
	char m_unknown00[ 0x08 ];		// 0x00  no INI field writes here
	Int m_key;						// 0x08  Key
	Int m_transition;				// 0x0c  Transition
	Int m_modifiers;				// 0x10  Modifiers
	Int m_useableIn;				// 0x14  UseableIn
	Int m_category;					// 0x18  Category
	UnicodeString m_description;	// 0x1c  Description
	UnicodeString m_displayName;	// 0x20  DisplayName

	static const FieldParse m_fieldParseTable[];
};

void parseDebugCommandMap( INI *ini )
{
	ini->getNextToken();

	DebugCommandMapEntry entry;
	ini->initFromINI( &entry, DebugCommandMapEntry::m_fieldParseTable );
}

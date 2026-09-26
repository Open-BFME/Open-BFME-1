// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The OptionGroup block. It is unusual among the parsers here: instead of
// handing initFromINI a static table, it builds a four-entry FieldParse array on
// the stack, one entry per value type the group can hold.
//
//   Bool  Int  String  Real
//
// So an OptionGroup body is a list of typed values rather than a fixed set of
// named settings, which is why the table has to be constructed per call. The
// four parse procs are stored as data, not called, so they are DIR32 slots the
// verifier fills in from the target; the four tokens are real string literals
// and are string-ref verified.
//
// The two globals have no recoverable names. The first is an AsciiString holding
// the group name for the duration of the parse -- set on entry, cleared to ""
// on exit -- and the second is the object the values are parsed into.
#include "PreRTS.h"
#include "Common/INI.h"

extern AsciiString TheOptionGroupName;		// 0x012ED60C
extern void *TheOptionGroupTarget;			// 0x012ED604

void parseOptionGroup( INI *ini )
{
	TheOptionGroupName = ini->getNextToken();

	const FieldParse myFieldParse[] =
	{
		{ "Bool",		INI::parseBool,			NULL, 0 },
		{ "Int",		INI::parseInt,			NULL, 0 },
		{ "String",		INI::parseAsciiString,	NULL, 0 },
		{ "Real",		INI::parseReal,			NULL, 0 },
		{ NULL,			NULL,					NULL, 0 }
	};

	ini->initFromINI( TheOptionGroupTarget, myFieldParse );

	TheOptionGroupName = "";
}

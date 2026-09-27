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
// named settings, which is why the table has to be constructed per call. Each
// entry reads a name and then its value, so the procs are the named-definition
// parsers at 0x000940F0/0x000941D0/0x00094300/0x00094470 (retail's table
// reaches them through their ILT thunks), not INI's scalar parsers.
//
// The two globals have no recoverable names. The first is an AsciiString holding
// the group name for the duration of the parse -- set on entry, cleared to ""
// on exit -- and the second is the object the values are parsed into.
#include "PreRTS.h"
#include "Common/INI.h"

class Rva000940F0 { public: static void parseDefinition( INI *ini, void *instance, void *store, const void *userData ); };
class Rva000941D0 { public: static void parseDefinition( INI *ini, void *instance, void *store, const void *userData ); };
class Rva00094300 { public: static void parseDefinition( INI *ini, void *instance, void *store, const void *userData ); };
class Rva00094470 { public: static void parseDefinition( INI *ini, void *instance, void *store, const void *userData ); };

extern AsciiString TheOptionGroupName;		// 0x012ED60C
extern void *TheOptionGroupTarget;			// 0x012ED604

void parseOptionGroup( INI *ini )
{
	TheOptionGroupName = ini->getNextToken();

	const FieldParse myFieldParse[] =
	{
		{ "Bool",		Rva000940F0::parseDefinition,	NULL, 0 },
		{ "Int",		Rva000941D0::parseDefinition,	NULL, 0 },
		{ "String",		Rva00094300::parseDefinition,	NULL, 0 },
		{ "Real",		Rva00094470::parseDefinition,	NULL, 0 },
		{ NULL,			NULL,								NULL, 0 }
	};

	ini->initFromINI( TheOptionGroupTarget, myFieldParse );

	TheOptionGroupName = "";
}

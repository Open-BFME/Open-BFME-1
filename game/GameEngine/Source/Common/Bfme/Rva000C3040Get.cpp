// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

// stlport
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata VA 0x0109FC28, 80 bytes: the VictorySystem field-parse table
// that matched iniParseVictorySystemDefinition (0x000C3060) passes to
// INI::initFromINI. Four INI::parseReal (0x00C52B20) entries and a zero
// terminator; offsets read from the image.
extern const FieldParse g_0109FC28[] =
{
	{ "CellSize",				INI::parseReal,	NULL, 0x0C },
	{ "ScalePerLogicFrame",		INI::parseReal,	NULL, 0x14 },
	{ "SubtractPerLogicFrame",	INI::parseReal,	NULL, 0x18 },
	{ "CellBonusRadius",		INI::parseReal,	NULL, 0x20 },
	{ NULL,						NULL,			NULL, 0 }
};

void *Rva000C3040Get()
{
	return (void *)g_0109FC28;
}

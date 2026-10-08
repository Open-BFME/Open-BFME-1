// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x0109FBC8, 96 bytes: the FactionVictoryData field-parse table
// iniParseFactionVictoryDefinition (0x000C31B0) hands to initFromINI. Five
// INI::parseReal entries (offsets read from the image) and the zero terminator.
// The owning struct is not recovered, so the name stays address-derived.
extern const FieldParse g_0109FBC8[] =
{
	{ "AllyDeathScaleFactor",	INI::parseReal,	0,	0x04 },
	{ "EnemyKillScaleFactor",	INI::parseReal,	0,	0x08 },
	{ "VictoryThreshold",		INI::parseReal,	0,	0x10 },
	{ "MapToCellVictoryRatio",	INI::parseReal,	0,	0x0C },
	{ "MajorUnitValue",			INI::parseReal,	0,	0x14 },
	{ 0,						0,				0,	0 }
};

void *Rva000C3050Get()
{
	return (void *)g_0109FBC8;
}

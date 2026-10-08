// cl: /O2 /GR- /EHsc- /DNDEBUG /DWIN32 /D_WINDOWS /MD /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Address-derived reconstruction of the six-byte fixed-address getter at 0x007E3AB0.
// The ZH Common/INI.h declares FieldParse and the INI::parse* statics the
// table names.
#include "PreRTS.h"
#include "Common/INI.h"

// Retail .rdata 0x0112CBD8, 96 bytes: the five-entry video record
// field-parse table (Filename, Comment, HasSubtitles, Volume, IsDefault)
// and its zero terminator; tokens, parsers and offsets read from the image.
// The getter below returns its address; the owning record is not proven,
// so the table keeps its address-derived name.
extern const FieldParse g_0112CBD8[];
const FieldParse g_0112CBD8[] =
{
	{ "Filename",	INI::parseAsciiString,	0,	0x0 },
	{ "Comment",	INI::parseAsciiString,	0,	0x8 },
	{ "HasSubtitles",	INI::parseBool,	0,	0xC },
	{ "Volume",	INI::parsePercentToReal,	0,	0x10 },
	{ "IsDefault",	INI::parseBool,	0,	0x14 },
	{ 0,	0,	0,	0 }
};

void *Rva007E3AB0FixedAddress()
{
	return reinterpret_cast<void *>( const_cast<FieldParse *>( g_0112CBD8 ) );
}

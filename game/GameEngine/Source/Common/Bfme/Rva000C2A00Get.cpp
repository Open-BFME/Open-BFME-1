// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/INI/INI.h"

// Retail .rdata 0x0108132C, 32 bytes: the one-entry field-parse table
// INIWaterTextureList.cpp hands to initFromINI ("Texture" through
// INI::parseAsciiStringVectorAppend at offset 8) and its zero terminator,
// read from the image. The getter below returns its address.
extern const FieldParse g_0108132C[];
const FieldParse g_0108132C[] =
{
	{ "Texture",	INI::parseAsciiStringVectorAppend,	0,	0x8 },
	{ 0,	0,	0,	0 }
};

void *Rva000C2A00Get()
{
	return const_cast<FieldParse *>(g_0108132C);
}

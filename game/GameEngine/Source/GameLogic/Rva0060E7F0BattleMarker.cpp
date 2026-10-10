// cl: /O2 /DNDEBUG /DWIN32 /MD /EHs
// Retail 0x0060E7F0 (135 B): format a BattleMarker name and return it by value
// (the caller supplies the hidden sret destination).  The caller-visible symbol
// is kept RVA-derived because no named owner for this generated entry is proven.

#include <new>

extern "C" __declspec(dllimport) int __cdecl sprintf(char *, const char *, ...);

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

extern "C" AsciiString rva0060E7F0(int marker)
{
	char buffer[64];
	sprintf(buffer, "BattleMarker%04d", marker);
	AsciiString value(buffer);
	return AsciiString(value);
}

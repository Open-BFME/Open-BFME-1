// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AsciiString scalar-deleting destructor at retail RVA
// 0x00062240 (30 bytes).  The existing matched AsciiString destructor at
// 0x0005EE90 is reached through ILT 0x0000D828; ascii_string.h/.cpp provide
// the authentic class and its StringBase<char> cleanup implementation.

#include "ascii_string.h"

void Force_AsciiString_Deleting_Destructor(AsciiString *value)
{
	delete value;
}

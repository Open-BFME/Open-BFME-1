// Retail 0x00467270 formats an APT level path into the supplied AsciiString.

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


void rva00467270(AsciiString *text, int level)
{
	text->format("/_level%d", level);
}

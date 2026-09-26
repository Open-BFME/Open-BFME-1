// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x0068E5A0, __cdecl, 111 bytes.  Reads one NUL-terminated ASCII field
// out of a packed byte stream into a StringBase<char> and returns the position
// after the terminator, clamping to `end` when one is supplied.  Its only
// caller is inside 0x0068EF70, in the block that decodes BFME's serialized LAN
// game-info payload, but nothing there names it, so the name describes the
// body rather than claiming a retail identity.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef unsigned char UnsignedByte;

extern "C" UnsignedByte *readAsciiFieldFromBuffer(UnsignedByte *buffer,
	StringBase<char> *out, UnsignedByte *end)
{
	out->set((const char *)0x0107301c, 0);

	if (end != 0)
	{
		if (buffer >= end || end - buffer < 1)
			return buffer;
	}

	while (*buffer != 0)
	{
		if (end != 0 && buffer >= end)
			return end;

		char ch = (char)*buffer;
		out->concat(&ch, 1);
		++buffer;
	}

	return buffer + 1;
}

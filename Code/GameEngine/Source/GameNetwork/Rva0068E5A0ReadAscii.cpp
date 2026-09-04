// cl: /DNDEBUG /MD /EHs-c-

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

typedef unsigned char UnsignedByte;

extern "C" UnsignedByte *rva68e5a0(UnsignedByte *buffer,
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

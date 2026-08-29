// ?bfmeReadByte_0068D990@@YAPAEPAE0PBE@Z
// partial score=0.95 date=2026-08-29
// Open-BFME5: guarded single-byte cursor read, retail 0x0068D990.

#include <string.h>

#pragma intrinsic(memcpy)

unsigned char *bfmeReadByte_0068D990(unsigned char *cursor,
	unsigned char *out, const unsigned char *end)
{
	if (end)
	{
		if (cursor > end)
			return cursor;

		if (cursor + 1 > end)
			return cursor;
	}

	memcpy(out, cursor, 1);

	return cursor + 1;
}

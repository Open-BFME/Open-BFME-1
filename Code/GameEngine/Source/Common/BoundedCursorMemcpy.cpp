#include <string.h>
#pragma intrinsic(memcpy)

char *rva68d7e0(char *cursor, char *out, unsigned n, char *limit)
{
	if (limit != 0 && (cursor > limit || cursor + n > limit))
		return cursor;

	memcpy(out, cursor, n);
	return cursor + n;
}

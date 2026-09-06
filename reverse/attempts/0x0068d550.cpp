// ?rva68d550@@YAPADPAD0I0@Z
// partial score=0.85 date=2026-09-06
#include <string.h>
#pragma intrinsic(memcpy)

char *rva68d550(char *cursor, char *out, unsigned n, char *limit)
{
	if (limit != 0 && (cursor > limit || cursor + n > limit))
		return cursor;

	memcpy(out, cursor, n);
	char *result = cursor + n;
	return result;
}

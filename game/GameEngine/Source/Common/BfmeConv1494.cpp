// Open-BFME5 conversions.

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"

extern "C" unsigned strlen(const char *s);
#pragma intrinsic(strlen)

class BfmeStrVMZ;

extern "C" __declspec(dllimport) char *__cdecl strstr(const char *a, const char *b);

char bfmeGetParamVMZ(const char *hay, const char *key, BfmeStrVMZ *out)
{
	if (hay == 0 || *hay == 0)
		return 0;
	if (key == 0 || *key == 0)
		return 0;

	const char *p = strstr(hay, key);

	if (p == 0)
		return 0;
	if (p != hay && p[-1] != '&')
		return 0;

	p += strlen(key);
	if (*p != '=')
		return 0;
	++p;

	const char *e = p;

	while (*e != 0 && *e != '&')
		++e;
	if (e == p)
	{
		((StringBase<char> *)out)->clear();
		return 1;
	}
	((StringBase<char> *)out)->set(p, e - p);
	return 1;
}

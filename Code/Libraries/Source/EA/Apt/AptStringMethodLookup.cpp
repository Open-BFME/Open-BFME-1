// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
#include <string.h>

struct R4Word
{
	const char *name;
	int value;
};

int bfmeSkipVE(const unsigned char *text, int length);

extern const R4Word g008A9710[];
extern const signed char g008A9710lookup[];

const R4Word *Rva008A9710(const char *str, unsigned int len)
{
	if (len <= 12 && len >= 5)
	{
		register int key = bfmeSkipVE((const unsigned char *)str, (int)len);
		if (key <= 0x16 && key >= 0)
		{
			register int index = g008A9710lookup[key];
			if (index >= 0)
			{
				register const char *s = g008A9710[index].name;
				if (*str == *s && !strcmp(str + 1, s + 1))
					return &g008A9710[index];
			}
			else if (index < -13)
			{
				register int offset = -1 - 13 - index;
				register const R4Word *wordptr = (g008A9710 + 13) + g008A9710lookup[offset];
				register const R4Word *wordendptr = wordptr - g008A9710lookup[offset + 1];
				while (wordptr < wordendptr)
				{
					register const char *s = wordptr->name;
					if (*str == *s && !strcmp(str + 1, s + 1))
						return wordptr;
					wordptr++;
				}
			}
		}
	}
	return 0;
}

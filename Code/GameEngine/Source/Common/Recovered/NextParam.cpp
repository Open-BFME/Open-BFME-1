// ?nextParam@@YAPADPAD0@Z
// The Zero Hour WinMain tokenizer names this body. Retail stores its static
// cursor at 0x012ED264 and loads strpbrk through 0x013594C4.
#include <string.h>

typedef char *(__cdecl *StrpbrkFunction)(const char *, const char *);

char *nextParam(char *newSource, char *seps)
{
	static char *source = NULL;
	if (newSource)
	{
		source = newSource;
	}
	if (!source)
	{
		return NULL;
	}

	char *first = source;
	if (first)
	{
		StrpbrkFunction find = *(StrpbrkFunction *)0x013594C4;
		char *firstSep = find(first, seps);
		char firstChar[2] = {0, 0};
		if (firstSep == first)
		{
			firstChar[0] = *first;
			while (*first == firstChar[0]) first++;
		}

		char *end;
		if (firstChar[0])
			end = find(first, firstChar);
		else
			end = find(first, seps);

		if (end)
		{
			source = end+1;
			*end = 0;
			if (!*source)
				source = NULL;
		}
		else
		{
			source = NULL;
		}

		if (first && !*first)
			first = NULL;
	}

	return first;
}

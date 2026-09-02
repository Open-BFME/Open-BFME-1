// cl: /DNDEBUG /MD /EHsc
#include <ctype.h>

static const char *skipIdent(const char *s)
{
	char ch = *s;
	if (ch)
	{
		do
		{
			if (!isalnum(ch) && *s != '_')
				break;
			ch = *++s;
		} while (ch);
	}
	return s;
}

const char *skipIdentAnchor(const char *s)
{
	return skipIdent(s);
}

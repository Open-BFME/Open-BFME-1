// ?skipSeps@@YAPADPADPBD@Z
// partial score=0.85 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Stash of char skipSeps (0x00887720). Inner strchr loop is byte-exact;
// the match path still retests *s (59B vs retail 54B).

static char *skipSeps(char *p, const char *seps);
static char *skipNonSeps(char *p, const char *seps);

class StringBaseSkipHost
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;

	bool nextToken(StringBaseSkipHost *tok, const char *seps);
};

bool StringBaseSkipHost::nextToken(StringBaseSkipHost *tok, const char *seps)
{
	Header *data = m_data;
	if (data == 0)
		return false;
	if (data->length == 0)
		return false;
	if (tok == this)
		return false;
	if (seps == 0)
		seps = " \n\r\t";
	char *start = skipSeps(data->data, seps);
	char *end = skipNonSeps(start, seps);
	return end > start;
}

static char *skipSeps(char *p, const char *seps)
{
	while (*p)
	{
		const char *s = seps;
		while (*s && *s != *p)
			++s;
		if (!*s)
			return p;
		++p;
	}
	return p;
}

static char *skipNonSeps(char *p, const char *seps)
{
	char c = *p;
	if (!c)
		return p;
	for (;;)
	{
		char first = *seps;
		const char *s = seps;
		if (!first)
			goto advance;
		char sc = first;
		while (sc != c)
		{
			sc = *++s;
			if (!sc)
				goto advance;
		}
		return p;
	advance:
		c = *++p;
		if (!c)
			return p;
	}
}

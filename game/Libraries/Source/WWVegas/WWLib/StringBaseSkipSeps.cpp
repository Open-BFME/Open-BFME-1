// cl: /DNDEBUG /MD /EHs-c-
//
// File-static skipSeps / skipNonSeps for StringBase::nextToken.
// Retail calls them with the string in EAX and the separator set in EDI:
// MSVC 7.1's private convention for a static whose every call site it can
// see. The nextToken-shaped caller below is what establishes that
// convention; it is not claimed.

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

// retail 0x00887720 (54 bytes): same shape as skipNonSeps -- the first
// separator is read into its own local, copied into the walking character,
// and the do/while leaves through a goto on a match so the loop re-enters at
// the compare and the miss exit falls into the return.
static char *skipSeps(char *p, const char *seps)
{
	char c = *p;
	while (c)
	{
		char first = *seps;
		const char *s = seps;
		if (!first)
			return p;
		char sc = first;
		do
		{
			if (sc == c)
				goto advance;
			sc = *++s;
		} while (sc);
		return p;
advance:
		c = *++p;
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

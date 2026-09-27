// cl: /DNDEBUG /MD /EHs-c-
//
// File-static skipSeps / skipNonSeps for StringBase::nextToken.
// Retail calls them with the string in EAX and the separator set in EDI:
// MSVC 7.1's private convention for a static whose every call site it can
// see: StringBase<char>::nextToken below.

static char *skipSeps(char *p, const char *seps);
static char *skipNonSeps(char *p, const char *seps);

#include <string.h>
#include "string_base.h"

// StringBase<char>::nextToken (retail 0x008880E0) lives here, beside the
// file-static helpers, because only a caller in the same translation unit
// gets their private register convention.
bool StringBase<char>::nextToken(StringBase<char> *tok, const char *seps)
{
	if (m_data == 0 || m_data->length == 0 || tok == this)
		return false;
	if (seps == 0)
		seps = " \n\r\t";
	char *start = skipSeps(&m_data->data[0], seps);
	char *end = skipNonSeps(start, seps);
	if (end > start)
	{
		int len = end - start;
		char *tmp = tok->getBufferForRead(len);
		memcpy(tmp, start, len);
		tmp[len] = 0;
		set(end, (m_data ? m_data->length : 0) - (int)(end - &m_data->data[0]));
		return true;
	}
	releaseBuffer();
	tok->releaseBuffer();
	return false;
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

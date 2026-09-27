// cl: /DNDEBUG /MD /EHs-c-
//
// File-static wchar skipSeps / skipNonSeps for StringBase<wchar_t>::nextToken.
// Retail calls them with the string in EAX and the separator set in EBX.

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps);
static unsigned short *skipNonSepsW(unsigned short *p, const unsigned short *seps);

#include <string.h>
#include "string_base.h"

// StringBase<wchar_t>::nextToken (retail 0x008889B0) lives here, beside the
// file-static helpers, because only a caller in the same translation unit
// gets their private register convention.
bool StringBase<wchar_t>::nextToken(StringBase<wchar_t> *tok, const wchar_t *seps)
{
	if (m_data == 0 || m_data->length == 0 || tok == this)
		return false;
	if (seps == 0)
		seps = L" \n\r\t";
	wchar_t *start = skipSepsW(&m_data->data[0], seps);
	wchar_t *end = skipNonSepsW(start, seps);
	if (end > start)
	{
		int len = end - start;
		wchar_t *tmp = tok->getBufferForRead(len);
		memcpy(tmp, start, len * sizeof(wchar_t));
		tmp[len] = 0;
		set(end, (m_data ? m_data->length : 0) - (int)(end - &m_data->data[0]));
		return true;
	}
	releaseBuffer();
	tok->releaseBuffer();
	return false;
}

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps)
{
	unsigned short c = *p;
	if (!c)
		return p;
	while (c)
	{
		unsigned short first = *seps;
		const unsigned short *s = seps;
		if (!first)
			return p;
		unsigned short sc = first;
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

static unsigned short *skipNonSepsW(unsigned short *p, const unsigned short *seps)
{
	unsigned short c = *p;
	if (!c)
		return p;
	for (;;)
	{
		unsigned short first = *seps;
		const unsigned short *s = seps;
		if (!first)
			goto advance;
		unsigned short sc = first;
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

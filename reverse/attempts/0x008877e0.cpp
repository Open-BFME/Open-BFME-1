// ?skipSepsW@@YAPAGPAGPBG@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
//
// File-static wchar skipSeps / skipNonSeps for StringBase<wchar_t>::nextToken.
// Retail calls them with the string in EAX and the separator set in EBX.

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps);
static unsigned short *skipNonSepsW(unsigned short *p, const unsigned short *seps);

class StringBaseSkipHostW
{
public:
	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		unsigned short data[1];
	};

	Header *m_data;

	bool nextToken(StringBaseSkipHostW *tok, const unsigned short *seps);
};

bool StringBaseSkipHostW::nextToken(StringBaseSkipHostW *tok, const unsigned short *seps)
{
	Header *data = m_data;
	if (data == 0)
		return false;
	if (data->length == 0)
		return false;
	if (tok == this)
		return false;
	static const unsigned short kDefault[] = { ' ', '\n', '\r', '\t', 0 };
	if (seps == 0)
		seps = kDefault;
	unsigned short *start = skipSepsW(data->data, seps);
	unsigned short *end = skipNonSepsW(start, seps);
	return end > start;
}

static unsigned short *skipSepsW(unsigned short *p, const unsigned short *seps)
{
	unsigned short c = *p;
	if (!c)
		return p;
	for (;;)
	{
		unsigned short first = *seps;
		const unsigned short *s = seps;
		if (!first)
			return p;
		unsigned short sc = first;
		while (sc != c)
		{
			sc = *++s;
			if (!sc)
				return p;
		}
		c = *++p;
		if (!c)
			return p;
	}
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

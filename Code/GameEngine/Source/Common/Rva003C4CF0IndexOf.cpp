// cl: /DNDEBUG /MD /EHsc
// Retail 0x003C4CF0: address-derived index lookup over a two-pointer int span.

struct Rva003C4CF0Span
{
	int *begin;
	int *end;
};

// ?indexOf@@YGHPAURva003C4CF0Span@@H@Z
int __stdcall indexOf(Rva003C4CF0Span *span, int value)
{
	unsigned i = 0;
	unsigned count = (unsigned)(span->end - span->begin);
	for (; i < count; ++i)
	{
		if (value == span->begin[i])
			return (int)i;
	}
	return -1;
}

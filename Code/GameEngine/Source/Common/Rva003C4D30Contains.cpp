// cl: /DNDEBUG /MD /EHsc
// Retail 0x003C4D30: address-derived contains helper recovered from the
// pointer span layout and complete loop/control-flow boundary.

struct Rva003C4D30Span
{
	int *begin;
	int *end;
};

// ?contains@@YG_NPAURva003C4D30Span@@H@Z
bool __stdcall contains(Rva003C4D30Span *span, int value)
{
	unsigned count = (unsigned)(span->end - span->begin);
	for (unsigned i = 0; i < count; ++i)
	{
		if (span->begin[i] == value)
			return true;
	}
	return false;
}

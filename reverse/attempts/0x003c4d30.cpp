// ?contains@@YG_NPAURva003C4D30Span@@H@Z
// partial score=0.88 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Rva003C4D30 contains, retail 0x003C4D30, 56 bytes.
// Size-exact pointer+index span walk; register-mirror edx/ecx for cursor vs index.

struct Rva003C4D30Span
{
	int *begin;
	int *end;
};

// ?contains@@YG_NPAURva003C4D30Span@@H@Z
bool __stdcall contains( Rva003C4D30Span * span, int value )
{
	int *cursor = span->begin;
	unsigned count = (unsigned)( span->end - cursor );
	unsigned i;
	for( i = 0; i < count; ++i, ++cursor )
	{
		if( *cursor == value )
			return true;
	}
	return false;
}

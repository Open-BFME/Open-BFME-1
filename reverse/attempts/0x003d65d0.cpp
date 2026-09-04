// ?apply@Rva003D65D0@@QAEHPAXPAUGen003D65D0Flags@@HH@Z
// partial score=0.81 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
//
// Rva003D65D0::apply candidate, retail 0x003D65D0, 139 bytes.
// Partial: 112/139. Gate and helper match; FPU store interleave (m_at08 write
// between fild/fstp of arg2*10 vs arg3*10) resists MSVC 7.1 scheduling.

struct Gen003D65D0Flags
{
	char m_pad00[ 0x0C ];
	unsigned m_flags;
};

bool __cdecl Gen003D65D0Helper( unsigned slot );

class Rva003D65D0
{
public:
	int apply( void * unused0, Gen003D65D0Flags * src, int a, int b );

private:
	char m_pad00[ 0x4 ];
	float *m_at04;
	unsigned m_at08;
};

// ?apply@Rva003D65D0@@QAEHPAXPAUGen003D65D0Flags@@HH@Z
int Rva003D65D0::apply( void * unused0, Gen003D65D0Flags * src, int a, int b )
{
	(void)unused0;
	unsigned flags = src->m_flags;
	unsigned low = flags & 7;
	if( low == 5 || low == 2 || low == 4 )
		return 1;
	if( (unsigned char)( flags >> 21 ) & 1 )
		return 1;
	if( m_at08 == 1 )
	{
		unsigned slot = ( flags >> 6 ) & 0x3F;
		if( Gen003D65D0Helper( slot ) )
			return 1;
	}
	int sa = a * 10;
	float *dst = m_at04;
	int sb = b * 10;
	unsigned slot = ( flags >> 6 ) & 0x3F;
	dst[ 0 ] = (float)sa;
	m_at08 = slot;
	dst = m_at04;
	dst[ 1 ] = (float)sb;
	return 0;
}

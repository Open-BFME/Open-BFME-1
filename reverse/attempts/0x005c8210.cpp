// ?u1FormatPair_005C8210@@YAPAVINI@@PAV1@PAVU1Pair@@@Z
// partial score=0.95 date=2026-09-06
// MSVC 7.1 emits the same field loads and formatter calls, but uses a 66-byte
// volatile-register layout instead of retail's saved EDI layout.

class INI
{
public:
	void u4Finish( int radix );
};

class U1Pair
{
public:
	char m_pad[ 4 ];
	float m_x;
	float m_y;
};

INI *__cdecl u4FormatFloat( INI *ini, double value );

INI *u1FormatPair_005C8210( INI *ini, U1Pair *pair )
{
	U1Pair *other = pair;
	const float *values = &other->m_x;
	float second = values[ 1 ];
	INI *next = u4FormatFloat( ini, values[ 0 ] );
	next->u4Finish( 32 );
	return u4FormatFloat( next, second );
}

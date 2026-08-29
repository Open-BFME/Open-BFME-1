// ?d_000fc5d0@@YAXXZ
// partial score=0.95 date=2026-08-29
// -------------------------------------------------------------------------
// 0x000FC5D0 -- 85 bytes, element 0x10
class Open2Elem0FC5D0
{
public:
	int m_at00;
	int m_at04;
	int m_at08;
	AsciiString m_at0c;
};

// @?Open2Copy0FC5D0@@YAPAVOpen2Elem0FC5D0@@PAV1@00@Z 0x000FC5D0
Open2Elem0FC5D0 *Open2Copy0FC5D0( Open2Elem0FC5D0 *first, Open2Elem0FC5D0 *last,
	Open2Elem0FC5D0 *result )
{
	for( int n = last - first; n > 0; --n )
	{
		*result = *first;
		++first;
		++result;
	}
	return result;
}

// ?d_0028f4d0@@YAXXZ
// partial score=0.96 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x0028F4D0 -- cache the indexed element, or clear the cache.
//
// The index is tested SIGNED against zero and then UNSIGNED against the
// element count (`jl` then `jae`), which is one `>= 0` and one `< size()`
// written as a pair, not a single range test.  Both failures share the tail.

class BfmeListYQ
{
public:
	void bfmePickYQ( void );

	char m_pad[ 0x80 ];
	union
	{
		void **m_begin;
		int m_beginAddress;
	};
	void **m_end;
	char m_pad2[ 4 ];
	void *m_current;
	char m_pad3[ 0x24 ];
	int m_index;
};

// @?bfmePickYQ@BfmeListYQ@@QAEXXZ 0x0028F4D0
void BfmeListYQ::bfmePickYQ( void )
{
	int index = m_index;
	if( index >= 0 )
	{
		int count = ( (int)m_end - m_beginAddress ) >> 2;
		if( (unsigned int)index < count )
		{
			void **begin = *(void ** volatile *)((char *)this + 0x80);
			m_current = begin[ index ];
			return;
		}
	}
	m_current = 0;
}


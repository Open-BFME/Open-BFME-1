// ?d_0028f4d0@@YAXXZ
// partial score=0.96 date=2026-08-29
// ---------------------------------------------------------------------------
// 0x0028F4D0 -- cache the indexed element, or clear the cache.
//
// The index is tested SIGNED against zero and then UNSIGNED against the
// element count (`jl` then `jae`), which is one `>= 0` and one `< size()`
// written as a pair, not a single range test.  Both failures share the tail.

class Rva0028F4D0
{
public:
	void refresh( void );

	char m_pad[ 0x80 ];
	void **m_begin;
	void **m_end;
	char m_pad2[ 4 ];
	void *m_current;
	char m_pad3[ 0x24 ];
	int m_index;
};

// @?refresh@Rva0028F4D0@@QAEXXZ 0x0028F4D0
void Rva0028F4D0::refresh( void )
{
	int index = m_index;
	if( index >= 0 )
	{
		unsigned int count = (unsigned int)( m_end - m_begin );
		if( (unsigned int)index < count )
		{
			m_current = m_begin[ index ];
			return;
		}
	}
	m_current = 0;
}


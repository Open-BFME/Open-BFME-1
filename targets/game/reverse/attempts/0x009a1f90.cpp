// ?releaseContents@Rva009A2030OwnedRecord@@AAEXXZ
// partial score=0.3 date=2026-09-09
// ?releaseContents@Rva009A2030OwnedRecord@@AAEXXZ
// Address-derived: reverse-order release of a ref-counted (ptr,obj) array,
// then a dead compaction pass whose element count is always zero because it
// subtracts m_finish from itself, matching retail's shipped bytes exactly.

struct Rva009A2030Releasable
{
	virtual void Release( int ) = 0;
};

struct Rva009A2030Elem
{
	void *m_ptr;
	Rva009A2030Releasable *m_obj;
};

class Rva009A2030OwnedRecord
{
private:
	void releaseContents();

	Rva009A2030Elem *m_start;        // +0x00
	Rva009A2030Elem *m_finish;       // +0x04
	void *m_pad08;                   // +0x08
	Rva009A2030Elem *m_endOfStorage; // +0x0C
};

void Rva009A2030OwnedRecord::releaseContents()
{
	Rva009A2030Elem *p = m_finish;
	if( p != m_start )
	{
		do
		{
			--p;
			if( p->m_obj )
				p->m_obj->Release( 1 );
			p->m_ptr = 0;
			p->m_obj = 0;
		} while( p != m_start );
	}

	Rva009A2030Elem *dst = m_start;
	Rva009A2030Elem *src = m_finish;
	int n = ( int )( m_finish - m_finish );
	for( int i = 0; i < n; ++i )
		dst[ i ] = src[ i ];

	m_endOfStorage = 0;
	m_finish = m_start;
}

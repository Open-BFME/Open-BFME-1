// 44-byte range-checked virtual dispatch

class RangeHolder00489280
{
public:
	virtual void v0();
	virtual void v1();
	virtual void handle( int relIndex );

	int m_count;
};

class Rva00489280
{
public:
	void dispatch( int index );

	char                 m_pad00[ 0x10 ];
	RangeHolder00489280 *m_holder;
	int                  m_start;
};

void Rva00489280::dispatch( int index )
{
	if( index < m_start )
		return;
	if( index > m_start + m_holder->m_count )
		return;
	if( m_holder )
		m_holder->handle( index - m_start );
}

// cl: /DNDEBUG /MD
//
// Retail 0x00181EE0: lazily allocate the 0x1C-byte inner object at +0x54
// (vtable Gen01083E78 plus six zero dwords) and copy its two 12-byte parts
// from the argument.  The inner constructor is the same store run as
// Rva001705A0Inner; the two copy callees are already pinned as
// BfmePartCDF::bfmeCopyOneCDF / bfmeCopyTwoCDF.

extern int Gen01083E78;

struct BfmePartCDF
{
	void bfmeCopyOneCDF( BfmePartCDF *other );
	void bfmeCopyTwoCDF( BfmePartCDF *other );
	int m_0;
	int m_1;
	int m_2;
};

class Rva00181EE0Inner
{
public:
	Rva00181EE0Inner();

	int *m_vtable;
	BfmePartCDF m_a;
	BfmePartCDF m_b;
};

inline Rva00181EE0Inner::Rva00181EE0Inner()
{
	m_vtable = &Gen01083E78;
	m_a.m_0 = 0;
	m_a.m_1 = 0;
	m_a.m_2 = 0;
	m_b.m_0 = 0;
	m_b.m_1 = 0;
	m_b.m_2 = 0;
}

class Rva00181EE0Owner
{
public:
	void setFrom( Rva00181EE0Inner *other );

private:
	char m_pad[ 0x54 ];
	Rva00181EE0Inner *m_inner;
};

void Rva00181EE0Owner::setFrom( Rva00181EE0Inner *other )
{
	if ( m_inner == 0 )
		m_inner = new Rva00181EE0Inner;
	Rva00181EE0Inner *inner = m_inner;
	inner->m_a.bfmeCopyOneCDF( &other->m_a );
	inner->m_b.bfmeCopyTwoCDF( &other->m_b );
}

// Retail 0x0048E9D0: fill a temporary layout result through the adjacent
// address-derived layout helper.

struct Rva0048E9D0Range
{
	int m_first;
	int m_last;
};

struct Rva0048E9D0Result
{
	int m_first;
	int m_last;
};

extern void j_00045a52( void );
typedef void (*Rva0048E9D0LayoutCall)( Rva0048E9D0Result *, int, int, int, int );

class Rva0048E9D0
{
public:
	void layout( Rva0048E9D0Range *range );

	int m_first;
	int m_last;
};

void Rva0048E9D0::layout( Rva0048E9D0Range *range )
{
	Rva0048E9D0Result result;
	((Rva0048E9D0LayoutCall)j_00045a52)( &result, m_first, m_last,
		range->m_first, range->m_last );
}

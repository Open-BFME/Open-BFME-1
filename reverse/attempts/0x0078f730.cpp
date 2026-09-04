// ?rva0078F730Select@@YAXPAURva0078F730Selectable@@@Z
// partial score=0.93 date=2026-09-02
// cl: /O2 /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

struct Rva0078F730Selectable
{
	char m_head[ 4 ];
	signed char m_sign;
	char m_gap[ 0x13 ];
	void *m_handler;
};

extern char Rva0078F730NegativeHandler[];
extern char Rva0078F730PositiveHandler[];
void rva0078F730Apply( Rva0078F730Selectable *item );

__forceinline int rva0078F730IsNegative( void *unused, Rva0078F730Selectable *item )
{
	(void)unused;
	return ((unsigned char *)item)[4] & 0x80;
}

void rva0078F730Select( Rva0078F730Selectable *item )
{
	if( rva0078F730IsNegative( 0, item ) )
		item->m_handler = Rva0078F730NegativeHandler;
	else
		item->m_handler = Rva0078F730PositiveHandler;

	rva0078F730Apply( item );
}

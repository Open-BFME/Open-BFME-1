// Retail 0x0047DAF0: admit an unlinked node and append it to the owner.

extern void *__cdecl operator new( unsigned int size );

class Rva0047CF90
{
public:
	Rva0047CF90()
	{
	}
	virtual void slot( void );

	void *m_value;
	void *m_next;
};

class Rva0047DAF0
{
public:
	int append( void *value );

	char m_pad00[ 0x20 ];
	Rva0047CF90 *m_node;
};

int Rva0047DAF0::append( void *value )
{
	if ( value == 0 )
		return -2;
	if ( *(void **)((char *)value + 0x200) != 0 )
		return -3;

	Rva0047CF90 *node = new Rva0047CF90;
	if ( node != 0 )
	{
		node->m_value = value;
		node->m_next = m_node;
		m_node = node;
		return 0;
	}
	return -1;
}

// cl: /DNDEBUG /MD /EHsc

struct Rva008D1EE0Node
{
	unsigned char m_padding00[ 0x4C ];
	Rva008D1EE0Node *m_next;
};

class Rva008D1EE0Chain
{
public:
	bool contains( void *needle );

private:
	unsigned char m_padding00[ 0x4C ];
	Rva008D1EE0Node *m_first;
};

bool Rva008D1EE0Chain::contains( void *needle )
{
	Rva008D1EE0Node *node = m_first;
	if ( node != 0 )
	{
		do
		{
			if ( needle == node )
				return true;
			node = node->m_next;
		}
		while ( node != 0 );
	}
	return false;
}

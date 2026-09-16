// cl: /DNDEBUG /MD
// Retail RVA 0x008951B0. Walks a singly linked list from the head at +0 and
// returns the first node whose entry carries the key, or a null. Nothing names
// the owner, so every class here is address-derived.

class Rva008951B0Entry
{
public:
	unsigned char m_bfmePad000[ 8 ];
	void *m_bfmeKey;
};

class Rva008951B0Node
{
public:
	Rva008951B0Entry *m_bfmeEntry;
	Rva008951B0Node *m_bfmeNext;
};

class Rva008951B0Handle
{
public:
	Rva008951B0Handle( Rva008951B0Node *node ) : m_bfmeNode( node ) {}
	Rva008951B0Handle( const Rva008951B0Handle &other )
		: m_bfmeNode( other.m_bfmeNode ) {}

	Rva008951B0Node *m_bfmeNode;
};

class Rva008951B0Owner
{
public:
	Rva008951B0Handle find( void *key );

	Rva008951B0Node *m_bfmeHead;
};

Rva008951B0Handle Rva008951B0Owner::find( void *key )
{
	Rva008951B0Node *node = m_bfmeHead;

	while( node )
	{
		if( node->m_bfmeEntry->m_bfmeKey == key )
			return Rva008951B0Handle( node );

		node = node->m_bfmeNext;
	}

	return Rva008951B0Handle( 0 );
}

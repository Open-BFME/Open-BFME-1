// cl: /DNDEBUG /MD
//
// Retail 0x0055C220: walk the pointer vector at +0x25c/+0x260, strcmp the
// object's +0x38 name, virtual-delete a match, and memmove the hole closed.

#include <cstring>

class BfmeNamedAptItem
{
public:
	virtual ~BfmeNamedAptItem();

	unsigned char m_unmodelled[ 0x34 ];
	const char *m_name;
};

class BfmeAptScreenRemoveNamed
{
public:
	void removeNamed( const char *name );

private:
	unsigned char m_unmodelled_000[ 0x25c ];
	BfmeNamedAptItem **m_begin;
	BfmeNamedAptItem **m_end;
	unsigned char m_unmodelled_264[ 8 ];
	BfmeNamedAptItem *m_current;
};

// ?removeNamed@BfmeAptScreenRemoveNamed@@QAEXPBD@Z
void BfmeAptScreenRemoveNamed::removeNamed( const char *name )
{
	BfmeNamedAptItem **last = m_end;
	BfmeNamedAptItem **it = m_begin;
	if( it == last )
		return;

	for( ; it != m_end; ++it )
	{
		BfmeNamedAptItem *item = *it;
		if( strcmp( item->m_name, name ) == 0 )
		{
			if( m_current == item )
				m_current = 0;
			delete item;
			BfmeNamedAptItem **next = it + 1;
			if( m_end != next )
				memmove( it, next, (char *)m_end - (char *)next );
			m_end = (BfmeNamedAptItem **)((char *)m_end - 4);
			return;
		}
	}
}

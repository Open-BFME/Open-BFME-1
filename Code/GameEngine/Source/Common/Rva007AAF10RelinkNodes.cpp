// cl: /DNDEBUG /MD
// Retail 0x007AAF10: detach every active node and prepend it to the inactive list.

struct Rva007AAF10Node
{
	char m_padding[0x3C];
	bool m_active;
	char m_padding2[0x73];
	Rva007AAF10Node *m_previous;
	Rva007AAF10Node *m_next;
};

class Rva007AAF10Owner
{
private:
	char m_padding[0x10];
	Rva007AAF10Node *m_active;
	Rva007AAF10Node *m_inactive;

public:
	void moveAllToInactive();
};

void Rva007AAF10Owner::moveAllToInactive()
{
	Rva007AAF10Node *node = m_active;
	while ( node != 0 )
	{
		Rva007AAF10Node *previous = node->m_previous;
		node->m_active = false;

		if ( node->m_previous != 0 )
			node->m_previous->m_next = node->m_next;
		if ( node->m_next != 0 )
			node->m_next->m_previous = node->m_previous;
		else
			m_active = node->m_previous;

		node->m_next = 0;
		node->m_previous = m_inactive;
		if ( m_inactive != 0 )
			m_inactive->m_next = node;
		m_inactive = node;
		node = previous;
	}
}

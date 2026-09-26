// cl: /DNDEBUG /MD
// Retail 0x007AAFA0: advance inactive-node time and move the active chain.

extern unsigned int (__cdecl * volatile g_rva007AAFA0Clock)();
extern unsigned int g_rva007AAFA0Flags;
extern unsigned int g_rva007AAFA0Time;

struct Rva007AAFA0Node
{
	char m_padding[0x3C];
	bool m_active;
	char m_padding2[0x37];
	unsigned int m_age;
	char m_padding3[0x38];
	Rva007AAFA0Node *m_previous;
	Rva007AAFA0Node *m_next;
};

class Rva007AAFA0Owner
{
private:
	char m_padding[0x10];
	Rva007AAFA0Node *m_active;
	Rva007AAFA0Node *m_inactive;

public:
	void advanceAndMoveNodes();
};

void Rva007AAFA0Owner::advanceAndMoveNodes()
{
	unsigned int (__cdecl *clock)() = g_rva007AAFA0Clock;
	unsigned int one = 1;
	unsigned char flags = *(unsigned char *)&g_rva007AAFA0Flags;
	if ( (flags & one) == 0 )
	{
		g_rva007AAFA0Flags |= one;
		g_rva007AAFA0Time = clock();
	}

	Rva007AAFA0Node *node = m_active;
	unsigned int elapsed = clock() - g_rva007AAFA0Time;
	g_rva007AAFA0Time += elapsed;

	while ( node != 0 )
	{
		Rva007AAFA0Node *previous = node->m_previous;
		if ( node->m_active )
			node->m_age += 33;
		else
		{
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
		}
		node = previous;
	}
}

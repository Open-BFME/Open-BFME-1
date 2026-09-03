// ?clear@Rva001E27D0Chain@@QAEXXZ
// partial score=0.6 date=2026-09-02
// cl: /DNDEBUG /MD /EHs-c-
// Walk [begin, end) of a pointer vector at +8/+0xC. Each slot holds a node
// whose +4 link is non-null: clear the link, scalar-delete the node, and
// replace the slot with the saved link. Then a counted empty loop over size.

class Rva001E27D0Node
{
public:
	virtual ~Rva001E27D0Node();
	Rva001E27D0Node *m_next;
};

Rva001E27D0Node::~Rva001E27D0Node()
{
}

class Rva001E27D0Chain
{
public:
	void clear(void);

private:
	unsigned char m_unreconstructed_00[8];
	Rva001E27D0Node **m_begin;
	Rva001E27D0Node **m_end;
};

void Rva001E27D0Chain::clear(void)
{
	Rva001E27D0Node **end = m_end;
	Rva001E27D0Node **it = m_begin;
	if (it != end)
	{
		do
		{
			Rva001E27D0Node *node = *it;
			Rva001E27D0Node *next = node->m_next;
			if (next)
			{
				node->m_next = 0;
				delete node;
				*it = next;
			}
			++it;
		}
		while (it != m_end);
	}

	unsigned int size = (unsigned int)(m_end - m_begin);
	unsigned int i = 0;
	if (size > 0)
	{
		unsigned int n = (unsigned int)(m_end - m_begin);
		while (++i < n)
			;
	}
}

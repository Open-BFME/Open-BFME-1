// cl: /DNDEBUG /MD /O2
// Gen003BD7D0Node::match, retail 0x003A43C0 (73 bytes).

struct Gen003A43C0Element
{
	unsigned char m_pad[0xA4];
	int m_id;
};

struct Gen003A43C0Span
{
	Gen003A43C0Element *const *m_begin;
	Gen003A43C0Element *const *m_end;
	__forceinline int size() const { return m_end - m_begin; }
};

class Gen003BD7D0Node
{
public:
	bool match(int id);

private:
	unsigned char m_pad[0x48];
	Gen003A43C0Span m_items;
};

bool Gen003BD7D0Node::match(int id)
{
	unsigned int i = 0;
	if (static_cast<unsigned int>(m_items.size()) > 0)
	{
		Gen003A43C0Element *const *ptr = m_items.m_begin;
		do
		{
			if ((*ptr)->m_id == id)
				return true;
			++i;
			++ptr;
		}
		while (i < m_items.size());
	}
	return false;
}

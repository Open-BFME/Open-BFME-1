// The manager destructor at 0x009A4620 directly calls this body on the object
// allocated by the named Rva009A45A0CollisionData constructor.  The synthetic
// scalar-deleting wrapper at 0x009A2920 calls the same body, but its generated
// class name is not used as the semantic identity here.
// cl: /O2 /DNDEBUG /MD /EHsc

struct Rva009A2390PrimaryLink
{
	Rva009A2390PrimaryLink *m_next;
	unsigned int m_pad04;
	Rva009A2390PrimaryLink *m_prev;
};

struct Rva009A2390EmbeddedLink;

struct Rva009A2390Owner
{
	unsigned int m_pad00;
	unsigned int m_refCount;
	unsigned int m_pad08;
	Rva009A2390EmbeddedLink *m_heads[6];
};

struct Rva009A2390SecondaryLink
{
	Rva009A2390SecondaryLink *m_prev;
	Rva009A2390SecondaryLink *m_next;
	char m_pad08[8];
	Rva009A2390SecondaryLink *m_ownerNext;
};

struct Rva009A2390EmbeddedLink
{
	Rva009A2390EmbeddedLink *m_links[2];
	char m_pad08[0xc];
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();

private:
	Rva009A2390Owner *m_owner;
	unsigned int m_pad04;
	Rva009A2390PrimaryLink *m_primaryPrev;
	Rva009A2390PrimaryLink *m_primaryNext;
	Rva009A2390SecondaryLink *m_secondaryPrev;
	Rva009A2390SecondaryLink *m_secondaryNext;
	char m_pad18[0xc];
	Rva009A2390EmbeddedLink m_embedded[6];
};

Rva009A45A0CollisionData::~Rva009A45A0CollisionData()
{
	--m_owner->m_refCount;

	if (m_primaryNext != 0)
		m_primaryNext->m_prev = m_primaryPrev;
	m_primaryPrev->m_next = m_primaryNext;
	m_primaryPrev = 0;

	if (m_embedded[0].m_links[0] != 0)
	{
		unsigned int index = 0;
		Rva009A2390EmbeddedLink **next = &m_embedded[0].m_links[1];
		do
		{
			Rva009A2390EmbeddedLink *previous = next[-1];
			if (previous != 0)
				previous->m_links[1] = *next;
			else
				m_owner->m_heads[index >> 1] = *next;

			Rva009A2390EmbeddedLink *current = *next;
			if (current != 0)
				current->m_links[0] = next[-1];
			next[-1] = 0;
			*next = 0;
			++index;
			next = (Rva009A2390EmbeddedLink **)((char *)next + 0x14);
		}
		while (index < 6);
	}

	if (m_secondaryPrev != 0)
	{
		if (m_secondaryNext != 0)
			m_secondaryNext->m_ownerNext = m_secondaryPrev;
		m_secondaryPrev->m_prev = m_secondaryNext;
		m_secondaryPrev = 0;
	}
}

// A bounded scan over the 0x28-byte records used by the three U4 proxy
// forwarders.  The proxy at 0x00606E20 proves the receiver and two-argument
// shape; this body's unnormalised EAX return proves that the result is a
// pointer rather than the historical Bool guess.

struct U4Elem
{
	char m_pad[0x28];
	void *m_named[0x1C8 / 4];
};

class U4Filter
{
public:
	bool accepts(const U4Elem *element) const;
};

class U4Scan
{
public:
	const char *firstNamed(void *out, const U4Filter *filter) const;

	int m_f00;
	int m_f04;
	U4Elem *m_begin;
	U4Elem *m_end;
};

const char *U4Scan::firstNamed(void *out, const U4Filter *filter) const
{
	U4Elem *p = m_begin;
	U4Elem *end = m_end;
	unsigned int index = (unsigned int)out;

	for (; p != end; ++p)
	{
		if (filter->accepts(p) && p->m_named[index] != 0)
			return static_cast<const char *>(p->m_named[index]) + 4;
	}

	return 0;
}

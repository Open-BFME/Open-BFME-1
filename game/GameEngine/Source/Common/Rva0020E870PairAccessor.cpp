// The retail body is a secondary-subobject accessor.  The word 12 bytes before
// that subobject leads to an owner, whose two-word value starts at
// offset 0x40.  No caller currently exposes the original class names, so the
// reconstruction keeps its identity explicitly address-derived.

class Rva0020E870Pair
{
public:
	__forceinline Rva0020E870Pair() {}
	__forceinline Rva0020E870Pair(const Rva0020E870Pair &other) :
		m_first(other.m_first),
		m_second(other.m_second)
	{
	}

	int m_first;
	int m_second;
};

class Rva0020E870Owner
{
public:
	char m_leading[0x40];
	Rva0020E870Pair m_pair;

	__forceinline const Rva0020E870Pair *pairAddress() const
	{
		return &m_pair;
	}
};

class Rva0020E870Subobject
{
public:
	Rva0020E870Pair getPair() const;
};

Rva0020E870Pair Rva0020E870Subobject::getPair() const
{
	const Rva0020E870Owner *owner =
		*reinterpret_cast<Rva0020E870Owner *const *>(
			reinterpret_cast<const char *>(this) - 0xC);
	const Rva0020E870Pair *source = owner->pairAddress();
	return Rva0020E870Pair(*source);
}

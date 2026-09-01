struct PrefMapNodeShim
{
	char m_unreconstructed00[0x10];
	void *m_value;
};

struct Rva0036E560Map
{
	char m_unreconstructed00[8];
	PrefMapNodeShim *m_begin;
};

PrefMapNodeShim *prefMapIncrement(PrefMapNodeShim *node);

class Rva0036E560PointerVector
{
public:
	unsigned int size() const
	{
		return m_end - m_begin;
	}

	void *operator[](unsigned int index) const
	{
		return m_begin[index];
	}

private:
	void **m_begin;
	void **m_end;
	void **m_capacity;
};

class Rva0036E560PointerSet
{
public:
	bool containsPointer(void *value) const;

private:
	char m_unreconstructed00[0xA0];
	void *m_primary;
	char m_unreconstructedA4[0x20];
	Rva0036E560PointerVector m_first;
	Rva0036E560PointerVector m_second;
	char m_unreconstructedDC[0x18];
	Rva0036E560Map *m_map;
};

bool Rva0036E560PointerSet::containsPointer(void *value) const
{
	if (value == m_primary)
		return true;

	PrefMapNodeShim *node = m_map->m_begin;
	while (node != (PrefMapNodeShim *)m_map)
	{
		if (value == node->m_value)
			return true;
		node = prefMapIncrement(node);
	}

	for (unsigned int i = 0; i < m_first.size(); ++i)
	{
		if (value == m_first[i])
			return true;
	}

	for (unsigned int i = 0; i < m_second.size(); ++i)
	{
		if (value == m_second[i])
			return true;
	}

	return false;
}

// @?containsPointer@Rva0036E560PointerSet@@QBE_NPAX@Z 0x0036E560

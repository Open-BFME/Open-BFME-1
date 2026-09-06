// ?lookup@Rva008838F0Owner@@QAEHIPAPAXI@Z
// Address-derived identity from the complete retail hash-bucket and copy
// shape; no semantic owner name is claimed.
// cl: /O2 /DNDEBUG /MD

extern "C" __declspec(dllimport) void __stdcall Rva01358D18Enter(void *lock);
extern "C" __declspec(dllimport) void __stdcall Rva01358E74Leave(void *lock);

class Rva008838F0Node
{
public:
	Rva008838F0Node *m_next;
	unsigned int m_pad04;
	unsigned int m_key;
	unsigned int m_pad0c[3];
	unsigned int m_count;
	void *m_values[1];
};

class Rva008838F0Owner
{
public:
	int lookup(unsigned int key, void **dest, unsigned int limit);

private:
	char m_pad00[0x0c];
	Rva008838F0Node *m_buckets[0x2b7b];
	char m_padAfterBuckets[0x282c0 - (0x0c + 0x2b7b * 4)];
	unsigned char m_disabled;
	char m_pad282c1[7];
	void *m_lock;
};

int Rva008838F0Owner::lookup(unsigned int key, void **dest, unsigned int limit)
{
	if (dest != 0 && limit != 0 && m_disabled == 0)
	{
		if (m_lock != 0)
			Rva01358D18Enter(m_lock);

		Rva008838F0Node **link = &m_buckets[key % 0x2b7b];
		while (*link != 0 && (*link)->m_key != key)
			link = &(*link)->m_next;
		Rva008838F0Node *node = *link;
		if (node == 0)
			return 0;

		unsigned int i = 0;
		while (i < limit && i < node->m_count)
		{
			dest[i] = node->m_values[i];
			++i;
		}

		if (m_lock != 0)
			Rva01358E74Leave(m_lock);
		return i;
	}

	return 0;
}

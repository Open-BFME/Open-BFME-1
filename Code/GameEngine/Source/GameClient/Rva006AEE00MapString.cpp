// cl: /DNDEBUG /MD
//
// Retail 0x006AEE00: thiscall returning StringBase by hidden pointer.  If the
// ready byte at +0x630 is clear, run init.  Find in the tree at +0x64, maybe
// increment, then copy either the empty string or the payload at node+0x10.

template <typename T> class StringBase
{
	friend class Rva006AEE00;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();
	void *m_data;
};

extern StringBase<char> g_Va01336E50;

void *rbIncrement(void *node);
void *rbDecrement(void *node);

class Rva006AEE00Tree
{
public:
	void *find(void *key);

	void *header;
	int count;
};

class Rva006AEE00
{
public:
	StringBase<char> get(void *key);
	StringBase<char> getPrev(void *key);

private:
	void init();

	char m_pad[0x64];
	Rva006AEE00Tree m_tree;
	char m_pad6C[0x630 - 0x6C];
	unsigned char m_ready;
};

StringBase<char> Rva006AEE00::get(void *key)
{
	if (!m_ready)
		init();
	void *it = m_tree.find(key);
	if (it != m_tree.header)
		it = rbIncrement(it);
	void *header = m_tree.header;
	if (it == header)
	{
		it = *((void **)header + 2);
		if (it == header)
			return g_Va01336E50;
	}
	return *reinterpret_cast<StringBase<char> *>((char *)it + 0x10);
}

StringBase<char> Rva006AEE00::getPrev(void *key)
{
	if (!m_ready)
		init();
	if (m_tree.count == 0)
		return g_Va01336E50;
	void *it = m_tree.find(key);
	void *header = m_tree.header;
	if (it == *((void **)header + 2))
		it = header;
	it = rbDecrement(it);
	return *reinterpret_cast<StringBase<char> *>((char *)it + 0x10);
}

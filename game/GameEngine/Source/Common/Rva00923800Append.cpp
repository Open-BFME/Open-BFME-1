class Rva00923800Item
{
public:
	int m_pad;
	int m_refs;
};

class Rva00923800
{
public:
	void append(Rva00923800Item *item);

private:
	char m_pad[0x130];
	Rva00923800Item *m_items[32];
	int m_count;
	int m_overflow;
};

void Rva00923800::append(Rva00923800Item *item)
{
	if ((unsigned)m_count < 31)
	{
		if (item != 0)
			++item->m_refs;
		m_items[m_count] = item;
		++m_count;
	}
	else
		++m_overflow;
}

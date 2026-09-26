// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class Rva0015A280Owner;

class Rva0015A280Item
{
public:
	unsigned char m_pad000[0x31C];
	Rva0015A280Owner *m_owner;
};

class Rva0015A280Owner
{
public:
	void append(Rva0015A280Item *item);

private:
	unsigned char m_pad000[0x120];
	int m_itemCount;
	Rva0015A280Item *m_items[36];
	unsigned char m_pad1B4[4];
	bool m_itemsCurrent;
};

void Rva0015A280Owner::append(Rva0015A280Item *item)
{
	item->m_owner = 0;
	if (m_itemCount < 36)
	{
		m_items[m_itemCount] = item;
		++m_itemCount;
	}
	m_itemsCurrent = false;
}

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007AECC0Item
{
	char m_pad[0x68];
	int m_value;
	int m_6c;
	int m_70;
};

class Rva007AECC0Slot
{
public:
	void set(unsigned int index, int value);
	int get(unsigned int index);
	void getPair(unsigned int index, int *a, int *b);

	char m_pad[0x58];
	Rva007AECC0Item *m_items[1];
};

void Rva007AECC0Slot::set(unsigned int index, int value)
{
	Rva007AECC0Item *item = m_items[index];
	if (item)
		item->m_value = value;
}

int Rva007AECC0Slot::get(unsigned int index)
{
	Rva007AECC0Item *item = m_items[index];
	if (item)
		return item->m_value;
	return 0;
}

void Rva007AECC0Slot::getPair(unsigned int index, int *a, int *b)
{
	Rva007AECC0Item *item = m_items[index];
	if (item)
	{
		*a = item->m_6c;
		*b = item->m_70;
	}
}

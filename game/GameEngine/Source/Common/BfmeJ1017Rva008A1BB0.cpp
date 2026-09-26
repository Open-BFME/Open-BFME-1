// cl: /O2 /DNDEBUG /MD
//
// Address-derived identity: no direct named caller is present in the current
// retail xref inventory. The class identity is supported by the exact call to
// BfmeJ1017::bfmeInsert at 0x008A0700 and the contiguous BfmeJ1017 layout used
// by BfmeJ1017Insert.cpp and BfmeJ1017Send.cpp. Retail writes the four fields
// at this+0x127C, +0x1280, +0x1284, +0x128C, +0x1290 and +0x1294 for type
// values 0x1F5 and 0x1F6, then inserts the packed event value.

class BfmeJ1017
{
public:
	void bfmeInsert(unsigned int packed);
	void rva008A1BB0(int a, int b, unsigned char c, int type);

private:
	char m_pad0[0x127C];
	int m_value127C;
	int m_value1280;
	unsigned char m_value1284;
	char m_pad1[7];
	int m_value128C;
	int m_value1290;
	unsigned char m_value1294;
};

void BfmeJ1017::rva008A1BB0(int a, int b, unsigned char c, int type)
{
	if (type == 0x1F5)
	{
		m_value127C = a;
		m_value1280 = b;
		m_value1284 = c;
	}
	else if (type == 0x1F6)
	{
		m_value128C = a;
		m_value1290 = b;
		m_value1294 = c;
	}

	bfmeInsert(((((type << 15) | c) << 2) | 1));
}

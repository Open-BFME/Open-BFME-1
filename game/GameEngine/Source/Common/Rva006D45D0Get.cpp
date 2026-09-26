// cl: /O2 /Ob0

class Rva006D45D0
{
	char pad[0xA4];
	int m_table[0x1000];

public:
	int get(unsigned i);
};

int Rva006D45D0::get(unsigned i)
{
	if (i < 0x1000)
		return m_table[i];
	return 0;
}

// cl: /O2 /Ob0

class Rva0066B100
{
	char pad[0x272];
	unsigned short m_tab[1];

public:
	int get(int i);
};

int Rva0066B100::get(int i)
{
	return m_tab[i] >= 5;
}

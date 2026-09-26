// cl: /O2 /Ob0

class Rva001B2B30
{
	char pad[0x2A0];
	int m_2A0;

public:
	int get(int bit);
};

int Rva001B2B30::get(int bit)
{
	return (m_2A0 & (1 << bit)) != 0;
}

// cl: /O2 /Ob0

class Rva0016A5B0
{
	char pad[0x40];
	int m_40;

public:
	int get(int bit);
};

int Rva0016A5B0::get(int bit)
{
	return (m_40 & (1 << bit)) != 0;
}

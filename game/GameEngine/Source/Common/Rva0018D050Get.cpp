// cl: /O2 /Ob0

struct Rva0018D050Inner
{
	char pad[0x3C];
	int m_3C;
};

class Rva0018D050
{
	char pad[4];
	Rva0018D050Inner *m_04;

public:
	int get(int bit);
};

int Rva0018D050::get(int bit)
{
	return (m_04->m_3C & (1 << bit)) != 0;
}

// cl: /O2 /Ob0

class Rva0049AF00
{
	char pad[0x148];
	int m_148;

public:
	void set(int v);
};

void Rva0049AF00::set(int v)
{
	if (v == 0 || v == 1)
		m_148 = v;
}

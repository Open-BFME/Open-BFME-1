// cl: /O2 /Ob0

class Rva0059F890
{
	char pad[8];
	char m_08;
	char pad2[7];
	int m_10, m_14;
	char pad3[0x14];
	int m_2C;

public:
	void set(int v);
};

void Rva0059F890::set(int v)
{
	m_2C = -1;
	if (v >= m_10 && v <= m_14)
	{
		if (v == m_10 || v == m_14)
			m_08 = 1;
		m_2C = v;
	}
}

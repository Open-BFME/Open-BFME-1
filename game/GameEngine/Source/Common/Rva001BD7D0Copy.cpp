// cl: /O2 /Ob0

class Rva001BD7D0
{
	char m_lead[0x48];
	int m_48;
	int m_4c;
	int m_50;

public:
	void copy(int *dst) const;
};

void Rva001BD7D0::copy(int *dst) const
{
	dst[0] = m_48;
	dst[1] = m_4c;
	dst[2] = m_50;
}

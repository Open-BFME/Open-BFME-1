// cl: /O2 /Ob0

class Rva0007C510
{
	char m_lead[0x171C];
	int m_left;
	char m_mid[0x1738 - 0x1720];
	int m_right;

public:
	int ge() const;
};

int Rva0007C510::ge() const
{
	return m_left >= m_right;
}

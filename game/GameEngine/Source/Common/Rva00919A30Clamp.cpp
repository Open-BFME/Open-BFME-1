class Rva00919A30
{
public:
	void set(int value);

private:
	char m_pad[0xC8];
	int m_max;
	char m_gap[0x58];
	int m_value;
};

void Rva00919A30::set(int value)
{
	value &= (value < 0) - 1;
	if (value >= m_max)
		m_value = m_max;
	else
		m_value = value;
}

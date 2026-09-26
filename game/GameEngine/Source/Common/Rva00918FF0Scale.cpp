class Rva00918FF0
{
public:
	int scale();

private:
	char m_pad[0xE0];
	int m_count;
	char m_gap[0x40];
	int m_shift;
};

int Rva00918FF0::scale()
{
	return (1 << m_shift) * (m_count - 1) << 1;
}

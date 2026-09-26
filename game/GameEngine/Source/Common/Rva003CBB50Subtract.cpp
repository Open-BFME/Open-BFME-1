class Rva003CBB50
{
public:
	void subtract(unsigned short value);

private:
	char m_pad[0x30];
	int m_value;
};

void Rva003CBB50::subtract(unsigned short value)
{
	m_value -= value;
	if (m_value < 0)
		m_value = 0;
}

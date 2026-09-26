class Rva003CB9A0
{
public:
	void add(unsigned short value);

private:
	char m_pad[0x30];
	int m_value;
};

void Rva003CB9A0::add(unsigned short value)
{
	m_value += value;
}

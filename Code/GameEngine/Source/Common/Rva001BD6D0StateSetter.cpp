// ?set@Rva001BD6D0State@@QAEXH@Z
// cl: /O2 /MD /EHsc-

class Rva001BD6D0State
{
public:
	void set(int value);

	char m_lead[0x314];
	int m_value;
	unsigned char m_flag318;
	unsigned char m_flag319;
};

void Rva001BD6D0State::set(int value)
{
	m_value = value;
	m_flag318 = 0;
	m_flag319 = 0;
}

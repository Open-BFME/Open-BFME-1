// cl: /O2 /Ob0

class Rva0060D580
{
	char m_lead[0x295];
	unsigned char m_flag;

public:
	void flip();
};

void Rva0060D580::flip()
{
	m_flag = !m_flag;
}

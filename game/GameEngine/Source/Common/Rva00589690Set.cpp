// cl: /O2 /Ob0

class Rva00589690
{
	char m_pad[0x4B];
	unsigned char m_flag;

	void notify();

public:
	void set(unsigned char v);
};

void Rva00589690::set(unsigned char v)
{
	m_flag = v;
	notify();
}

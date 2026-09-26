// Open-BFME: conditional flag reset reconstructed from retail RVA 0x002918E0.

class Rva002918E0Object
{
public:
	void set(unsigned char value);

private:
	char m_pad0[0x2D];
	unsigned char m_flag;
	char m_pad2E;
	unsigned char m_secondary;
};

void Rva002918E0Object::set(unsigned char value)
{
	m_flag = value;
	if (value != 0)
		m_secondary = 0;
}

// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F7500
{
	char m_pad[0xC];
	unsigned m_lead : 20;
	unsigned m_bit : 1;

public:
	void set(unsigned char value);
};

void Rva003F7500::set(unsigned char value)
{
	m_bit = value;
}

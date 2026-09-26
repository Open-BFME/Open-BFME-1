// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva003F75C0
{
	char m_pad[0xC];
	unsigned m_lead : 18;
	unsigned m_bit : 1;

public:
	void set(unsigned char value);
};

void Rva003F75C0::set(unsigned char value)
{
	m_bit = value;
}

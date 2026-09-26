// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Gen0083E8F0
{
	unsigned char m_pad8[8];
	unsigned m_8;
	unsigned char m_pad14[0x14 - 0xC];
	unsigned m_14;
	unsigned char m_pad58[0x58 - 0x18];
	unsigned m_58;

public:
	void handle();
	void set(unsigned v);
};

void Gen0083E8F0::set(unsigned v)
{
	if (!m_58)
		v |= 1;
	m_8 = v;
	if (m_14 & v)
		handle();
}

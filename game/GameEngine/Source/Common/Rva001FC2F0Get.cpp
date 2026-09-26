// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

extern unsigned g_sentinel012ADC38;

class Rva001FC2F0
{
	unsigned char m_pad[0x0C];
	unsigned m_0C;
	unsigned char m_pad2[0x40 - 0x10];
	unsigned m_40;

public:
	unsigned get() const;
};

unsigned Rva001FC2F0::get() const
{
	unsigned v = m_40;
	if (v == g_sentinel012ADC38)
		return m_0C;
	return v;
}

class Rva001FC310
{
	unsigned char m_pad[0x0C];
	unsigned m_0C;
	unsigned char m_pad2[0x44 - 0x10];
	unsigned m_44;

public:
	unsigned get() const;
};

unsigned Rva001FC310::get() const
{
	unsigned v = m_44;
	if (v == g_sentinel012ADC38)
		return m_0C;
	return v;
}

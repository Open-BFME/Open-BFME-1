// cl: /DNDEBUG /MD /EHsc

void __stdcall bfmeFree923F(void *value, int mode);

class Gen003BD8D0Arg
{
};

class Rva003BF540
{
public:
	bool act(Gen003BD8D0Arg *value);
};

class Glo012F1028Type
{
public:
	bool act(Gen003BD8D0Arg *value);
};

extern Glo012F1028Type *Glo012F1028;

class Rva003C8340Item
{
public:
	char m_pad00[0xa8];
	unsigned char m_enabled;
};

class Rva003C8340
{
public:
	void set(Rva003C8340Item *value);
	void release(Rva003C8340Item *value, int mode);
	void prepare(Rva003C8340Item *value);

	char m_pad00[8];
	Rva003C8340Item *m_current;
	char m_pad0c[4];
	unsigned char m_enabled;
};

#pragma comment(linker, "/alternatename:?act@Glo012F1028Type@@QAE_NPAVGen003BD8D0Arg@@@Z=?act@Rva003BF540@@QAE_NPAVGen003BD8D0Arg@@@Z")
#pragma comment(linker, "/alternatename:?prepare@Rva003C8340@@QAEXPAVRva003C8340Item@@@Z=?d_003c7d20@@YAXXZ")

void Rva003C8340::set(Rva003C8340Item *value)
{
	if (!m_enabled || value == 0 || !value->m_enabled)
	{
		if (m_current != 0)
			release(m_current, 0);
		m_current = 0;
		return;
	}

	if (m_current != 0 && m_current != value)
		bfmeFree923F(m_current, 0);

	if (!((Rva003BF540 *)Glo012F1028)->act((Gen003BD8D0Arg *)value))
	{
		m_current = 0;
		return;
	}

	prepare(value);
	if (m_current == value)
		return;

	release(value, 1);
	m_current = value;
}

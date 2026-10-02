// cl: /DNDEBUG /MD /EHsc

class Gen003BD8D0Arg
{
};

class Rva003BF540
{
public:
	bool act(Gen003BD8D0Arg *value);
};

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

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
	void notifyHilight(Rva003C8340Item *value, bool enabled);
	void prepare(Rva003C8340Item *value);

	char m_pad00[8];
	Rva003C8340Item *m_current;
	char m_pad0c[4];
	unsigned char m_enabled;
};

#pragma comment(linker, "/alternatename:?prepare@Rva003C8340@@QAEXPAVRva003C8340Item@@@Z=?d_003c7d20@@YAXXZ")

void Rva003C8340::set(Rva003C8340Item *value)
{
	if (!m_enabled || value == 0 || !value->m_enabled)
	{
		if (m_current != 0)
			notifyHilight(m_current, false);
		m_current = 0;
		return;
	}

	if (m_current != 0 && m_current != value)
		notifyHilight(m_current, false);

	if (!((Rva003BF540 *)TheLivingWorldLogic)->act((Gen003BD8D0Arg *)value))
	{
		m_current = 0;
		return;
	}

	prepare(value);
	if (m_current == value)
		return;

	notifyHilight(value, true);
	m_current = value;
}

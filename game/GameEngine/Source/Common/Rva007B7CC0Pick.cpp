// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

struct Rva007B7CC0Target
{
	int m_pad;
	int m_refs;
};

class Rva007B7CC0Pick
{
public:
	Rva007B7CC0Target *pick(unsigned char flag);

	char m_pad[0x30];
	Rva007B7CC0Target *m_30;
	Rva007B7CC0Target *m_34;
};

Rva007B7CC0Target *Rva007B7CC0Pick::pick(unsigned char flag)
{
	Rva007B7CC0Target *target;
	if (flag)
		target = m_34;
	else
		target = m_30;
	if (target)
		++target->m_refs;
	return target;
}

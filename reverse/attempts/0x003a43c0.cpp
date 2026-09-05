// ?bfmeContains@Gen003A43C0@@QBE_NPBX@Z
// partial score=0.4 date=2026-09-05
// cl: /DNDEBUG /MD /O2
// Clean C++ conversion of the pointer-array membership scan at retail RVA 0x003A43C0.

struct Gen003A43C0Element
{
	unsigned char m_pad[0xA4];
	void *m_key;
};

class Gen003A43C0
{
public:
	bool bfmeContains(const void *key) const;

private:
	unsigned char m_pad[0x48];
	Gen003A43C0Element *const *m_begin;
	Gen003A43C0Element *const *m_end;
};

bool Gen003A43C0::bfmeContains(const void *key) const
{
	int count = static_cast<int>(m_end - m_begin);
	if (count <= 0)
		return false;

	Gen003A43C0Element *const *ptr = m_begin;
	int i = 0;
	do
	{
		if ((*ptr)->m_key == key)
			return true;
		++i;
		++ptr;
	}
	while (i < static_cast<int>(m_end - m_begin));

	return false;
}

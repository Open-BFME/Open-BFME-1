// cl: /O2 /DNDEBUG /MD

struct BfmeSub929G
{
	char m_bfmePad[6];
	unsigned short m_bfmeW;
};

class BfmeThing929G
{
public:
	void bfmeInit929G();
	BfmeSub929G *m_bfmeP;
};

void BfmeThing929G::bfmeInit929G()
{
	BfmeSub929G *data = m_bfmeP;
	char *s = reinterpret_cast<char *>(data) + 8;
	unsigned hash = 0x811C9DC5;
	int c = (signed char)*s;
	if (c)
	{
		do
		{
			++s;
			if (c <= 'Z' && c >= 'A')
				c += 32;
			hash = (unsigned)((c ^ (int)hash) * 0x01000193);
			c = (signed char)*s;
		}
		while (c);
	}
	unsigned int value;
	if ((unsigned short)hash == 0)
		value = 0x4567;
	else
		value = hash;
	data->m_bfmeW = (unsigned short)value;
}

// ?ComputeHash@EAStringC@@QAEXXZ
// partial score=0.55 date=2026-09-02
// cl: /O2 /DNDEBUG /MD

class EAStringC
{
	class StringDataC
	{
	public:
		unsigned short m_uRefCount;
		unsigned short m_uSize;
		unsigned short m_uMaxSize;
		unsigned short m_uHash;
	};

	StringDataC *m_pData;

public:
	void ComputeHash();
};

void EAStringC::ComputeHash()
{
	StringDataC *data = m_pData;
	char *s = reinterpret_cast<char *>(data) + sizeof(StringDataC);
	int c = (signed char)*s;
	unsigned hash = 0x811C9DC5u;
	if (c)
	{
		do
		{
			++s;
			if (c <= 'Z' && c >= 'A')
				c += 32;
			int mixed = c;
			mixed ^= (int)hash;
			mixed *= 0x01000193;
			hash = (unsigned)mixed;
			c = (signed char)*s;
		}
		while (c);
	}
	if ((unsigned short)hash == 0)
	{
		int v = 0x4567;
		data->m_uHash = (unsigned short)v;
	}
	else
		data->m_uHash = (unsigned short)hash;
}

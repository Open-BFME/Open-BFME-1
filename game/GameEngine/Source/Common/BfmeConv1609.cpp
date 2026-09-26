// Open-BFME5 conversions.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value) throw();

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTC
{
public:
	BfmeStrVTC(const BfmeStrVTC &other);
	~BfmeStrVTC();
	char *m_bfme00;
};

class BfmeTargetVTC
{
public:
	int m_bfme00;
	long m_bfme04;
};

struct BfmeEntVTC
{
	__forceinline BfmeEntVTC(const BfmeEntVTC &other)
		: m_bfme00(other.m_bfme00)
	{
		m_bfme04 = other.m_bfme04;

		if (m_bfme04 != 0)
			InterlockedIncrement(&m_bfme04->m_bfme04);
	}

	BfmeStrVTC m_bfme00;
	BfmeTargetVTC *m_bfme04;
};

void bfmeConstructVTC(BfmeEntVTC *dest, const BfmeEntVTC *source)
{
	new (dest) BfmeEntVTC(*source);
}

// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTI
{
public:
	BfmeStrVTI(const BfmeStrVTI &other);
	~BfmeStrVTI();
	char *m_bfme00;
};

struct BfmeHeadVTI
{
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
};

struct BfmeEntVTI
{
	__forceinline BfmeEntVTI(const BfmeEntVTI &other)
		: m_bfme00(other.m_bfme00), m_bfme18(other.m_bfme18)
	{
	}

	BfmeHeadVTI m_bfme00;
	BfmeStrVTI m_bfme18;
};

void bfmeConstructVTI(BfmeEntVTI *dest, const BfmeEntVTI *source)
{
	new (dest) BfmeEntVTI(*source);
}

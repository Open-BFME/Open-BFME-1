// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTH
{
public:
	BfmeStrVTH(const BfmeStrVTH &other);
	~BfmeStrVTH();
	char *m_bfme00;
};

struct BfmeEntVTH
{
	__forceinline BfmeEntVTH(const BfmeEntVTH &other)
		: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04),
		  m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c),
		  m_bfme10(other.m_bfme10)
	{
	}

	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	BfmeStrVTH m_bfme10;
};

void bfmeConstructVTH(BfmeEntVTH *dest, const BfmeEntVTH *source)
{
	new (dest) BfmeEntVTH(*source);
}

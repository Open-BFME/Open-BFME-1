// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTF
{
public:
	BfmeStrVTF(const BfmeStrVTF &other);
	~BfmeStrVTF();
	char *m_bfme00;
};

struct BfmeEntVTF
{
	__forceinline BfmeEntVTF(const BfmeEntVTF &other)
		: m_bfme00(other.m_bfme00), m_bfme04(other.m_bfme04),
		  m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c)
	{
	}

	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	BfmeStrVTF m_bfme0c;
};

void bfmeConstructVTF(BfmeEntVTF *dest, const BfmeEntVTF *source)
{
	new (dest) BfmeEntVTF(*source);
}

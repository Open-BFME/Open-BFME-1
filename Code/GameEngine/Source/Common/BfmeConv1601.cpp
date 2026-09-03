// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVSY
{
public:
	BfmeStrVSY(const BfmeStrVSY &other);
	~BfmeStrVSY() { bfmeClearVSY(); }
	void bfmeClearVSY();
	char *m_bfme00;
	int m_bfme04;
};

struct BfmeEntVSY
{
	__forceinline BfmeEntVSY(const BfmeEntVSY &other)
		: m_bfme00(other.m_bfme00), m_bfme08(other.m_bfme08), m_bfme0c(other.m_bfme0c)
	{
	}

	BfmeStrVSY m_bfme00;
	int m_bfme08;
	int m_bfme0c;
};

void bfmeConstructVSY(BfmeEntVSY *dest, const BfmeEntVSY *source)
{
	new (dest) BfmeEntVSY(*source);
}

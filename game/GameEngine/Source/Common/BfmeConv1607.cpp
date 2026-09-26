// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTB
{
public:
	BfmeStrVTB(const BfmeStrVTB &other);
	~BfmeStrVTB();
	char *m_bfme00;
};

class BfmeEntVTB
{
public:
	__forceinline BfmeEntVTB(const BfmeEntVTB &other)
		: m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08),
		  m_bfme0c(other.m_bfme0c), m_bfme10(other.m_bfme10)
	{
	}

	virtual void bfmeSlot0VTB();
	int m_bfme04;
	int m_bfme08;
	BfmeStrVTB m_bfme0c;
	char m_bfme10;
};

void bfmeConstructVTB(BfmeEntVTB *dest, const BfmeEntVTB *source)
{
	new (dest) BfmeEntVTB(*source);
}

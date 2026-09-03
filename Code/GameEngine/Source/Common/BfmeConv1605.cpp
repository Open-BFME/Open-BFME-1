// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeStrVTA
{
public:
	BfmeStrVTA(const BfmeStrVTA &other);
	~BfmeStrVTA();
	char *m_bfme00;
};

class BfmeEntVTA
{
public:
	__forceinline BfmeEntVTA(const BfmeEntVTA &other)
		: m_bfme04(other.m_bfme04), m_bfme08(other.m_bfme08)
	{
	}

	virtual void bfmeSlot0VTA();
	BfmeStrVTA m_bfme04;
	char m_bfme08;
};

void bfmeConstructVTA(BfmeEntVTA *dest, const BfmeEntVTA *source)
{
	new (dest) BfmeEntVTA(*source);
}

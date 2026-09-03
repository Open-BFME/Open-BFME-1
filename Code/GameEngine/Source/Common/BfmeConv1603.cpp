// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

class BfmeBigVSZ
{
public:
	BfmeBigVSZ(const BfmeBigVSZ &other);
	~BfmeBigVSZ();
	char m_bfmePad00[0x70];
};

struct BfmeEntVSZ
{
	__forceinline BfmeEntVSZ(const BfmeEntVSZ &other)
		: m_bfme00(other.m_bfme00), m_bfme70(other.m_bfme70), m_bfme74(other.m_bfme74)
	{
	}

	BfmeBigVSZ m_bfme00;
	int m_bfme70;
	char m_bfme74;
};

void bfmeConstructVSZ(BfmeEntVSZ *dest, const BfmeEntVSZ *source)
{
	new (dest) BfmeEntVSZ(*source);
}

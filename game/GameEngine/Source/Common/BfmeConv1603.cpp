// Open-BFME5 conversions.

inline void *operator new(unsigned int size, void *where)
{
	return where;
}

inline void operator delete(void *block, void *where)
{
}

// callees.py 0x0069C3A0: the member copy is ILT 0x00047B27 -> 0x000B2FB0,
// the matched AudioEventRTS copy constructor.
class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &other);
	~AudioEventRTS();
	char m_bfmePad00[0x70];
};

struct BfmeEntVSZ
{
	__forceinline BfmeEntVSZ(const BfmeEntVSZ &other)
		: m_bfme00(other.m_bfme00), m_bfme70(other.m_bfme70), m_bfme74(other.m_bfme74)
	{
	}

	AudioEventRTS m_bfme00;
	int m_bfme70;
	char m_bfme74;
};

void bfmeConstructVSZ(BfmeEntVSZ *dest, const BfmeEntVSZ *source)
{
	new (dest) BfmeEntVSZ(*source);
}

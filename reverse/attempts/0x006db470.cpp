// ??0Rva006DABB0@@QAE@PAVRva006DABB0Source@@H@Z
// partial score=0.79 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// Twin of ??1Rva006DABB0@@UAE@XZ. Retail 0x006DB470 (160 bytes).
// Two stack args: source object and an int stored at +4. Increments g_012F801C.

extern int g_012F801C;

class Rva006DABB0Source
{
public:
	float getFloat(void);
	int *getTriple(void);
	unsigned char m_unmodelled_000[0x3B1];
	unsigned char m_flag3B1;
};

class Rva006DABB0Base
{
public:
	virtual ~Rva006DABB0Base() {}
};

class Rva006DABB0 : public Rva006DABB0Base
{
public:
	Rva006DABB0(Rva006DABB0Source *src, int extra);

	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_unmodelled_011[0x44 - 0x11];
	unsigned char m_44;
	int m_48;
	int m_4C;
	int m_50;
	float m_54;
};

Rva006DABB0::Rva006DABB0(Rva006DABB0Source *src, int extra)
{
	int extraLocal = extra;
	Rva006DABB0Source *srcLocal = src;
	m_04 = extraLocal;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_50 = 0;
	m_54 = 1.0f;
	if (srcLocal)
	{
		m_44 = srcLocal->m_flag3B1;
		m_54 = srcLocal->getFloat();
		int *t = srcLocal->getTriple();
		m_48 = t[0];
		m_4C = t[1];
		m_50 = t[2];
	}
	++g_012F801C;
}

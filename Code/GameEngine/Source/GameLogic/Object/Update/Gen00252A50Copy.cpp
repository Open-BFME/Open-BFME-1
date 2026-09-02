// cl: /DNDEBUG /MD /EHsc
// Open-BFME: 73-byte copy ctor. dword at +0, copy-ctor member at +4 (12 bytes),
// then seven POD dwords at +0x10..+0x28.

struct BfmeLegendStringVec
{
	BfmeLegendStringVec(const BfmeLegendStringVec &other);
	char *m_bfmeStart;
	char *m_bfmeFinish;
	char *m_bfmeEndOfStorage;
};

class Gen00252A50
{
public:
	Gen00252A50(const Gen00252A50 &other);

private:
	int m_key;
	BfmeLegendStringVec m_inner;
	int m_rest[7];
};

// ??0Gen00252A50@@QAE@ABV0@@Z
Gen00252A50::Gen00252A50(const Gen00252A50 &other)
	: m_key(other.m_key), m_inner(other.m_inner)
{
	m_rest[0] = other.m_rest[0];
	m_rest[1] = other.m_rest[1];
	m_rest[2] = other.m_rest[2];
	m_rest[3] = other.m_rest[3];
	m_rest[4] = other.m_rest[4];
	m_rest[5] = other.m_rest[5];
	m_rest[6] = other.m_rest[6];
}

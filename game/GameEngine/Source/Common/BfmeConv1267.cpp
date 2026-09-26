// Open-BFME5 conversions.

extern "C" double __cdecl sin(double a);

extern const float g_bfmeZero1267;
extern const float g_bfmeK1267A;
extern const float g_bfmeK1267B;

struct BfmeVec1267
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeG1267
{
public:
	char m_bfmePad00[0x3c];
	unsigned int m_bfme3c;
};

extern BfmeG1267 *g_bfme1267;

class BfmeA1267
{
public:
	BfmeVec1267 *bfmeGet1267();
	char m_bfmePad00[0x28];
	BfmeVec1267 m_bfme28;
	char m_bfmePad34[0x3c - 0x34];
	float m_bfme3c;
	float m_bfme40;
	BfmeVec1267 m_bfme44;
};

BfmeVec1267 *BfmeA1267::bfmeGet1267()
{
	float s;
	BfmeVec1267 *r;

	if (m_bfme40 != g_bfmeZero1267 && m_bfme3c != g_bfmeZero1267) {
	r = &m_bfme44;
	r->m_bfme00 = m_bfme28.m_bfme00;
	r->m_bfme04 = m_bfme28.m_bfme04;
	r->m_bfme08 = m_bfme28.m_bfme08;

	s = (float)sin((float)g_bfme1267->m_bfme3c * m_bfme40) * *(volatile float *)&m_bfme3c * g_bfmeK1267A + g_bfmeK1267B;
	r->m_bfme00 = r->m_bfme00 * s;
	m_bfme44.m_bfme04 = m_bfme44.m_bfme04 * s;
	m_bfme44.m_bfme08 = m_bfme44.m_bfme08 * s;
		return r;
	}
	return &m_bfme28;
}

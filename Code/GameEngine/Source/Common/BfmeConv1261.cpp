// Open-BFME5 conversions.

extern const float g_bfmeK1261;

struct BfmeVec1261
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeA1261
{
public:
	void bfmeMove1261(const BfmeVec1261 *a);
	char m_bfmePad00[0x0c];
	BfmeVec1261 m_bfme0c;
	int m_bfme18;
	int m_bfme1c;
};

void BfmeA1261::bfmeMove1261(const BfmeVec1261 *a)
{
	BfmeVec1261 t;

	t.m_bfme08 = m_bfme0c.m_bfme08;
	t.m_bfme00 = a->m_bfme00 - m_bfme18 * g_bfmeK1261;
	t.m_bfme04 = a->m_bfme04 - m_bfme1c * g_bfmeK1261;
	m_bfme0c = t;
}

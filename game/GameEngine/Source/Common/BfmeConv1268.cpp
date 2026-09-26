// Open-BFME5 conversions.

extern const float g_bfmeK1268;

struct BfmeVec1268
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1268
{
public:
	virtual void bfmeV1268_00();
	virtual void bfmeV1268_01();
	virtual void bfmeV1268_02();
	virtual void bfmeV1268_03();
	virtual void bfmeV1268_04();
	virtual void bfmeV1268_05();
	virtual float bfmeHeight1268(float a, float b, int c);
};

extern BfmeR1268 *g_bfme1268;

class BfmeA1268
{
public:
	void bfmeCell1268(unsigned int i, BfmeVec1268 *out);
	unsigned int m_bfme00;
	char m_bfmePad04[8];
	float m_bfme0c;
};

void BfmeA1268::bfmeCell1268(unsigned int i, BfmeVec1268 *out)
{
	out->m_bfme00 = (float)(i % m_bfme00) * *(volatile float *)&m_bfme0c + *(volatile float *)&m_bfme0c * g_bfmeK1268;
	out->m_bfme04 = (float)(i / m_bfme00) * *(volatile float *)&m_bfme0c + *(volatile float *)&m_bfme0c * g_bfmeK1268;
	out->m_bfme08 = g_bfme1268->bfmeHeight1268(out->m_bfme00, out->m_bfme04, 0) + g_bfmeK1268;
}

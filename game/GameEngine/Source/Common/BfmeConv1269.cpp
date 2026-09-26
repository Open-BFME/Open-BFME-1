// Open-BFME5 conversions.

extern const float g_bfmeK1269A;
extern const float g_bfmeK1269B;

struct BfmeVec1269
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeG1269
{
public:
	char m_bfmePad00[0xab4];
	float m_bfmeab4;
};

extern BfmeG1269 *g_bfme1269;

class BfmeA1269
{
public:
	virtual void bfmeV1269_00();
	virtual void bfmeV1269_01();
	virtual void bfmeV1269_02();
	virtual void bfmeV1269_03();
	virtual void bfmeV1269_04();
	virtual void bfmeV1269_05();
	virtual void bfmeFill1269(BfmeVec1269 *t, int a, int b, int c, int d);
	void bfmeGet1269(BfmeVec1269 *out, int a, int b, int c, int d);
};

void BfmeA1269::bfmeGet1269(BfmeVec1269 *out, int a, int b, int c, int d)
{
	BfmeVec1269 t;

	bfmeFill1269(&t, a, b, c, d);
	t.m_bfme00 = (*(volatile float *)&g_bfme1269->m_bfmeab4 + g_bfmeK1269A) * g_bfmeK1269B * t.m_bfme00;
	t.m_bfme04 = (*(volatile float *)&g_bfme1269->m_bfmeab4 + g_bfmeK1269A) * g_bfmeK1269B * t.m_bfme04;
	t.m_bfme08 = (*(volatile float *)&g_bfme1269->m_bfmeab4 + g_bfmeK1269A) * g_bfmeK1269B * t.m_bfme08;
	out->m_bfme00 = t.m_bfme00;
	out->m_bfme04 = t.m_bfme04;
	out->m_bfme08 = t.m_bfme08;
}

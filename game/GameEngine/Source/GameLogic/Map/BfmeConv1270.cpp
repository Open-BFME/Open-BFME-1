// Open-BFME5 conversions.

extern const float g_bfmeK1270;

struct BfmeVec1270
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

struct BfmeBox1270
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
	float m_bfme0c;
	float m_bfme10;
	float m_bfme14;
};

class BfmeA1270
{
public:
	virtual void bfmeV1270_00();
	virtual void bfmeV1270_01();
	virtual void bfmeV1270_02();
	virtual void bfmeV1270_03();
	virtual void bfmeV1270_04();
	virtual void bfmeV1270_05();
	virtual float bfmeHeight1270(float a, float b, int c);
	virtual void bfmeV1270_07();
	virtual void bfmeBounds1270(BfmeBox1270 *b);
	void bfmeGet1270(BfmeVec1270 *out, BfmeVec1270 *lim);
};

void BfmeA1270::bfmeGet1270(BfmeVec1270 *out, BfmeVec1270 *lim)
{
	BfmeBox1270 box;
	BfmeVec1270 t;

	bfmeBounds1270(&box);
	if ((box.m_bfme0c - box.m_bfme00) * g_bfmeK1270 > lim->m_bfme00)
		t.m_bfme00 = box.m_bfme0c;
	else
		t.m_bfme00 = box.m_bfme00;
	if ((box.m_bfme10 - box.m_bfme04) * g_bfmeK1270 > lim->m_bfme04)
		t.m_bfme04 = box.m_bfme10;
	else
		t.m_bfme04 = box.m_bfme04;
	t.m_bfme08 = bfmeHeight1270(t.m_bfme00, t.m_bfme04, 0);
	out->m_bfme00 = t.m_bfme00;
	out->m_bfme04 = t.m_bfme04;
	out->m_bfme08 = t.m_bfme08;
}

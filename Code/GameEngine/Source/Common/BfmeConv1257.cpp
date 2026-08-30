// Open-BFME5 conversions.

// Open-BFME5 conversions.

struct BfmeVec1257
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1257
{
public:
	virtual void bfmeV1257_00();
	virtual void bfmeV1257_01();
	virtual void bfmeV1257_02();
	virtual void bfmeV1257_03();
	virtual void bfmeV1257_04();
	virtual void bfmeV1257_05();
	virtual void bfmeV1257_06();
	virtual void bfmeV1257_07();
	virtual void bfmeV1257_08();
	virtual void bfmeV1257_09();
	virtual void bfmeV1257_10();
	virtual void bfmeV1257_11();
	virtual void bfmeMark1257(BfmeVec1257 *p, int a, unsigned int c, int d);
};

extern BfmeR1257 *g_bfme1257;
extern const float g_bfmeK1257;

class BfmeA1257
{
public:
	void bfmeDraw1257(BfmeVec1257 p);
	char m_bfmePad00[0x24];
	union {
		int m_bfme24;
		float m_bfme24f;
	};
};

void BfmeA1257::bfmeDraw1257(BfmeVec1257 p)
{
	p.m_bfme08 = p.m_bfme08 - *(volatile float *)&m_bfme24f * g_bfmeK1257;
	g_bfme1257->bfmeMark1257(&p, m_bfme24, 0xccaaffff, 0);
	p.m_bfme08 = p.m_bfme08 + m_bfme24f;
	g_bfme1257->bfmeMark1257(&p, m_bfme24, 0xccaaffff, 0);
}

// Open-BFME5 conversions.

extern const float g_bfmeK1263;

struct BfmeVec1263
{
	float m_bfme00;
	float m_bfme04;
	float m_bfme08;
};

class BfmeR1263
{
public:
	virtual void bfmeV1263_00();
	virtual void bfmeV1263_01();
	virtual void bfmeV1263_02();
	virtual void bfmeV1263_03();
	virtual void bfmeV1263_04();
	virtual void bfmeV1263_05();
	virtual float bfmeHeight1263(float a, float b, int c);
};

extern BfmeR1263 *g_bfme1263;

extern "C" void bfmeAssert1263(void);

class BfmeA1263
{
public:
	void bfmeGet1263(BfmeVec1263 *out);
	char m_bfmePad00[0x1c];
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	char m_bfmePad2c[4];
	char m_bfme30;
};

void BfmeA1263::bfmeGet1263(BfmeVec1263 *out)
{
	if (!out)
		return;
	if (m_bfme30)
		bfmeAssert1263();
	out->m_bfme00 = (m_bfme1c + m_bfme24) * g_bfmeK1263;
	out->m_bfme04 = (m_bfme20 + m_bfme28) * g_bfmeK1263;
	if (g_bfme1263)
		out->m_bfme08 = g_bfme1263->bfmeHeight1263(out->m_bfme00, out->m_bfme04, 0);
	else
		out->m_bfme08 = 0;
}

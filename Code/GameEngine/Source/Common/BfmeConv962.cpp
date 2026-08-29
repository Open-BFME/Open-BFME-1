// Open-BFME5 conversions.

class BfmeSrc962
{
public:
	virtual void bfmeV0962();
	virtual void bfmeV1962();
	virtual void bfmeV2962();
	virtual void bfmeV3962();
	virtual void bfmeV4962();
	virtual void bfmeV5962();
	virtual void bfmeV6962();
	virtual void bfmeV7962();
	virtual void bfmeV8962();
	virtual void bfmeV9962();
	virtual void bfmeV10962();
	virtual void bfmeV11962();
	virtual void bfmeV12962();
	virtual void bfmeV13962();
	virtual void bfmeV14962();
	virtual void bfmeV15962();
	virtual void bfmeV16962();
	virtual void bfmeV17962();
	virtual void bfmeV18962();
	virtual void bfmeV19962();
	virtual void bfmeV20962();
	virtual void bfmeV21962();
	virtual void bfmeV22962();
	virtual void bfmeV23962();
	virtual void bfmeV24962();
	virtual void bfmeV25962();
	virtual int bfmeStamp962();
};

extern BfmeSrc962 *g_bfmeSrc962;

class BfmeInit962
{
public:
	void bfmeInit962(int a);

	char m_bfmePad[0xb0];
	float m_bfmeScale;
	char m_bfmePad2[0x70];
	int m_bfmeMode;
	int m_bfmeZero;
	int m_bfmeArg;
	char m_bfmePad3[0x1d8];
	int m_bfmeStamp;
};

void BfmeInit962::bfmeInit962(int a)
{
	m_bfmeScale = 1.0f;
	m_bfmeMode = 2;
	m_bfmeArg = a;
	m_bfmeZero = 0;
	m_bfmeStamp = g_bfmeSrc962->bfmeStamp962();
}

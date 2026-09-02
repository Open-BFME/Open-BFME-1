// ?bfmeGoDC@BfmeObjDC@@QAEXXZ
// partial score=0.92 date=2026-09-02
// cl: /O2 /Ob0

extern float g_bfmeKDCMul;

class BfmeHoldDC
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
	virtual int v9();
	virtual int v10();
	virtual int virt2C();
	virtual int virt30();
};

class BfmeObjDC : public BfmeHoldDC
{
public:
	void bfmeGoDC();
	char m_04[0x30];
	BfmeHoldDC *m_34;
	char m_38[0xC0];
	int m_F8;
	float m_FC;
	float m_100;
	float m_104;
	char m_108;
};

void BfmeObjDC::bfmeGoDC()
{
	if (!m_108)
		return;
	BfmeHoldDC *h = m_34;
	if (!h)
		return;
	float ratio = (float)h->virt2C() / (float)h->virt30();
	float a = (float)(unsigned)this->virt2C();
	m_F8 = 0;
	a *= ratio;
	float b = (float)(unsigned)this->virt30() - a;
	m_FC = b * g_bfmeKDCMul;
	m_100 = (float)(unsigned)this->virt2C();
	m_104 = a + m_FC;
}

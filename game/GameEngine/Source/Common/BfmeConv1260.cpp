// Open-BFME5 conversions.

extern const float g_bfmeK1260;

class BfmeV1260
{
public:
	virtual void bfmeV1260_00();
	virtual void bfmeV1260_01();
	virtual void bfmeV1260_02();
	virtual void bfmeV1260_03();
	virtual void bfmeV1260_04();
	virtual void bfmeV1260_05();
	virtual void bfmeV1260_06();
	virtual void bfmeV1260_07();
	virtual void bfmeV1260_08();
	virtual void bfmeV1260_09();
	virtual void bfmeV1260_10();
	virtual void bfmeV1260_11();
	virtual void bfmeV1260_12();
	virtual void bfmeV1260_13();
	virtual void bfmeV1260_14();
	virtual void bfmeV1260_15();
	virtual void bfmeV1260_16();
	virtual void bfmeV1260_17();
	virtual void bfmeApply1260(float a, float b);
};

class BfmeA1260
{
public:
	void bfmeSet1260(float a, float b);
	char m_bfmePad00[0xac];
	float m_bfmeac;
	char m_bfmePadb0[0x150 - 0xb0];
	BfmeV1260 **m_bfme150;
};

void BfmeA1260::bfmeSet1260(float a, float b)
{
	if (*m_bfme150)
		(*m_bfme150)->bfmeApply1260(a, b);
	m_bfmeac = (a + b) * g_bfmeK1260;
}

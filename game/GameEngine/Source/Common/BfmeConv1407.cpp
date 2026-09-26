// Open-BFME5 conversions.

class BfmeBlockVKP
{
public:
	bool bfmeCmpVKP(const BfmeBlockVKP &o);
	void bfmeApplyVKP(int a, int b);
	int m_bfmeArr[10];
};

class BfmeNotifyVKP
{
public:
	void bfmeNotifyVKP(BfmeBlockVKP *b, int x, int y);
};

class BfmeUpdVKP
{
public:
	void bfmeUpdateVKP();
};

class BfmeThingVKP
{
public:
	void bfmeSetVKP(int a, int b);
	char m_bfmePad00[0x80];
	BfmeNotifyVKP *m_bfme80;
	char m_bfmePad84[0x8c];
	BfmeBlockVKP m_bfme110;
	char m_bfmePad138[0xcc];
	BfmeUpdVKP *m_bfme204;
};

void BfmeThingVKP::bfmeSetVKP(int a, int b)
{
	BfmeBlockVKP *cur = &m_bfme110;
	BfmeBlockVKP tmp = m_bfme110;
	cur->bfmeApplyVKP(a, b);
	if (tmp.bfmeCmpVKP(*cur))
	{
		if (m_bfme80)
			m_bfme80->bfmeNotifyVKP(cur, 0, 0);
		if (m_bfme204)
			m_bfme204->bfmeUpdateVKP();
	}
}

class BfmeCZD
{
public:
	void bfmeDoZD(int value, int flag, int spare);

	unsigned char m_bfmeHeadZD[0x28];
	int m_bfmeBaseZD;
};

class BfmeBZD
{
public:
	unsigned char m_bfmeHeadZD[0x210];
	BfmeCZD *m_bfmeCZD;
};

class BfmeAZD
{
public:
	unsigned char m_bfmeHeadZD[0x70];
	int m_bfmeFirstZD;
	int m_bfmeSecondZD;
};

class BfmeOwnerZD
{
public:
	void bfmeAdjustZD(void);
};

void BfmeOwnerZD::bfmeAdjustZD(void)
{
	BfmeAZD *a = *(BfmeAZD **)((char *)this - 0xc);
	BfmeBZD *b = *(BfmeBZD **)((char *)this - 8);
	BfmeCZD *c = b->m_bfmeCZD;

	int first = a->m_bfmeFirstZD;
	int second = a->m_bfmeSecondZD - c->m_bfmeBaseZD;
	const int &value = first < second ? first : second;

	if (value >= 1)
		c->bfmeDoZD(value, 1, 0);
}

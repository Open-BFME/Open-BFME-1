// Open-BFME5 conversions.

class BfmeSub1251
{
public:
	void bfmeSet1251(void *a);
	int m_bfme00;
};

class BfmeSub2_1251
{
public:
	void bfmeUse1251(void *a);
	int m_bfme00;
};

class BfmeS1251
{
public:
	char m_bfmePad00[0x2bc];
	void *m_bfme2bc;
};

class BfmeB1251
{
public:
	void *m_bfme00;
	int m_bfme04;
	void *m_bfme08;
	void *m_bfme0c;
	char m_bfmePad10[4];
	int m_bfme14;
	char m_bfmePad18[0xb4 - 0x18];
	int m_bfmeb4;
};

class BfmeA1251
{
public:
	void bfmeInit1251(BfmeB1251 *b, BfmeS1251 *a);
	int m_bfme00;
	BfmeS1251 *m_bfme04;
	void *m_bfme08;
	int m_bfme0c;
	char m_bfmePad10[0x18 - 0x10];
	void *m_bfme18;
	void *m_bfme1c;
	BfmeSub2_1251 m_bfme20;
	char m_bfmePad24[4];
	BfmeSub1251 m_bfme28;
	char m_bfmePad2c[4];
	BfmeSub1251 m_bfme30;
};

void BfmeA1251::bfmeInit1251(BfmeB1251 *b, BfmeS1251 *a)
{
	m_bfme04 = a;
	m_bfme08 = b->m_bfme00;
	m_bfme18 = b->m_bfme08;
	m_bfme1c = b->m_bfme0c;
	m_bfme28.bfmeSet1251(&b->m_bfme14);
	m_bfme30.bfmeSet1251(&b->m_bfmeb4);
	m_bfme20.bfmeUse1251(m_bfme04->m_bfme2bc);
	m_bfme0c = 1;
}

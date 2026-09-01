// Open-BFME5 conversions.

class BfmeTexVGS
{
public:
	void bfmeReleaseVGS();
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

class BfmeBufVGS
{
public:
	void bfmeSetVGS(int index, BfmeTexVGS **src);
	char m_bfmePad[8];
	BfmeTexVGS **m_bfmeArray;
};

void BfmeBufVGS::bfmeSetVGS(int index, BfmeTexVGS **src)
{
	BfmeTexVGS **p = &m_bfmeArray[index];
	if (*src)
		(*src)->m_bfmeRefs++;
	if (*p)
		(*p)->bfmeReleaseVGS();
	*p = *src;
}

class BfmeMeshVGT
{
public:
	void bfmeSetVGT(BfmeTexVGS **src, int pass, int stage);
	char m_bfmePad[0x74];
	BfmeTexVGS *m_bfmeArr[16];
};

void BfmeMeshVGT::bfmeSetVGT(BfmeTexVGS **src, int pass, int stage)
{
	BfmeTexVGS **p = &m_bfmeArr[pass * 2 + stage];
	if (*src)
		(*src)->m_bfmeRefs++;
	if (*p)
		(*p)->bfmeReleaseVGS();
	*p = *src;
}

class BfmeThingVGV
{
public:
	void __fastcall bfmeSetVGV(BfmeTexVGS **src);
	char m_bfme00;
	char m_bfme01;
	char m_bfmePad[2];
	BfmeTexVGS *m_bfme04;
};

void __fastcall BfmeThingVGV::bfmeSetVGV(BfmeTexVGS **src)
{
	if (m_bfme04 != *src)
	{
		bool a = (*src != 0);
		bool b = (m_bfme04 != 0);
		if (b != a)
			m_bfme00 = 1;
		if (*src)
			(*src)->m_bfmeRefs++;
		if (m_bfme04)
			m_bfme04->bfmeReleaseVGS();
		m_bfme04 = *src;
		m_bfme01 = 1;
	}
}

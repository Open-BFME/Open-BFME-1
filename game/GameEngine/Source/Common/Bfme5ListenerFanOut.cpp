// Open-BFME5 conversions: more fan-outs over the null-terminated item array
// at this+0x150.

extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

class Bfme5FanSub
{
public:
	virtual void bfmeSV0();
	virtual void bfmeSV1();
	virtual void bfmeSV2();
	virtual void bfmeSV3();
	virtual void bfmeSV4();
	virtual void bfmeSV5();
	virtual void bfmeSV6();
	virtual void bfmeSV7();
	virtual void bfmeSV8();
	virtual void bfmeSV9();
	virtual void bfmeSV10();
	virtual void bfmeSV11();
	virtual void bfmeSV12();
	virtual void bfmeSV13();
	virtual void bfmeSV14();
	virtual void bfmeSV15();
	virtual void bfmeSV16();
	virtual void bfmeSV17();
	virtual void bfmeGive(int *a);
	virtual void bfmeSV19();
	virtual void bfmeTake(int *a);
};

class Bfme5FanItem
{
public:
	virtual void bfmeIV0();
	virtual void bfmeIV1();
	virtual void bfmeIV2();
	virtual void bfmeIV3();
	virtual void bfmeIV4();
	virtual void bfmeIV5();
	virtual void bfmeIV6();
	virtual void bfmeIV7();
	virtual void bfmeIV8();
	virtual void bfmeIV9();
	virtual void bfmeIV10();
	virtual void bfmeIV11();
	virtual void bfmeIV12();
	virtual void bfmeIV13();
	virtual void bfmeIV14();
	virtual void bfmeIV15();
	virtual void bfmeIV16();
	virtual void bfmeIV17();
	virtual void bfmeIV18();
	virtual void bfmeIV19();
	virtual void bfmeIV20();
	virtual void bfmeIV21();
	virtual void bfmeIV22();
	virtual void bfmeIV23();
	virtual void bfmeIV24();
	virtual void bfmeIV25();
	virtual void bfmeIV26();
	virtual void bfmeIV27();
	virtual void bfmeIV28();
	virtual void bfmeIV29();
	virtual void bfmeIV30();
	virtual void bfmeIV31();
	virtual void bfmeIV32();
	virtual void bfmeIV33();
	virtual void bfmeIV34();
	virtual void bfmeIV35();
	virtual void bfmeIV36();
	virtual void bfmeIV37();
	virtual void bfmeIV38();
	virtual Bfme5FanSub *bfmeGetSub();
};

class Bfme5FanOwner
{
public:
	void bfmeSetMode(char mode);
	void bfmeResetAll(int *a);

	char m_bfmePad0[0x150];
	Bfme5FanItem **m_bfmeItems;
	char m_bfmePad1[0x124];
	int m_bfme278[10];
	int m_bfme2a0[10];
	char m_bfmePad2[0x52];
	char m_bfme31a;
	char m_bfmePad3[0xa5];
	int *m_bfme3c0;
};

void Bfme5FanOwner::bfmeSetMode(char mode)
{
	int *x = 0;

	m_bfme31a = mode;

	if (mode == 1)
		x = m_bfme3c0;

	for (Bfme5FanItem **p = m_bfmeItems; *p; ++p) {
		Bfme5FanSub *s = (*p)->bfmeGetSub();

		if (s)
			s->bfmeTake(x);
	}
}

void Bfme5FanOwner::bfmeResetAll(int *a)
{
	for (Bfme5FanItem **p = m_bfmeItems; *p; ++p) {
		Bfme5FanSub *s = (*p)->bfmeGetSub();

		if (s)
			s->bfmeGive(a);
	}

	memset(m_bfme2a0, 0, sizeof(m_bfme2a0));
	memset(m_bfme278, 0, sizeof(m_bfme278));
}


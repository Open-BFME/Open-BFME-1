// Open-BFME5 conversions.

class BfmeSubAVHW
{
public:
	void bfmeClearAVHW();
	char m_bfmePad[8];
};

class BfmeSubBVHW
{
public:
	void bfmeClearBVHW();
	char m_bfmePad[12];
};

extern int g_bfmeVftAVHW[];
extern int g_bfmeVftBVHW[];

class BfmeThingVHW
{
public:
	void bfmeClearVHW();
	void *m_bfmeVfptr;
	int m_bfme04;
	char m_bfmePad08[8];
	BfmeSubBVHW m_bfme10;
	BfmeSubBVHW m_bfme1c;
	int m_bfme28;
	int m_bfme2c;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	BfmeSubAVHW m_bfme3c;
	int m_bfme44;
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
	int m_bfme54;
	int m_bfme58;
	int m_bfme5c;
	int m_bfme60;
	char m_bfme64;
	char m_bfme65;
	char m_bfmePad66[2];
	int m_bfme68;
	int m_bfme6c;
	int m_bfme70;
	int m_bfme74;
	int m_bfme78;
};

void BfmeThingVHW::bfmeClearVHW()
{
	m_bfmeVfptr = g_bfmeVftAVHW;
	m_bfme04 = 0;
	m_bfme28 = 0;
	m_bfme2c = 0;
	m_bfme30 = 0;
	m_bfme34 = 0;
	m_bfme38 = 0;
	m_bfme44 = 0;
	m_bfme4c = -1;
	m_bfme50 = 0;
	m_bfme54 = 0;
	m_bfme58 = 0;
	m_bfme5c = 0;
	m_bfme64 = 0;
	m_bfme65 = 0;
	m_bfme68 = 0;
	m_bfme70 = 0;
	m_bfme74 = 0;
	m_bfme6c = 0;
	m_bfme78 = 0;
	m_bfme3c.bfmeClearAVHW();
	m_bfme1c.bfmeClearBVHW();
	m_bfme10.bfmeClearBVHW();
	m_bfmeVfptr = g_bfmeVftBVHW;
}

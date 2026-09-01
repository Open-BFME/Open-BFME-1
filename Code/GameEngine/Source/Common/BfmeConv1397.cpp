// Open-BFME5 conversions.

struct BfmeBlockVKC
{
	int m_bfmeArr[10];
};

class BfmeUniVKC
{
public:
	void bfmeSetVKC(const BfmeUniVKC &o);
	void *m_bfme00;
};

class BfmeThingVKC
{
public:
	void bfmeCopyVKC(const BfmeThingVKC &o);
	int m_bfme00;
	int m_bfme04;
	char m_bfme08;
	char m_bfme09;
	char m_bfmePad0a[2];
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	int m_bfme20;
	int m_bfme24;
	int m_bfme28;
	char m_bfme2c;
	char m_bfme2d;
	char m_bfmePad2e[2];
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
	BfmeUniVKC m_bfme3c;
	int m_bfme40;
	char m_bfme44;
	char m_bfmePad45[3];
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
	BfmeBlockVKC m_bfme54;
	BfmeBlockVKC m_bfme7c;
	BfmeBlockVKC m_bfmea4;
	BfmeBlockVKC m_bfmecc;
	BfmeUniVKC m_bfmef4;
};

void BfmeThingVKC::bfmeCopyVKC(const BfmeThingVKC &o)
{
	m_bfme04 = o.m_bfme04;
	m_bfme08 = o.m_bfme08;
	m_bfme09 = o.m_bfme09;
	m_bfme0c = o.m_bfme0c;
	m_bfme10 = o.m_bfme10;
	m_bfme14 = o.m_bfme14;
	m_bfme18 = o.m_bfme18;
	m_bfme1c = o.m_bfme1c;
	m_bfme20 = o.m_bfme20;
	m_bfme24 = o.m_bfme24;
	m_bfme28 = o.m_bfme28;
	m_bfme2c = o.m_bfme2c;
	m_bfme2d = o.m_bfme2d;
	m_bfme30 = o.m_bfme30;
	m_bfme34 = o.m_bfme34;
	m_bfme38 = o.m_bfme38;
	m_bfme3c.bfmeSetVKC(o.m_bfme3c);
	m_bfme40 = o.m_bfme40;
	m_bfme44 = o.m_bfme44;
	m_bfme48 = o.m_bfme48;
	m_bfme4c = o.m_bfme4c;
	m_bfme50 = o.m_bfme50;
	m_bfme54 = o.m_bfme54;
	m_bfmea4 = o.m_bfmea4;
	m_bfme7c = o.m_bfme7c;
	m_bfmecc = o.m_bfmecc;
	m_bfmef4.bfmeSetVKC(o.m_bfmef4);
}

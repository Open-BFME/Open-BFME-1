// Open-BFME5 conversions.

struct BfmeBlockVKV
{
	int m_bfmeArr[10];
};

class BfmeStrVKV
{
public:
	void bfmeCopyVKV(const BfmeStrVKV &o);
	void *m_bfme00;
};

struct BfmeRefVKV
{
	int m_bfme00;
	int m_bfme04;
};

__declspec(dllimport) void __stdcall bfmeAddRefVKV(void *p);

class BfmeThingVKV
{
public:
	BfmeThingVKV *bfmeInitVKV(const BfmeThingVKV &o);
	BfmeStrVKV m_bfme00;
	BfmeRefVKV *m_bfme04;
	int m_bfme08;
	BfmeBlockVKV m_bfme0c;
	BfmeBlockVKV m_bfme34;
	char m_bfme5c;
};

BfmeThingVKV *BfmeThingVKV::bfmeInitVKV(const BfmeThingVKV &o)
{
	m_bfme00.bfmeCopyVKV(o.m_bfme00);
	m_bfme04 = o.m_bfme04;
	if (m_bfme04)
		bfmeAddRefVKV(&m_bfme04->m_bfme04);
	m_bfme08 = o.m_bfme08;
	m_bfme0c = o.m_bfme0c;
	m_bfme34 = o.m_bfme34;
	m_bfme5c = o.m_bfme5c;
	return this;
}

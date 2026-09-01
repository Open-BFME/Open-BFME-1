// Open-BFME5 conversions.

class BfmeUniVKE
{
public:
	void bfmeCopyUVKE(const BfmeUniVKE &o);
	void *m_bfme00;
};

struct BfmeBlockVKE
{
	int m_bfmeArr[16];
};

class BfmeThingVKE
{
public:
	BfmeThingVKE *bfmeInitVKE(const BfmeThingVKE &o);
	BfmeUniVKE m_bfme00;
	char m_bfme04;
	char m_bfmePad05[3];
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBlockVKE m_bfme18;
};

BfmeThingVKE *BfmeThingVKE::bfmeInitVKE(const BfmeThingVKE &o)
{
	m_bfme00.bfmeCopyUVKE(o.m_bfme00);
	m_bfme04 = o.m_bfme04;
	m_bfme08 = o.m_bfme08;
	m_bfme0c = o.m_bfme0c;
	m_bfme10 = o.m_bfme10;
	m_bfme14 = o.m_bfme14;
	m_bfme18 = o.m_bfme18;
	return this;
}

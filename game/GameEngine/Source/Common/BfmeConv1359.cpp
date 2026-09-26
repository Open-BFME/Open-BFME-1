// Open-BFME5 conversions.

class BfmeTexVGX
{
public:
	void bfmeReleaseVGX();
	int m_bfme00;
	unsigned short m_bfmeRefs;
};

class BfmeThingVGX
{
public:
	BfmeThingVGX &bfmeAssignVGX(const BfmeThingVGX &o);
	BfmeTexVGX *m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	int m_bfme18;
	int m_bfme1c;
	char m_bfme20;
};

BfmeThingVGX &BfmeThingVGX::bfmeAssignVGX(const BfmeThingVGX &o)
{
	if (this != &o)
	{
		if (o.m_bfme00)
			o.m_bfme00->m_bfmeRefs++;
		if (m_bfme00)
			m_bfme00->bfmeReleaseVGX();
		m_bfme00 = o.m_bfme00;
		m_bfme04 = o.m_bfme04;
		m_bfme08 = o.m_bfme08;
		m_bfme0c = o.m_bfme0c;
		m_bfme10 = o.m_bfme10;
		m_bfme14 = o.m_bfme14;
		m_bfme18 = o.m_bfme18;
		m_bfme20 = o.m_bfme20;
		m_bfme1c = o.m_bfme1c;
	}
	return *this;
}

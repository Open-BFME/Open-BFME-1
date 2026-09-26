// Open-BFME5 conversions.

class BfmeSubAVIK
{
public:
	void bfmeAssignAVIK(const BfmeSubAVIK &o);
	char m_bfmePad[0x50];
};

class BfmeSubBVIK
{
public:
	void bfmeAssignBVIK(const BfmeSubBVIK &o);
	char m_bfmePad[0x10];
};

class BfmeThingVIK
{
public:
	BfmeThingVIK &bfmeAssignVIK(const BfmeThingVIK &o);
	void bfmeBaseVIK(const BfmeThingVIK &o);
	char m_bfmePad[0xc8];
	int m_bfmec8;
	int m_bfmecc;
	int m_bfmed0;
	int m_bfmed4;
	int m_bfmed8;
	int m_bfmedc;
	int m_bfmee0;
	int m_bfmee4;
	int m_bfmee8;
	int m_bfmeec;
	int m_bfmef0;
	int m_bfmef4;
	int m_bfmef8;
	int m_bfmefc;
	int m_bfme100;
	BfmeSubAVIK m_bfme104;
	BfmeSubBVIK m_bfme154;
};

BfmeThingVIK &BfmeThingVIK::bfmeAssignVIK(const BfmeThingVIK &o)
{
	bfmeBaseVIK(o);
	if (this != &o)
	{
		m_bfmec8 = o.m_bfmec8;
		m_bfmed0 = o.m_bfmed0;
		m_bfmed8 = o.m_bfmed8;
		m_bfmedc = o.m_bfmedc;
		m_bfmee0 = o.m_bfmee0;
		m_bfmee8 = o.m_bfmee8;
		m_bfmeec = o.m_bfmeec;
		m_bfmef0 = o.m_bfmef0;
		m_bfmef8 = o.m_bfmef8;
		m_bfmefc = o.m_bfmefc;
		m_bfme100 = o.m_bfme100;
		m_bfme104.bfmeAssignAVIK(o.m_bfme104);
		m_bfme154.bfmeAssignBVIK(o.m_bfme154);
		m_bfmecc = o.m_bfmecc;
	}
	return *this;
}

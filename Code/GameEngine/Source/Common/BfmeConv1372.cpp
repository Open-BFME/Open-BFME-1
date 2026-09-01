// Open-BFME5 conversions.

class BfmePartVID
{
public:
	int bfmeComputeVID();
};

class BfmePartBVID
{
public:
	int bfmeComputeBVID();
};

class BfmeThingVID
{
public:
	int bfmeSizeVID();
	BfmePartVID *m_bfme00;
	BfmePartVID *m_bfme04;
	BfmePartVID *m_bfme08;
	BfmePartVID *m_bfme0c;
	BfmePartVID *m_bfme10;
	BfmePartVID *m_bfme14;
	BfmePartVID *m_bfme18;
	int m_bfme1c;
	BfmePartBVID *m_bfme20;
};

int BfmeThingVID::bfmeSizeVID()
{
	int total = 0x24;
	if (m_bfme00)
		total = m_bfme00->bfmeComputeVID() + 0x24;
	if (m_bfme04)
		total += m_bfme04->bfmeComputeVID();
	if (m_bfme08)
		total += m_bfme08->bfmeComputeVID();
	if (m_bfme0c)
		total += m_bfme0c->bfmeComputeVID();
	if (m_bfme10)
		total += m_bfme10->bfmeComputeVID();
	if (m_bfme14)
		total += m_bfme14->bfmeComputeVID();
	if (m_bfme18)
		total += m_bfme18->bfmeComputeVID();
	if (m_bfme20)
		total += m_bfme20->bfmeComputeBVID();
	return total;
}

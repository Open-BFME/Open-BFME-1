class BfmeItemYQ;

struct BfmeKeyYQ
{
	unsigned char m_bfmeBytesYQ[4];
};

class BfmeItemYQ
{
public:
	unsigned char m_bfmeHeadYQ[0x20];
	BfmeKeyYQ m_bfmeKeyYQ;
	unsigned char m_bfmeMidYQ[0x368];
	BfmeItemYQ *m_bfmeNextYQ;
};

class BfmeMapYQ
{
public:
	void bfmeEraseYQ(BfmeKeyYQ *key);
	BfmeItemYQ **bfmeSlotYQ(BfmeKeyYQ *key);
};

class BfmeOwnerYQ
{
public:
	void bfmeAddYQ(BfmeItemYQ *item);

	unsigned char m_bfmeHeadYQ[8];
	BfmeItemYQ *m_bfmeListYQ;
	unsigned char m_bfmePadYQ[4];
	BfmeMapYQ m_bfmeMapYQ;
};

void BfmeOwnerYQ::bfmeAddYQ(BfmeItemYQ *item)
{
	m_bfmeMapYQ.bfmeEraseYQ(&item->m_bfmeKeyYQ);

	item->m_bfmeNextYQ = m_bfmeListYQ;
	m_bfmeListYQ = item;

	*m_bfmeMapYQ.bfmeSlotYQ(&item->m_bfmeKeyYQ) = item;
}

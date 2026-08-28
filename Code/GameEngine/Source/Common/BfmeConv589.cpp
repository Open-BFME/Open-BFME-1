struct BfmeListCEF
{
	unsigned char m_bfmeHead[4];
};

struct BfmeOwnerCEF
{
	unsigned char m_bfmeHead[0x20];
	BfmeListCEF m_bfmeList;
};

class BfmeSubCEF
{
public:
	void bfmeAttachCEF(BfmeListCEF *list);
	unsigned char m_bfmeHead[4];
};

class BfmeThingCEF
{
public:
	void bfmeOneCEF();
	void bfmeTwoCEF();
	void bfmeGoCEF(BfmeOwnerCEF *owner);
	unsigned char m_bfmeHead[0x14];
	BfmeSubCEF m_bfmeSub;
	BfmeOwnerCEF *m_bfmeOwner;
};

void BfmeThingCEF::bfmeGoCEF(BfmeOwnerCEF *owner)
{
	m_bfmeOwner = owner;
	m_bfmeSub.bfmeAttachCEF(&owner->m_bfmeList);
	bfmeOneCEF();
	bfmeTwoCEF();
}

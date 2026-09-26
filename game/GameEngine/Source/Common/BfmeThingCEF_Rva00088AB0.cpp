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
	const BfmeListCEF *rva00088AB0CEF(void) const;

	unsigned char m_bfmeHead[0x14];
	BfmeSubCEF m_bfmeSub;
	BfmeOwnerCEF *m_bfmeOwner;
};

const BfmeListCEF *BfmeThingCEF::rva00088AB0CEF(void) const
{
	BfmeOwnerCEF *owner = m_bfmeOwner;
	if (owner != 0)
	{
		void *candidate = *(void **)((char *)owner + 0x24);
		BfmeListCEF *result;
		if (candidate != 0)
		{
			if (*(unsigned short *)((char *)candidate + 4) != 0)
				result = (BfmeListCEF *)((char *)owner + 0x24);
			else
				result = (BfmeListCEF *)((char *)owner + 0x20);
		}
		else
			result = (BfmeListCEF *)((char *)owner + 0x20);
		return result;
	}
	return (BfmeListCEF *)((char *)this + 0x14);
}
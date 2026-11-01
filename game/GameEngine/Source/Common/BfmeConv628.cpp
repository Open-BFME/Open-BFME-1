class BfmeInnerCPB
{
public:
	void bfmeOneCPB(int one, int two);
};

struct BfmeMidCPB
{
	unsigned char m_bfmeHead[0x20];
	BfmeInnerCPB m_bfmeInner;
};

// ILT 0x0003E126 -> matched body 0x001BEEB0, Object::setSelectable.
class Object
{
public:
	void setSelectable(bool selectable);
};

struct BfmeSubCPB
{
	unsigned char m_bfmeHead[0x94];
	unsigned int m_bfmeFlags;
	unsigned char m_bfmeGap[0x16c];
	BfmeMidCPB *m_bfmeMid;
};

class BfmeThingCPB
{
public:
	void bfmeGoCPB();
	unsigned char m_bfmeHead[8];
	BfmeSubCPB *m_bfmeSub;
};

void BfmeThingCPB::bfmeGoCPB()
{
	BfmeSubCPB *sub = m_bfmeSub;
	if (sub->m_bfmeFlags & 0x20)
		return;
	BfmeMidCPB *mid = sub->m_bfmeMid;
	if (mid == 0)
		return;
	mid->m_bfmeInner.bfmeOneCPB(0, 2);
	((Object *)sub)->setSelectable(false);
}

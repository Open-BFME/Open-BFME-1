// A record taken over from another: the incoming charge is taken up, the old
// one let go of, and the whole record copied across.

class BfmeItemFT;

struct BfmeOpsFT
{
	void (__stdcall *m_bfmeSpare)(BfmeItemFT *item);
	void (__stdcall *m_bfmeAdd)(BfmeItemFT *item);
	void (__stdcall *m_bfmeDrop)(BfmeItemFT *item);
};

struct BfmeItemFT
{
	BfmeOpsFT *m_bfmeOps;			// 0x0
};

class BfmeThingFT
{
public:
	BfmeThingFT &bfmeTakeFT(const BfmeThingFT *from);

private:
	BfmeItemFT *m_bfmeItem;			// 0x00
	int m_bfmeFirst;			// 0x04
	int m_bfmeSecond;			// 0x08
	int m_bfmeThird;			// 0x0c
	int m_bfmeFourth;			// 0x10
	int m_bfmeFifth;			// 0x14
	int m_bfmeSixth;			// 0x18
	int m_bfmeSeventh;			// 0x1c
	int m_bfmeEighth;			// 0x20
};

BfmeThingFT &BfmeThingFT::bfmeTakeFT(const BfmeThingFT *from)
{
	BfmeItemFT *item = from->m_bfmeItem;

	if (item != 0)
		item->m_bfmeOps->m_bfmeAdd(item);

	BfmeItemFT *mine = m_bfmeItem;

	if (mine != 0)
		mine->m_bfmeOps->m_bfmeDrop(mine);

	m_bfmeItem = from->m_bfmeItem;
	m_bfmeFirst = from->m_bfmeFirst;
	m_bfmeSecond = from->m_bfmeSecond;
	m_bfmeThird = from->m_bfmeThird;
	m_bfmeFourth = from->m_bfmeFourth;
	m_bfmeFifth = from->m_bfmeFifth;
	m_bfmeSixth = from->m_bfmeSixth;
	m_bfmeSeventh = from->m_bfmeSeventh;
	m_bfmeEighth = from->m_bfmeEighth;

	return *this;
}


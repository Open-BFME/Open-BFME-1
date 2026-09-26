// A mark set on an item according to whose side it is on, and a reading handed
// back through a caller's own record, blank unless the thing is of the right
// sort.

class BfmeSideYF
{
public:
	unsigned char m_bfmeHead[0x28];		// 0x00
	int m_bfmeKind;				// 0x28
};

class BfmeItemYF
{
public:
	unsigned char m_bfmeHead[0x14];		// 0x00
	BfmeSideYF *m_bfmeSide;			// 0x14
	unsigned char m_bfmeBody[0x23];		// 0x18
	unsigned char m_bfmeOdd;		// 0x3b
};

class BfmeBoxYF
{
public:
	BfmeItemYF *m_bfmeItem;			// 0x00
};

class BfmeThingYF
{
public:
	void bfmeMarkYF(BfmeBoxYF *box) const;

private:
	unsigned char m_bfmeHead[0x604];	// 0x000
	int m_bfmeKind;				// 0x604
};

void BfmeThingYF::bfmeMarkYF(BfmeBoxYF *box) const
{
	BfmeItemYF *item = box->m_bfmeItem;
	int kind = item->m_bfmeSide->m_bfmeKind;

	if (kind != 2 && kind != m_bfmeKind)
		item->m_bfmeOdd = 1;
	else
		item->m_bfmeOdd = 0;
}

struct BfmeVecYG
{
	int m_bfmeAcross;			// 0x0
	int m_bfmeUp;				// 0x4
	int m_bfmeAlong;			// 0x8
};

class BfmeThingYG
{
public:
	void bfmeReadYG(BfmeVecYG *out) const;

private:
	int m_bfmeSort;				// 0x00
	unsigned char m_bfmeGap[0x10];		// 0x04
	BfmeVecYG m_bfmeWhere;			// 0x14
};

void BfmeThingYG::bfmeReadYG(BfmeVecYG *out) const
{
	out->m_bfmeAlong = 0;
	out->m_bfmeUp = 0;
	out->m_bfmeAcross = 0;

	if (m_bfmeSort == 0x10)
		*out = m_bfmeWhere;
}

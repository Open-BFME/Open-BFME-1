// Two more: the twin of the owner unlink and a bounds update.

class BfmeOwnerEI
{
public:
	int m_bfmeFirst;					// +0x00
	int m_bfmeHead[8];					// +0x04
	unsigned int m_bfmeFlags;				// +0x24
	int m_bfmeGap;						// +0x28
	BfmeOwnerEI *m_bfmePrev;				// +0x2C
	BfmeOwnerEI *m_bfmeNext;				// +0x30
};

class Gen_003F6A20
{
public:
	void bfmeDetach(void);

private:
	BfmeOwnerEI *m_bfmeOwner;				// +0x00
};

// ?bfmeDetach@Gen_003F6A20@@QAEXXZ
void Gen_003F6A20::bfmeDetach(void)
{
	BfmeOwnerEI *owner = m_bfmeOwner;

	BfmeOwnerEI *next = owner->m_bfmeNext;

	if (next != 0)
	{
		next->m_bfmeFirst = (int)owner->m_bfmePrev;

		BfmeOwnerEI *previous = owner->m_bfmePrev;

		if (previous != 0)
			previous->m_bfmeNext = owner->m_bfmeNext;

		owner->m_bfmeNext = 0;
		owner->m_bfmePrev = 0;
	}

	m_bfmeOwner->m_bfmeFlags = m_bfmeOwner->m_bfmeFlags & ~0x10;
}

class Gen_00470870
{
public:
	void bfmeExtend(int left, int top, int right, int bottom);

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeLeft;						// +0x08
	int m_bfmeTop;						// +0x0C
	int m_bfmeRight;					// +0x10
	int m_bfmeBottom;					// +0x14
};

// ?bfmeExtend@Gen_00470870@@QAEXHHHH@Z
void Gen_00470870::bfmeExtend(int left, int top, int right, int bottom)
{
	if (m_bfmeLeft > left)
		m_bfmeLeft = left;

	if (m_bfmeRight < right)
		m_bfmeRight = right;

	if (m_bfmeTop > top)
		m_bfmeTop = top;

	if (m_bfmeBottom < bottom)
		m_bfmeBottom = bottom;
}

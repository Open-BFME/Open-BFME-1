// cl: /MD /O2 /EHsc- /GR-

class BfmeSubBOB;

struct BfmeGotBOB
{
public:
	int m_vtable;
	BfmeSubBOB *m_bob;
	int m_pad[2];
	int m_order;
};

class BfmeSubBOB
{
public:
	BfmeGotBOB *bfmeFindBOB(void);
};

class BfmeCompareBOB
{
public:
	bool lessThan(BfmeCompareBOB *other);
	bool greaterThan(BfmeCompareBOB *other);

private:
	int m_vtable;
	BfmeGotBOB *m_item;
	int m_pad[2];
	int m_order;
};

// ?lessThan@BfmeCompareBOB@@QAE_NPAV1@@Z
bool BfmeCompareBOB::lessThan(BfmeCompareBOB *other)
{
	BfmeGotBOB *item = m_item;
	BfmeGotBOB *left;
	if (item != 0)
	{
	BfmeSubBOB *bob = item->m_bob;
		if (bob != 0)
			left = bob->bfmeFindBOB();
		else
			left = item;
	}
	else
		left = (BfmeGotBOB *)this;

	item = other->m_item;
	BfmeGotBOB *right;
	if (item != 0)
	{
		BfmeSubBOB *bob = item->m_bob;
		if (bob != 0)
			right = bob->bfmeFindBOB();
		else
			right = item;
	}
	else
		right = (BfmeGotBOB *)other;

	if (left == 0 || right == 0)
		return false;

	return left->m_order < right->m_order;
}

// ?greaterThan@BfmeCompareBOB@@QAE_NPAV1@@Z
bool BfmeCompareBOB::greaterThan(BfmeCompareBOB *other)
{
	BfmeGotBOB *item = m_item;
	BfmeGotBOB *left;
	if (item != 0)
	{
		BfmeSubBOB *bob = item->m_bob;
		if (bob != 0)
			left = bob->bfmeFindBOB();
		else
			left = item;
	}
	else
		left = (BfmeGotBOB *)this;

	item = other->m_item;
	BfmeGotBOB *right;
	if (item != 0)
	{
		BfmeSubBOB *bob = item->m_bob;
		if (bob != 0)
			right = bob->bfmeFindBOB();
		else
			right = item;
	}
	else
		right = (BfmeGotBOB *)other;

	if (left == 0 || right == 0)
		return false;

	return left->m_order > right->m_order;
}

// Three walks: one over a fixed table looking for a key, one comparing two runs
// of numbers, and one counting how many cells carry a given mark.

struct BfmePairYL
{
	int m_bfmeKey;				// 0x0
	int m_bfmeValue;			// 0x4
};

class BfmeTableYL
{
public:
	BfmePairYL *bfmeFindYL(int key);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmePairYL m_bfmePairs[13];		// 0x10
};

BfmePairYL *BfmeTableYL::bfmeFindYL(int key)
{
	for (int i = 0; i < 13; ++i)
	{
		if (m_bfmePairs[i].m_bfmeKey == key)
			return &m_bfmePairs[i];
	}

	return 0;
}

unsigned char bfmeSameYM(const int *first, const int *last, const int *other)
{
	while (first != last)
	{
		if (*first != *other)
			return 0;

		++first;
		++other;
	}

	return 1;
}

struct BfmeItemYN
{
	unsigned char m_bfmeHead[0x14];		// 0x00
	int m_bfmeMark;				// 0x14
};

struct BfmeCellYN
{
	BfmeItemYN *m_bfmeItem;			// 0x0
	BfmeCellYN *m_bfmeNext;			// 0x4
};

class BfmeThingYN
{
public:
	int bfmeCountYN(int mark) const;

private:
	unsigned char m_bfmeHead[8];		// 0x0
	BfmeCellYN *m_bfmeList;			// 0x8
};

int BfmeThingYN::bfmeCountYN(int mark) const
{
	int count = 0;
	BfmeCellYN *list = m_bfmeList;

	if (list != 0)
	{
		BfmeCellYN *cell = list->m_bfmeNext;

		while (cell != 0)
		{
			if (cell->m_bfmeItem->m_bfmeMark == mark)
				++count;

			cell = cell->m_bfmeNext;
		}
	}

	return count;
}

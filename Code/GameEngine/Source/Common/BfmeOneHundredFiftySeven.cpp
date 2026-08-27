// A triple added to a short fixed list, a reading taken only when something has
// really changed, and a walk down a sorted tree for the first entry that is not
// below a key.

struct BfmeVecZB
{
	int m_bfmeAcross;			// 0x0
	int m_bfmeUp;				// 0x4
	int m_bfmeAlong;			// 0x8
};

class BfmeListZB
{
public:
	unsigned char bfmeAddZB(const BfmeVecZB *value);

private:
	unsigned char m_bfmeHead[0x74];		// 0x000
	BfmeVecZB m_bfmeItems[16];		// 0x074
	int m_bfmeCount;			// 0x134
};

unsigned char BfmeListZB::bfmeAddZB(const BfmeVecZB *value)
{
	if (m_bfmeCount < 16)
	{
		m_bfmeItems[m_bfmeCount] = *value;
		++m_bfmeCount;

		return 1;
	}

	return 0;
}

struct BfmeOwnerZC
{
	unsigned char m_bfmeHead[0x20];		// 0x00
	int m_bfmeMark;				// 0x20
};

struct BfmeBoxZC
{
	BfmeOwnerZC *m_bfmeOwner;		// 0x0
	int m_bfmeSpare;			// 0x4
	unsigned short m_bfmeKind;		// 0x8
};

class BfmeThingZC
{
public:
	int bfmeSetZC(int spare, const BfmeBoxZC *box, int which, int extra);

private:
	int m_bfmeFirst;			// 0x00
	int m_bfmeMark;				// 0x04
	int m_bfmeKind;				// 0x08
	int m_bfmeWhich;			// 0x0c
	int m_bfmeExtra;			// 0x10
};

int BfmeThingZC::bfmeSetZC(int spare, const BfmeBoxZC *box, int which, int extra)
{
	BfmeOwnerZC *owner = box->m_bfmeOwner;
	int mark = (owner != 0) ? owner->m_bfmeMark : 0;

	if (mark != m_bfmeMark)
	{
		m_bfmeKind = box->m_bfmeKind;
		m_bfmeWhich = which;
		m_bfmeExtra = extra;

		return 1;
	}

	return 0;
}

struct BfmeNodeZA
{
	unsigned char m_bfmeHead[4];		// 0x00
	BfmeNodeZA *m_bfmeRoot;			// 0x04
	BfmeNodeZA *m_bfmeLeft;			// 0x08
	BfmeNodeZA *m_bfmeRight;		// 0x0c
	unsigned char m_bfmeBody[0x18];		// 0x10
	unsigned int m_bfmeKey;			// 0x28
};

struct BfmeIterZA
{
	BfmeNodeZA *m_bfmeNode;			// 0x0
};

struct BfmeWantZA
{
	unsigned char m_bfmeHead[0x18];		// 0x00
	unsigned int m_bfmeKey;			// 0x18
};

class BfmeTreeZA
{
public:
	BfmeIterZA bfmeLowerZA(const BfmeWantZA *want) const;

private:
	BfmeNodeZA *m_bfmeHead;			// 0x0
};

BfmeIterZA BfmeTreeZA::bfmeLowerZA(const BfmeWantZA *want) const
{
	BfmeNodeZA *head = m_bfmeHead;
	BfmeNodeZA *found = head;
	BfmeNodeZA *at = head->m_bfmeRoot;

	while (at != 0)
	{
		if (at->m_bfmeKey >= want->m_bfmeKey)
		{
			found = at;
			at = at->m_bfmeLeft;
		}
		else
			at = at->m_bfmeRight;
	}

	BfmeIterZA result;

	result.m_bfmeNode = found;

	return result;
}

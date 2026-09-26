// Three vector clears that copy an empty range over themselves.
//
// The self-comparison and the subtraction of a register from itself come from
// the copy helper being handed the same member for both ends of its range;
// after inlining both parameters live in one register and MSVC still emits
// what it was asked for.
//
// All three walk the vector first and read the bound straight from the member,
// both for the entry test and for the reload inside the loop: there is no
// local, so the compare against the member is a memory operand. Two of them
// delete their elements through the vftable and so test for null first; the
// third calls a deleting helper directly with a flag of 1 and has no test.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeOwnedC
{
public:
	virtual ~BfmeOwnedC(void);				// slot +0x00
};

inline BfmeOwnedC **bfmeCopySlots(BfmeOwnedC **destination, BfmeOwnedC **first, BfmeOwnedC **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedC **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class Gen_003788C0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeOwnedC **m_bfmeStart;				// +0x0C
	BfmeOwnedC **m_bfmeFinish;				// +0x10
	BfmeOwnedC **m_bfmeEnd;					// +0x14
};

// ?bfmeClear@Gen_003788C0@@QAEXXZ
void Gen_003788C0::bfmeClear(void)
{
	BfmeOwnedC **it = m_bfmeStart;

	while (it != m_bfmeFinish)
	{
		delete *it;

		++it;
	}

	m_bfmeFinish = bfmeCopySlots(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
}

class Gen_003C1230
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[23];					// +0x00
	BfmeOwnedC **m_bfmeStart;				// +0x5C
	BfmeOwnedC **m_bfmeFinish;				// +0x60
	BfmeOwnedC **m_bfmeEnd;					// +0x64
};

// ?bfmeClear@Gen_003C1230@@QAEXXZ
void Gen_003C1230::bfmeClear(void)
{
	BfmeOwnedC **it = m_bfmeStart;

	while (it != m_bfmeFinish)
	{
		delete *it;

		++it;
	}

	m_bfmeFinish = bfmeCopySlots(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
}

class BfmeOwnedD
{
public:
	void *bfmeDeleteSelf(unsigned int flags);		// retail thunk 0x0000E4A8 -> 0x001CBDC0
};

inline BfmeOwnedD **bfmeCopyOwned(BfmeOwnedD **destination, BfmeOwnedD **first, BfmeOwnedD **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedD **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class Gen_0038A6F0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[87];					// +0x000
	BfmeOwnedD **m_bfmeStart;				// +0x15C
	BfmeOwnedD **m_bfmeFinish;				// +0x160
	BfmeOwnedD **m_bfmeEnd;					// +0x164
};

// ?bfmeClear@Gen_0038A6F0@@QAEXXZ
void Gen_0038A6F0::bfmeClear(void)
{
	BfmeOwnedD **it = m_bfmeStart;

	while (it != m_bfmeFinish)
	{
		(*it)->bfmeDeleteSelf(1);

		++it;
	}

	m_bfmeFinish = bfmeCopyOwned(m_bfmeStart, m_bfmeFinish, m_bfmeFinish);
}

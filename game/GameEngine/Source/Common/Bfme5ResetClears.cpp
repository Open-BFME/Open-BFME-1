// A reset that empties its vector and puts the fields around it back to their
// defaults, and a plain clear that deletes its elements first.
//
// The zeroes and the flag share one register, so they are all written in one
// run; the float is an immediate because 1.0f is not zero. The store of the
// new finish comes last on both paths, which is where the vector's own erase
// puts it.
//
// The flag is written after the clear, not with the other defaults: that is
// what keeps the zero in a callee-saved register across the copy and gets the
// byte store duplicated into both paths.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecJ
{
public:
	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class Gen_00459F00
{
public:
	void bfmeReset(void);

private:
	BfmeVecJ m_bfmeVector;					// +0x00
	int m_bfmeCount;					// +0x0C
	int m_bfmeIndex;					// +0x10
	float m_bfmeScale;					// +0x14
	int m_bfmeState;					// +0x18
	bool m_bfmeFlag;					// +0x1C
};

// ?bfmeReset@Gen_00459F00@@QAEXXZ
void Gen_00459F00::bfmeReset(void)
{
	m_bfmeCount = 0;
	m_bfmeIndex = 0;
	m_bfmeScale = 1.0f;
	m_bfmeState = 0;

	m_bfmeVector.bfmeClear();

	m_bfmeFlag = false;
}

class BfmeOwnedJ
{
public:
	virtual ~BfmeOwnedJ(void);				// slot +0x00
};

inline BfmeOwnedJ **bfmeCopyOwned(BfmeOwnedJ **destination, BfmeOwnedJ **first, BfmeOwnedJ **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedJ **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecK
{
public:
	void bfmeErase(BfmeOwnedJ **first, BfmeOwnedJ **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedJ **m_bfmeStart;				// +0x00
	BfmeOwnedJ **m_bfmeFinish;				// +0x04
	BfmeOwnedJ **m_bfmeEnd;					// +0x08
};

class Gen_00419DC0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[190];					// +0x000
	BfmeVecK m_bfmeVector;					// +0x2F8
};

// ?bfmeClear@Gen_00419DC0@@QAEXXZ
void Gen_00419DC0::bfmeClear(void)
{
	BfmeOwnedJ **it = m_bfmeVector.m_bfmeStart;

	while (it != m_bfmeVector.m_bfmeFinish)
	{
		delete *it;

		++it;
	}

	m_bfmeVector.bfmeClear();
}

// Two counted clears: the span is recomputed on every pass, so it is the
// condition of a for loop, and the unsigned compares make the index unsigned
// even though the shift that divides the pointer difference is signed.
//
// The first sets two fields after emptying, both duplicated into the two
// paths. The second releases the string it derives from first and deletes its
// elements by hand -- destructor call and free are separate, so that element
// type's destructor is not virtual.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

class BfmeOwnedM
{
public:
	virtual ~BfmeOwnedM(void);				// slot +0x00
};

inline BfmeOwnedM **bfmeCopyOwned(BfmeOwnedM **destination, BfmeOwnedM **first, BfmeOwnedM **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeOwnedM **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecM
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeOwnedM *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeOwnedM **first, BfmeOwnedM **last)
	{
		m_bfmeFinish = bfmeCopyOwned(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeOwnedM **m_bfmeStart;				// +0x00
	BfmeOwnedM **m_bfmeFinish;				// +0x04
	BfmeOwnedM **m_bfmeEnd;					// +0x08
};

class Gen_001B98B0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead;						// +0x00
	BfmeVecM m_bfmeVector;					// +0x04
	int m_bfmeCount;					// +0x10
	bool m_bfmeFlag;					// +0x14
};

// ?bfmeClear@Gen_001B98B0@@QAEXXZ
void Gen_001B98B0::bfmeClear(void)
{
	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
		delete m_bfmeVector.bfmeAt(index);

	m_bfmeVector.bfmeClear();

	m_bfmeCount = 0;
	m_bfmeFlag = false;
}

class BfmeElemN
{
public:
	~BfmeElemN(void);					// retail thunk 0x000295FF -> 0x0060AA70
};

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0

inline BfmeElemN **bfmeCopyElems(BfmeElemN **destination, BfmeElemN **first, BfmeElemN **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemN **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecN
{
public:
	unsigned int bfmeSize(void) const
	{
		return (unsigned int)(m_bfmeFinish - m_bfmeStart);
	}

	BfmeElemN *bfmeAt(unsigned int index) const
	{
		return m_bfmeStart[index];
	}

	void bfmeErase(BfmeElemN **first, BfmeElemN **last)
	{
		m_bfmeFinish = bfmeCopyElems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeElemN **m_bfmeStart;				// +0x00
	BfmeElemN **m_bfmeFinish;				// +0x04
	BfmeElemN **m_bfmeEnd;					// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
protected:
	void releaseBuffer(void);				// retail 0x00887940

private:
	void *m_bfmeData;					// +0x00
};

class Gen_0060B470 : public AsciiString
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[2];					// +0x04
	BfmeVecN m_bfmeVector;					// +0x0C
};

// ?bfmeClear@Gen_0060B470@@QAEXXZ
void Gen_0060B470::bfmeClear(void)
{
	releaseBuffer();

	for (unsigned int index = 0; index < m_bfmeVector.bfmeSize(); ++index)
	{
		BfmeElemN *element = m_bfmeVector.bfmeAt(index);

		if (element)
		{
			element->~BfmeElemN();

			bfmeFreeScalar(element);
		}
	}

	m_bfmeVector.bfmeClear();
}

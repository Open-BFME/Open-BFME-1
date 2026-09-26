// A body that empties two vectors of a different element width in a row.
//
// Each vector empties itself the way a vector does: clear() calls erase() with
// its own two ends, and erase() hands the copy helper a range whose ends are a
// parameter and the member the call site read for it. Both land in one
// register after inlining, so the comparison of a register against itself and
// the subtraction that yields zero survive. Comparing the two ends directly in
// the body of a method instead folds the whole thing away.
//
// The store of each new finish has to be written by a method of the vector
// subobject. Written at this level -- or from an inline method of the holder,
// or through a pointer to the member -- MSVC sinks the first vector's store
// past the load and the self-compare of the second.

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source, unsigned int bytes);

inline int *bfmeCopyInts(int *destination, const int *first, const int *last)
{
	int count = last - first;

	while (count > 0)
	{
		*destination = *first;

		++first;
		++destination;
		--count;
	}

	return destination;
}

inline void **bfmeCopySlots(void **destination, void **first, void **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (void **)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeIntVecG
{
public:
	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyInts(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	int *m_bfmeStart;
	int *m_bfmeFinish;
	int *m_bfmeEnd;
};

class BfmeSlotVecG
{
public:
	void bfmeErase(void **first, void **last)
	{
		m_bfmeFinish = bfmeCopySlots(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	void **m_bfmeStart;
	void **m_bfmeFinish;
	void **m_bfmeEnd;
};

class Gen_0018B850
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead;
	BfmeIntVecG m_bfmeVecA;
	BfmeSlotVecG m_bfmeVecB;
};

// ?bfmeClear@Gen_0018B850@@QAEXXZ
void Gen_0018B850::bfmeClear(void)
{
	m_bfmeVecA.bfmeClear();

	m_bfmeVecB.bfmeClear();
}

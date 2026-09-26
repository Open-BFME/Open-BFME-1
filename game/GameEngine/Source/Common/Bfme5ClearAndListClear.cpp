// A clear that tells each element twice before dropping it, then empties the
// list that follows the vector.
//
// The list clear reloads its node pointer for every one of the three stores it
// makes through it: storing through the node could reach the pointer itself,
// so MSVC cannot keep it in a register.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

class BfmeElemW
{
public:
	void bfmeEnable(int first, int second);			// retail thunk 0x000482AC -> 0x004482AC
	void bfmeSelect(int first, int second);			// retail thunk 0x0001949D -> 0x0041949D
};

inline BfmeElemW **bfmeCopyElems(BfmeElemW **destination, BfmeElemW **first, BfmeElemW **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (BfmeElemW **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecW
{
public:
	void bfmeErase(BfmeElemW **first, BfmeElemW **last)
	{
		m_bfmeFinish = bfmeCopyElems(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	BfmeElemW **m_bfmeStart;				// +0x00
	BfmeElemW **m_bfmeFinish;				// +0x04
	BfmeElemW **m_bfmeEnd;					// +0x08
};

class BfmeNodeW
{
public:
	int m_bfmeTag;						// +0x00
	BfmeNodeW *m_bfmeHead;					// +0x04
	BfmeNodeW *m_bfmeNext;					// +0x08
	BfmeNodeW *m_bfmePrev;					// +0x0C
};

class BfmeListW
{
public:
	void bfmeClear(void)
	{
		if (m_bfmeCount)
		{
			bfmeEraseFrom(m_bfmeNode->m_bfmeHead);

			m_bfmeNode->m_bfmeNext = m_bfmeNode;
			m_bfmeNode->m_bfmeHead = 0;
			m_bfmeNode->m_bfmePrev = m_bfmeNode;

			m_bfmeCount = 0;
		}
	}

	void bfmeEraseFrom(BfmeNodeW *node);			// retail thunk 0x00037AB5 -> 0x00437AB5

	BfmeNodeW *m_bfmeNode;					// +0x00
	int m_bfmeCount;					// +0x04
};

class Gen_004B1720
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[3];					// +0x00
	BfmeVecW m_bfmeVector;					// +0x0C
	int m_bfmeGap[11];					// +0x18
	BfmeListW m_bfmeList;					// +0x44
};

// ?bfmeClear@Gen_004B1720@@QAEXXZ
void Gen_004B1720::bfmeClear(void)
{
	BfmeElemW **it = m_bfmeVector.m_bfmeStart;

	while (it != m_bfmeVector.m_bfmeFinish)
	{
		BfmeElemW *element = *it;

		if (element)
		{
			element->bfmeEnable(1, 1);

			element->bfmeSelect(-1, -1);
		}

		++it;
	}

	m_bfmeVector.bfmeClear();

	m_bfmeList.bfmeClear();
}

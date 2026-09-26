// A clear followed by a walk of a linked list and a tail call on a singleton,
// and a body that empties two vectors before walking four groups.
//
// The successor is read before the visit and kept in a callee-saved register,
// so the loop reads its next pointer once; the test at the bottom is on that
// successor, which is what makes the walk a while loop over the node rather
// than over the member.
//
// The second is what identifies the copier: the slot the copy goes through is
// the memmove import, and only an import is hoisted into a register when it is
// called twice in one body. Declared as an ordinary function pointer the two
// calls each reload the slot and the body grows eight bytes.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);

inline void **bfmeCopySlots(void **destination, void **first, void **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (void **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecR
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

	void **m_bfmeStart;					// +0x00
	void **m_bfmeFinish;					// +0x04
	void **m_bfmeEnd;					// +0x08
};

class BfmeNodeR
{
public:
	int m_bfmeHead[34];					// +0x00
	BfmeNodeR *m_bfmeNext;					// +0x88
};

class BfmeSingletonR
{
public:
	virtual ~BfmeSingletonR(void);				// slot +0x00
	virtual void bfmeSlot04(void);
	virtual void bfmeSlot08(void);
	virtual void bfmeSlot0C(void);
	virtual void bfmeSlot10(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot1C(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot2C(void);
	virtual void bfmeSlot30(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot38(void);
	virtual void bfmeSlot3C(void);
	virtual void bfmeSlot40(void);
	virtual void bfmeSlot44(void);
	virtual void bfmeSlot48(void);
	virtual void bfmeSlot4C(void);
	virtual void bfmeSlot50(void);
	virtual void bfmeSlot54(void);
	virtual void bfmeSlot58(void);
	virtual void bfmeSlot5C(void);
	virtual void bfmeSlot60(void);
	virtual void bfmeSlot64(void);
	virtual void bfmeSlot68(void);
	virtual void bfmeSlot6C(void);
	virtual void bfmeSlot70(void);
	virtual void bfmeSlot74(void);
	virtual void bfmeSlot78(void);
	virtual void bfmeSlot7C(void);
	virtual void bfmeRefresh(void);				// slot +0x80
};

extern BfmeSingletonR *g_bfmeSingletonR;			// retail 0x012F1464

class Gen_0038D000
{
public:
	void bfmeClear(void);

private:
	void bfmeVisit(BfmeNodeR *node);			// retail thunk 0x0001D0DE -> 0x0038B0C0
	void bfmeFinish(void);					// retail thunk 0x00015028 -> 0x0038AE90

	int m_bfmeHead[42];					// +0x000
	BfmeNodeR *m_bfmeList;					// +0x0A8
	int m_bfmeGap[44];					// +0x0AC
	BfmeVecR m_bfmeVector;					// +0x15C
};

// ?bfmeClear@Gen_0038D000@@QAEXXZ
void Gen_0038D000::bfmeClear(void)
{
	m_bfmeVector.bfmeClear();

	BfmeNodeR *node = m_bfmeList;

	while (node)
	{
		BfmeNodeR *next = node->m_bfmeNext;

		bfmeVisit(node);

		node = next;
	}

	bfmeFinish();

	if (g_bfmeSingletonR)
		g_bfmeSingletonR->bfmeRefresh();
}

class BfmeItemS
{
public:
	void bfmeReset(void);					// retail thunk 0x00036A9D -> 0x00436A9D

	int m_bfmeHead[12];					// +0x00
	int m_bfmeMark;						// +0x30
	int m_bfmeTail[2];					// +0x34
};

class BfmeGroupS
{
public:
	int m_bfmeHead[2];					// +0x00
	BfmeItemS *m_bfmeStart;					// +0x08
	BfmeItemS *m_bfmeFinish;				// +0x0C
};

class Gen_003CFBA0
{
public:
	void bfmeClear(void);

private:
	int m_bfmeHead[4];					// +0x00
	BfmeGroupS *m_bfmeGroups[4];				// +0x10
	int m_bfmeGap;						// +0x20
	BfmeVecR m_bfmeSecond;					// +0x24
	BfmeVecR m_bfmeFirst;					// +0x30
};

// ?bfmeClear@Gen_003CFBA0@@QAEXXZ
void Gen_003CFBA0::bfmeClear(void)
{
	m_bfmeFirst.bfmeClear();

	m_bfmeSecond.bfmeClear();

	for (int index = 0; index < 4; ++index)
	{
		BfmeGroupS *group = m_bfmeGroups[index];

		if (group)
		{
			BfmeItemS *item = group->m_bfmeStart;

			while (item != group->m_bfmeFinish)
			{
				item->bfmeReset();

				item->m_bfmeMark = 0;

				++item;
			}
		}
	}
}

// cl: /GX

// Eight more bodies in two shapes.
//
// 0x00340860, 0x00452910, 0x00452970 and 0x00753460 are the unguarded linear
// insert of an insertion sort. The comparator arrives BY VALUE as the third
// argument -- lea ecx,[esp+0x20] takes the address of that argument slot, it
// is not a local -- and it is called with the pending value first and the
// element second. The loop is rotated: the element for the next comparison is
// loaded before the call, and the walk runs backwards four bytes at a time.
//
// 0x00881040, 0x008F7650, 0x009A2700 and 0x009F2880 fill a two-byte pair with
// true and hand its address to virtual slot ten of the argument, then pass the
// argument on to the member at +0x04. Both bytes come from one mov al,1, and
// the pair lives in the four bytes reserved by the push ecx in the prologue.

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};

struct BfmeAcceptFrame
{
	BfmeFlagPair m_bfmePair;
	unsigned int m_bfmeScratch;
};


struct BfmeInsertCompareA
{
	bool operator()(void *pending, void *element);		// ILT 0x00024B81
};

struct BfmeInsertCompareB
{
	bool operator()(void *pending, void *element);		// ILT 0x00024055
};

struct BfmeInsertCompareC
{
	bool operator()(void *pending, void *element);		// ILT 0x00039CB1
};

struct BfmeInsertCompareD
{
	bool operator()(void *pending, void *element);		// ILT 0x0002952D
};

// ?bfmeLinearInsert_00340860@@YAXPAPAXPAXUBfmeInsertCompareA@@@Z
void bfmeLinearInsert_00340860(void **last, void *pending, BfmeInsertCompareA compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00452910@@YAXPAPAXPAXUBfmeInsertCompareB@@@Z
void bfmeLinearInsert_00452910(void **last, void *pending, BfmeInsertCompareB compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00452970@@YAXPAPAXPAXUBfmeInsertCompareC@@@Z
void bfmeLinearInsert_00452970(void **last, void *pending, BfmeInsertCompareC compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

// ?bfmeLinearInsert_00753460@@YAXPAPAXPAXUBfmeInsertCompareD@@@Z
void bfmeLinearInsert_00753460(void **last, void *pending, BfmeInsertCompareD compare)
{
	void **previous = last - 1;

	while (compare(pending, *previous))
	{
		*last = *previous;
		last = previous;
		--previous;
	}

	*last = pending;
}

class BfmeFlagTarget
{
public:
	virtual void bfmeSlot0(void);
	virtual bool bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual bool bfmeSlot3(void);
	virtual bool bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeSlot6(void);
	virtual void bfmeSlot7(void);
	virtual void bfmeSlot8(void);
	virtual void bfmeSlot9(void);
	virtual void bfmeDescribe(BfmeFlagPair *flags);		// slot 10, vtable+0x28
	virtual void bfmeSlot11(void);
	virtual void bfmeSlot12(void);
	virtual void bfmeSlot13(void);
	virtual void bfmeSlot14(void);
	virtual void bfmeSlot15(void);
	virtual void bfmeSlot16(void);
	virtual void bfmeSlot17(void);
	virtual void bfmeSlot18(void);
	virtual void bfmeSlot19(void);
	virtual void bfmeSlot20(void);
	virtual void bfmeSlot21(void);
	virtual void bfmeSlot22(void *region);			// slot 22, vtable+0x58
	virtual void bfmeSlot23(void);
	virtual void bfmeSlot24(void);
	virtual void bfmeSlot25(void);
	virtual void bfmeSlot26(void);
	virtual void bfmeSlot27(float *value);			// slot 27, vtable+0x6C
	virtual void bfmeSlot28(void);
	virtual void bfmeSlot29(unsigned int *value);		// slot 29, vtable+0x74
	virtual void bfmeSlot30(int *value);			// slot 30, vtable+0x78
	virtual void bfmeSlot31(void);
	virtual void bfmeSlot32(void);
	virtual void bfmeSlot33(void);
	virtual void bfmeSlot34(void);
	virtual void bfmeSlot35(bool *value);			// slot 35, vtable+0x8C
};

class BfmeSinkA
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x008815A0

private:
	char m_bfmeRegion[0x18];				// +0x00
	float m_bfmeCellSize;				// +0x18
	float m_bfmeCellSizeInv;				// +0x1C
	int m_bfmeWidth;					// +0x20
	int m_bfmeHeight;					// +0x24
	struct BfmeCellFC *m_bfmeCells;				// +0x28
};

class BfmeSeedTarget;

class Gen_00881C60
{
public:
	void bfmeSeed(BfmeSeedTarget *target);			// matched 0x00881C60
};

class Gen_008812D0
{
public:
	void bfmeVisitCells(void);					// matched 0x00881410
};

struct BfmeCellFC
{
	BfmeCellFC();
	~BfmeCellFC();

	unsigned char m_bfmeKind;
	unsigned char m_bfmeGap[3];
	int m_bfmeValue;
};

void *__cdecl operator new[](unsigned int size);
void __cdecl operator delete[](void *block);

unsigned long CRC_Memory(const unsigned char *data, unsigned long length,
	unsigned long crc);

// ?bfmeAccept@BfmeSinkA@@QAEXPAVBfmeFlagTarget@@@Z
void BfmeSinkA::bfmeAccept(BfmeFlagTarget *target)
{
	if (!target->bfmeSlot4())
	{
		{
			BfmeAcceptFrame frame;
			frame.m_bfmePair.m_bfmeFirst = true;
			frame.m_bfmePair.m_bfmeSecond = true;
			target->bfmeDescribe(&frame.m_bfmePair);
			target->bfmeSlot22(this);
			target->bfmeSlot27((float *)&m_bfmeCellSize);
			target->bfmeSlot27((float *)&m_bfmeCellSizeInv);

			target->bfmeSlot30(&m_bfmeWidth);
			target->bfmeSlot30(&m_bfmeHeight);

			frame.m_bfmeScratch = 0;
			target->bfmeSlot29(&frame.m_bfmeScratch);
		}

		if (target->bfmeSlot1())
		{
			delete[] m_bfmeCells;
			m_bfmeCells = new BfmeCellFC[m_bfmeWidth * m_bfmeHeight];
		}

		BfmeCellFC *cell = m_bfmeCells;
		unsigned int scratch = 0;
		for (; scratch < (unsigned int)m_bfmeHeight; ++scratch)
		{
			for (unsigned int x = 0; x < (unsigned int)m_bfmeWidth;
				++x, ++cell)
			{
				reinterpret_cast<Gen_00881C60 *>(cell)->bfmeSeed(
					reinterpret_cast<BfmeSeedTarget *>(target));
			}
		}
	}
	else
	{
		unsigned int scratch = 0;
		unsigned int y = 0;
		if (y < (unsigned int)m_bfmeHeight)
		{
			do
			{
				unsigned int width = (unsigned int)m_bfmeWidth;
				unsigned char *cells =
					reinterpret_cast<unsigned char *>(m_bfmeCells);
				unsigned int offset = width;
				offset *= y;
				unsigned char *rowData = cells + offset * 8;
				unsigned int rowLength = width << 3;
				scratch += CRC_Memory(
					rowData,
					rowLength,
					0);
				++y;
			}
			while (y < (unsigned int)m_bfmeHeight);
		}
		target->bfmeSlot29(&scratch);
	}

	if (target->bfmeSlot1())
		reinterpret_cast<Gen_008812D0 *>(this)->bfmeVisitCells();
}

class Gen_00881040
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkA *m_bfmeSink;					// +0x04
};

class BfmeSinkB
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x008FB0B0

private:
	char m_bfmeHead[0x24];					// +0x00
	unsigned int m_bfmeWidth;					// +0x24
	unsigned int m_bfmeHeight;					// +0x28
	class ShroudManagerImpl008FBA40Element *m_bfmeElements;		// +0x2C
	class BfmeThingCDE *m_bfmeNodes;				// +0x30
	class PartitionData *m_bfmePendingPartitionData;			// +0x34
	int m_bfmeUnknown38;					// +0x38
	char m_bfmeRecords[0x28];				// +0x3C
	int m_bfmeUnknown64;					// +0x64
	bool m_bfmeEnabled;					// +0x68
	char m_bfmePadding69[3];					// +0x69
};

class BfmeThingCDE
{
public:
	void d_008f7ec0();
	char m_bfmeHead[0x10];					// +0x00
	BfmeThingCDE *m_bfmeNext;					// +0x10
};

class BfmeHostXO
{
public:
	void bfmeFlushXO();
};

class PartitionData
{
public:
	void unlink();
	void makeDirty();

	private:
	void updateCellsTouched();
	friend class BfmeSinkB;
};

class ShroudManagerImpl008FBA40
{
public:
	void drainPending();
	void notify();

	private:
	void processPending(bool drainAll);
	friend class BfmeSinkB;
};

class ShroudManagerImpl008FBA40Element
{
public:
	ShroudManagerImpl008FBA40Element();
	~ShroudManagerImpl008FBA40Element();

	char m_bfmeHead[4];					// +0x00
	char m_bfmePayload[0x60];				// +0x04
	int m_bfmeUnknown64;					// +0x64
};

class BfmeTargetHL;

class BfmeThingHL
{
public:
	void bfmeGoHL(BfmeTargetHL *target);
};

class BfmeTargetHL
{
};

// ?bfmeAccept@BfmeSinkB@@QAEXPAVBfmeFlagTarget@@@Z
void BfmeSinkB::bfmeAccept(BfmeFlagTarget *target)
{
	if (!target->bfmeSlot4())
	{
		reinterpret_cast<ShroudManagerImpl008FBA40 *>(this)->drainPending();

		BfmeThingCDE *node = m_bfmeNodes;
		while (node != 0)
		{
			node->d_008f7ec0();
			reinterpret_cast<BfmeHostXO *>(node)->bfmeFlushXO();
			reinterpret_cast<PartitionData *>(node)->makeDirty();
			node = node->m_bfmeNext;
		}

		reinterpret_cast<ShroudManagerImpl008FBA40 *>(this)->processPending(false);

		{
			unsigned char flags[4];
			flags[0] = true;
			flags[1] = true;
			target->bfmeDescribe(reinterpret_cast<BfmeFlagPair *>(flags));
		}
		target->bfmeSlot29(reinterpret_cast<unsigned int *>(this));
		target->bfmeSlot22(reinterpret_cast<unsigned char *>(this) + 4);
		target->bfmeSlot27(reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x1C));
		target->bfmeSlot27(reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(this) + 0x20));
		target->bfmeSlot30(reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x24));
		target->bfmeSlot30(reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(this) + 0x28));
		target->bfmeSlot29(reinterpret_cast<unsigned int *>(reinterpret_cast<unsigned char *>(this) + 0x38));

		if (!target->bfmeSlot3())
			target->bfmeSlot30(&m_bfmeUnknown64);

		target->bfmeSlot35(&m_bfmeEnabled);

		if (target->bfmeSlot1())
		{
			delete[] m_bfmeElements;
			m_bfmeElements = new ShroudManagerImpl008FBA40Element[
				m_bfmeWidth * m_bfmeHeight];
		}

		ShroudManagerImpl008FBA40Element *element = m_bfmeElements;
		unsigned int y = 0;
		for (; y < m_bfmeHeight; ++y)
		{
			unsigned int x = 0;
			for (; x < m_bfmeWidth; ++x, ++element)
				reinterpret_cast<BfmeThingHL *>(element)->bfmeGoHL(
					reinterpret_cast<BfmeTargetHL *>(target));
		}

		if (target->bfmeSlot1())
		{
			reinterpret_cast<ShroudManagerImpl008FBA40 *>(this)->notify();
		}
		else
		{
			++m_bfmeUnknown38;
			while (m_bfmePendingPartitionData != 0)
			{
				PartitionData *partitionData = m_bfmePendingPartitionData;
				partitionData->unlink();
				partitionData->updateCellsTouched();
			}
			reinterpret_cast<ShroudManagerImpl008FBA40 *>(this)->processPending(true);
		}
	}
	else
	{
		unsigned int scratch = 0;
		ShroudManagerImpl008FBA40Element *element = m_bfmeElements;
		unsigned int y = 0;
		for (; y < m_bfmeHeight; ++y)
		{
			unsigned int x = 0;
			for (; x < m_bfmeWidth; ++x, ++element)
			{
				scratch += CRC_Memory(
					reinterpret_cast<const unsigned char *>(element->m_bfmePayload),
					0x60,
					0) + element->m_bfmeUnknown64;
			}
		}
		target->bfmeSlot29(&scratch);
	}
}

class Gen_008F7650
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkB *m_bfmeSink;					// +0x04
};

class BfmeSinkC
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x009A2FC0
};

class Gen_009A2700
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkC *m_bfmeSink;					// +0x04
};

class BfmeSinkD
{
public:
	void bfmeAccept(BfmeFlagTarget *target);		// retail 0x009F49F0
};

class Gen_009F2880
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkD *m_bfmeSink;					// +0x04
};

// ?bfmeDescribe@Gen_00881040@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_00881040::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_008F7650@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_008F7650::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_009A2700@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_009A2700::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

// ?bfmeDescribe@Gen_009F2880@@QAEXPAVBfmeFlagTarget@@@Z
void Gen_009F2880::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

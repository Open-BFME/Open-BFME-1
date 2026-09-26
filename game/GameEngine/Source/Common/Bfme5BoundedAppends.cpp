// Nine bounded appends.
//
// Each compares the cursor at +0x10 against the limit at +0x18 minus ONE
// ELEMENT, copies into the cursor and advances it when there is room, and
// hands the item to a grow routine when there is not.
//
// The subtraction is what gives the element width away -- 0x194, 0x1F0, 0x210,
// 0x330 and 4 across the nine -- because it is pointer arithmetic on the limit,
// not a byte constant the source spells out. The cursor is re-read after the
// copy call before being advanced, since the call could have moved it, and the
// two bodies with four-byte elements are five bytes shorter because both that
// subtraction and the advance fit in a byte displacement.


struct BfmeSlotA
{
	char m_bfmeBytes[0x194];
};

void bfmeCopySlotA(BfmeSlotA *dest, void *source);	// retail 0x00002A8B

struct BfmeSlotB
{
	char m_bfmeBytes[0x330];
};

void bfmeCopySlotB(BfmeSlotB *dest, void *source);	// retail 0x0003BB51

struct BfmeSlotC
{
	char m_bfmeBytes[0x210];
};

void bfmeCopySlotC(BfmeSlotC *dest, void *source);	// retail 0x00045877

struct BfmeSlotD
{
	char m_bfmeBytes[0x1F0];
};

void bfmeCopySlotD(BfmeSlotD *dest, void *source);	// retail 0x00026BAC

struct BfmeSlotE
{
	char m_bfmeBytes[0x4];
};

void bfmeCopySlotE(BfmeSlotE *dest, void *source);	// retail 0x0001870F

class Gen_0064C330
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0004B646

	char m_bfmeHead[0x10];
	BfmeSlotA *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotA *m_bfmeEnd;					// +0x18
};

class Gen_0064C380
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x00005EB1

	char m_bfmeHead[0x10];
	BfmeSlotB *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotB *m_bfmeEnd;					// +0x18
};

class Gen_0064CAA0
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0004B646

	char m_bfmeHead[0x10];
	BfmeSlotA *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotA *m_bfmeEnd;					// +0x18
};

class Gen_0065DA70
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0004ACAF

	char m_bfmeHead[0x10];
	BfmeSlotC *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotC *m_bfmeEnd;					// +0x18
};

class Gen_0065DAC0
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0001B018

	char m_bfmeHead[0x10];
	BfmeSlotD *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotD *m_bfmeEnd;					// +0x18
};

class Gen_0065DCC0
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0004ACAF

	char m_bfmeHead[0x10];
	BfmeSlotC *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotC *m_bfmeEnd;					// +0x18
};

class Gen_0065DD10
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0001B018

	char m_bfmeHead[0x10];
	BfmeSlotD *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotD *m_bfmeEnd;					// +0x18
};

class Gen_006AB0B0
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0000B61D

	char m_bfmeHead[0x10];
	BfmeSlotE *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotE *m_bfmeEnd;					// +0x18
};

class Gen_006AC5D0
{
public:
	void bfmePush(void *item);

private:
	void bfmeGrow(void *item);				// retail 0x0000B61D

	char m_bfmeHead[0x10];
	BfmeSlotE *m_bfmeCursor;				// +0x10
	char m_bfmeGap[4];
	BfmeSlotE *m_bfmeEnd;					// +0x18
};

// ?bfmePush@Gen_0064C330@@QAEXPAX@Z
void Gen_0064C330::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotA(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0064C380@@QAEXPAX@Z
void Gen_0064C380::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotB(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0064CAA0@@QAEXPAX@Z
void Gen_0064CAA0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotA(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0065DA70@@QAEXPAX@Z
void Gen_0065DA70::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotC(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0065DAC0@@QAEXPAX@Z
void Gen_0065DAC0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotD(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0065DCC0@@QAEXPAX@Z
void Gen_0065DCC0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotC(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_0065DD10@@QAEXPAX@Z
void Gen_0065DD10::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotD(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_006AB0B0@@QAEXPAX@Z
void Gen_006AB0B0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotE(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

// ?bfmePush@Gen_006AC5D0@@QAEXPAX@Z
void Gen_006AC5D0::bfmePush(void *item)
{
	if (m_bfmeCursor != m_bfmeEnd - 1)
	{
		bfmeCopySlotE(m_bfmeCursor, item);

		m_bfmeCursor = m_bfmeCursor + 1;
	}
	else
	{
		bfmeGrow(item);
	}
}

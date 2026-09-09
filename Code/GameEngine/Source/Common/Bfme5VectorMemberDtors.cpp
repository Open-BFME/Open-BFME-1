// Four destructors over a vector member and its neighbours.

//
// All four run their members in reverse declaration order with the state word
// counting down, and the vector's destructor is inline everywhere -- the
// size-dispatch release rather than a call -- so its position in the sequence
// says where it sits in the layout.
//
// The bases differ. One has two, a primary at zero and a secondary at +0x08,
// with the secondary folding in and the primary called out of line. Two have a
// single base whose destructor folds in, which is the second vftable store at
// the exit. The last has no base at all and no vftable anywhere, and its body
// is a call on this.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

extern void * (__cdecl *bfmeMemCopy)(void *destination, const void *source,
	unsigned int bytes);

inline int *bfmeCtorCopyRange(int *destination, const int *first,
	const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;
	return (int *)((char *)bfmeMemCopy(destination, first, bytes) + bytes);
}

class BfmeVecMemberV
{
public:
	BfmeVecMemberV(void) : m_bfmeStart(0), m_bfmeFinish(0), m_bfmeEnd(0) {}

	~BfmeVecMemberV(void)
	{
		int *start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
	}

	void clear(void)
	{
		m_bfmeFinish = bfmeCtorCopyRange(m_bfmeStart, m_bfmeFinish,
			m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class BfmeBaseP
{
public:
	virtual ~BfmeBaseP(void);				// retail 0x009A1A40

private:
	int m_bfmeField;					// +0x04
};

class BfmeBaseQ
{
public:
	virtual ~BfmeBaseQ(void) {}
};

class Gen_00378650 : public BfmeBaseP, public BfmeBaseQ
{
public:
	virtual ~Gen_00378650(void);

private:
	BfmeVecMemberV m_bfmeVector;				// +0x0C
};

// ??1Gen_00378650@@UAE@XZ
Gen_00378650::~Gen_00378650(void)
{
}

class BfmeTailV
{
public:
	~BfmeTailV(void);					// retail 0x00887940

private:
	int m_bfmeField;
};

class Gen_0081DC90
{
public:
	~Gen_0081DC90(void);

	void bfmeFinish(void);					// retail 0x0081DBE0

private:
	int m_bfmePadA[2];					// +0x00
	BfmeTailV m_bfmeA;					// +0x08
	BfmeTailV m_bfmeB;					// +0x0C
	int m_bfmePadB;						// +0x10
	BfmeVecMemberV m_bfmeVector;				// +0x14
};

// ??1Gen_0081DC90@@QAE@XZ
Gen_0081DC90::~Gen_0081DC90(void)
{
	bfmeFinish();
}

class Gen00046B00
{
public:
	void handle(int a, int b);
};

class BfmeMidA
{
public:
	BfmeMidA(void) : m_bfmeStart(0), m_bfmeFinish(0), m_bfmeEnd(0) {}
	~BfmeMidA(void);					// retail 0x00035D8C

	void erase(void)
	{
		Gen00046B00 &sub = *(Gen00046B00 *)this;
		sub.handle((int)m_bfmeStart, (int)m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;					// +0x08
};

class BfmeBaseR_003643C0
{
public:
	virtual ~BfmeBaseR_003643C0(void) {}
};

class Gen_003643C0 : public BfmeBaseR_003643C0
{
public:
	virtual ~Gen_003643C0(void);

private:
	BfmeTailV m_bfmeA;					// +0x04
	int m_bfmePad[4];					// +0x08
	BfmeMidA m_bfmeB;					// +0x18
	BfmeVecMemberV m_bfmeVector;				// +0x24
};

// The constructor at 0x00366B90 initializes the same object whose destructor
// is above. Its first member uses the retail AsciiString literal constructor,
// and its two following members are vector headers. The owning class name is
// not proven, so the constructor keeps its retail address-derived name.
class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString(void) { releaseBuffer(); }
	void releaseBuffer(void);

	void *m_data;
};

class BfmeCtorString : public BFMERetailAsciiString
{
public:
	BfmeCtorString(const char *text) : BFMERetailAsciiString(text) {}
};

class Gen_00366B90 : public BfmeBaseR_003643C0
{
public:
	Gen_00366B90(void);

private:
	BfmeCtorString m_bfmeA;					// +0x04
	int m_bfmePad08;					// +0x08
	int m_bfmePad0C;					// +0x0C
	bool m_bfmeFlag;					// +0x10
	int m_bfmeColour;					// +0x14
	BfmeMidA m_bfmeB;					// +0x18
	BfmeVecMemberV m_bfmeVector;				// +0x24
};

// ??0Gen_00366B90@@QAE@XZ
Gen_00366B90::Gen_00366B90(void)
	: m_bfmeA((const char *)0x0107301C)
	, m_bfmeFlag(false)
	, m_bfmeB()
	, m_bfmeVector()
{
	m_bfmeColour = 0xFF000000;
	m_bfmePad08 = 0;
	m_bfmePad0C = 0;
	m_bfmeB.erase();
	m_bfmeVector.clear();
}

class BfmeMidB
{
public:
	~BfmeMidB(void);					// retail 0x009D82D0

private:
	int m_bfmeField;
};

class BfmeMidC
{
public:
	~BfmeMidC(void);					// retail 0x009D7A70

private:
	int m_bfmeField;
};

class BfmeBaseR_009D83D0
{
public:
	virtual ~BfmeBaseR_009D83D0(void) {}
};

class Gen_009D83D0 : public BfmeBaseR_009D83D0
{
public:
	virtual ~Gen_009D83D0(void);

private:
	int m_bfmePad[2];					// +0x04
	BfmeVecMemberV m_bfmeVector;				// +0x0C
	BfmeMidB m_bfmeB;					// +0x18
	int m_bfmeGap[4];					// +0x1C
	BfmeMidC m_bfmeC;					// +0x2C
};

// ??1Gen_003643C0@@UAE@XZ
Gen_003643C0::~Gen_003643C0(void)
{
}

// ??1Gen_009D83D0@@UAE@XZ
Gen_009D83D0::~Gen_009D83D0(void)
{
}

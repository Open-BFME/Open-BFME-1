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

class BfmeVecMemberV
{
public:
	~BfmeVecMemberV(void)
	{
		int *start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(int) * (m_bfmeEnd - start));
	}

private:
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

class BfmeMidA
{
public:
	~BfmeMidA(void);					// retail 0x00035D8C

private:
	int m_bfmeField;
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
	int m_bfmeGap[2];					// +0x1C
	BfmeVecMemberV m_bfmeVector;				// +0x24
};

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

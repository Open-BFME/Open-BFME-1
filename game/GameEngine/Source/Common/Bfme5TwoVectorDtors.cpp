// Two destructors, both empty in source.
//
// The first lets two vector members go in reverse order and chains to a base
// that is out of line and not polymorphic -- no vftable store anywhere.
//
// The second has a base whose destructor folds in, and that base has a body of
// its own: a delete and a null store that land AFTER the state word has gone
// back to -1 and after the base vftable store. Everything past those two marks
// belongs to the base, not to the derived class.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMemberR
{
public:
	~BfmeVecMemberR(void)
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

class BfmeBaseZ
{
public:
	~BfmeBaseZ(void);					// retail 0x0002B4AE

private:
	int m_bfmeFields[3];					// +0x00
};

class Gen_000E54B0 : public BfmeBaseZ
{
public:
	~Gen_000E54B0(void);

private:
	BfmeVecMemberR m_bfmeFirst;				// +0x0C
	BfmeVecMemberR m_bfmeSecond;				// +0x18
};

// ??1Gen_000E54B0@@QAE@XZ
Gen_000E54B0::~Gen_000E54B0(void)
{
}

class BfmeOwnedR
{
public:
	virtual ~BfmeOwnedR(void);				// slot +0x00
};

class BfmeTailQ
{
public:
	~BfmeTailQ(void);					// retail 0x00887940

private:
	int m_bfmeField;
};

class BfmeTailP
{
public:
	~BfmeTailP(void);					// retail 0x008881D0

private:
	int m_bfmeField;
};

class BfmeBaseY
{
public:
	virtual ~BfmeBaseY(void)
	{
		delete m_bfmePtr;

		m_bfmePtr = 0;
	}

	BfmeOwnedR *m_bfmePtr;					// +0x04

private:
	int m_bfmeField;					// +0x08
};

class Gen_0039C060 : public BfmeBaseY
{
public:
	virtual ~Gen_0039C060(void);

private:
	BfmeTailQ m_bfmeA;					// +0x0C
	BfmeTailP m_bfmeB;					// +0x10
	BfmeVecMemberR m_bfmeVector;				// +0x14
};

// ??1Gen_0039C060@@UAE@XZ
Gen_0039C060::~Gen_0039C060(void)
{
}

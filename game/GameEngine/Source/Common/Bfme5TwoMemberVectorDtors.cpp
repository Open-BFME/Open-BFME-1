// Two destructors over a vector and a second member.
//
// The body is one call taking the address of the second member; then that
// member's own destructor runs, and last the vector at offset zero releases
// its block. Reverse declaration order, so the member at +0x0C goes first.
//
// The state word counts the two members -- one while the body runs, zero once
// the second is gone, then -1 -- and the middle store is byte-wide because
// only the low byte changes. Neither class is polymorphic: there is no vftable
// store anywhere.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMemberZ
{
public:
	~BfmeVecMemberZ(void)
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

class BfmeSecondZ
{
public:
	~BfmeSecondZ(void);					// retail 0x00017E63

private:
	int m_bfmeField;
};

void __cdecl bfmeUnregister(BfmeSecondZ *second);		// retail 0x00035328

class Gen_0035B8A0
{
public:
	~Gen_0035B8A0(void);

private:
	BfmeVecMemberZ m_bfmeFirst;				// +0x00
	BfmeSecondZ m_bfmeSecond;				// +0x0C
};

// ??1Gen_0035B8A0@@QAE@XZ
Gen_0035B8A0::~Gen_0035B8A0(void)
{
	bfmeUnregister(&m_bfmeSecond);
}

class BfmeSecondY
{
public:
	~BfmeSecondY(void);					// retail 0x0002A699

private:
	int m_bfmeField;
};

void __cdecl bfmeUnregisterY(BfmeSecondY *second);		// retail 0x0002F0EF

class Gen_0035B960
{
public:
	~Gen_0035B960(void);

private:
	BfmeVecMemberZ m_bfmeFirst;				// +0x00
	BfmeSecondY m_bfmeSecond;				// +0x0C
};

// ??1Gen_0035B960@@QAE@XZ
Gen_0035B960::~Gen_0035B960(void)
{
	bfmeUnregisterY(&m_bfmeSecond);
}

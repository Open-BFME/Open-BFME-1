// Two destructors with real bodies over a vector.
//
// The first finishes through a call on this, deletes what a pointer member
// owns and nulls it, and only then lets the vector member go and chains to the
// base. Everything before the state word drops is body: the state stays at its
// starting value across the delete and the null store.
//
// The second walks the vector releasing a reference on every non-null element,
// then the vector itself goes. Its bound is read once into a local before the
// walk, and the element call takes the pointer stored in the slot rather than
// the slot itself.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMemberT
{
public:
	~BfmeVecMemberT(void)
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

class BfmeOwnedT
{
public:
	virtual ~BfmeOwnedT(void);				// slot +0x00
};

class BfmeBaseX
{
public:
	virtual ~BfmeBaseX(void);				// retail 0x009A1A40

private:
	int m_bfmeField;					// +0x04
};

class Gen_00490100 : public BfmeBaseX
{
public:
	virtual ~Gen_00490100(void);

	void bfmeFinish(void);					// retail 0x00013421

private:
	BfmeOwnedT *m_bfmePtr;					// +0x08
	BfmeVecMemberT m_bfmeVector;				// +0x0C
};

// ??1Gen_00490100@@UAE@XZ
Gen_00490100::~Gen_00490100(void)
{
	bfmeFinish();

	delete m_bfmePtr;

	m_bfmePtr = 0;
}

class BfmeTextureS
{
public:
	void bfmeReleaseRef(void);				// retail 0x009EB7A0
};

class BfmeVecBaseS
{
public:
	~BfmeVecBaseS(void)
	{
		BfmeTextureS **start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(BfmeTextureS *) * (m_bfmeEnd - start));
	}

	BfmeTextureS **m_bfmeStart;				// +0x00
	BfmeTextureS **m_bfmeFinish;				// +0x04
	BfmeTextureS **m_bfmeEnd;				// +0x08
};

class Gen_00757830 : public BfmeVecBaseS
{
public:
	~Gen_00757830(void);
};

// ??1Gen_00757830@@QAE@XZ
Gen_00757830::~Gen_00757830(void)
{
	BfmeTextureS **last = m_bfmeFinish;

	for (BfmeTextureS **it = m_bfmeStart; it != last; ++it)
	{
		if (*it)
			(*it)->bfmeReleaseRef();
	}
}

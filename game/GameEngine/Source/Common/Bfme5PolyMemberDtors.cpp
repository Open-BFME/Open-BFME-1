// Three destructors over a vector and its neighbours.
//
// Members go in reverse declaration order with the state word counting down,
// and the vector's destructor is inline -- the size-dispatch release rather
// than a call.
//
// The third of them settles a question the earlier ones raised: a lone vftable
// store at the EXIT with none at the entry is not a folded base. It is a
// polymorphic FIRST MEMBER whose own inline destructor runs last. A base would
// have forced the most-derived vptr in at the entry as well, whether or not
// the derived class overrides anything.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMemberU
{
public:
	~BfmeVecMemberU(void)
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

class BfmeTailU
{
public:
	~BfmeTailU(void);					// retail 0x00887940

private:
	int m_bfmeField;
};

class Gen_0037EFB0
{
public:
	~Gen_0037EFB0(void);

private:
	BfmeVecMemberU m_bfmeVector;				// +0x00
	BfmeTailU m_bfmeTail;					// +0x0C
};

class BfmeTailT
{
public:
	~BfmeTailT(void);					// retail 0x00005709

private:
	int m_bfmeField;
};

class BfmeBaseT
{
public:
	virtual ~BfmeBaseT(void);				// retail 0x009A1A40

private:
	int m_bfmeFields[2];					// +0x04
};

class Gen_004B1670 : public BfmeBaseT
{
public:
	virtual ~Gen_004B1670(void);

private:
	BfmeVecMemberU m_bfmeVector;				// +0x0C
	int m_bfmePad[11];					// +0x18
	BfmeTailT m_bfmeTail;					// +0x44
};

// ??1Gen_0037EFB0@@QAE@XZ
Gen_0037EFB0::~Gen_0037EFB0(void)
{
}

// ??1Gen_004B1670@@UAE@XZ
Gen_004B1670::~Gen_004B1670(void)
{
}

class BfmeBaseS
{
public:
	virtual void bfmeSlot0(void);

	~BfmeBaseS(void) {}

private:
	int m_bfmeField;					// +0x04
};

class Gen_0015C4B0
{
public:
	~Gen_0015C4B0(void);

private:
	BfmeBaseS m_bfmeFirst;					// +0x00
	BfmeVecMemberU m_bfmeVector;				// +0x08
};

// ??1Gen_0015C4B0@@QAE@XZ
Gen_0015C4B0::~Gen_0015C4B0(void)
{
}


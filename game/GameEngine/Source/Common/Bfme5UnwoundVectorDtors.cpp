// Three unwound vector destructors.
//
// Each is empty in source. The whole body is the vector member going away --
// release the block by size, exactly as the matching allocate chooses its
// allocator -- followed by the base destructor on this.
//
// The unwind frame with the state word moving -1 to 0 and back exists because
// the member has a destructor; the state returns to -1 before the base runs,
// since by then nothing is left to clean. The member offset is the base width:
// four, eight and twelve across the three.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMember;

class BfmeVecEnd
{
public:
	BfmeVecEnd(BfmeVecMember *owner)
	{
		BfmeVecMember *volatile self = owner;
		m_bfmeEnd = 0;
	}

	int *m_bfmeEnd;
};

class BfmeVecMember
{
public:
	BfmeVecMember(void) : m_bfmeStart(0), m_bfmeFinish(0), m_bfmeEnd(this) {}
	void bfmeStart(void *first, void *second, void **slot);

	~BfmeVecMember(void)
	{
		int *start = m_bfmeStart;

		if (start)
			bfmeRelease(start, sizeof(int) * (m_bfmeEnd.m_bfmeEnd - start));
	}

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	BfmeVecEnd m_bfmeEnd;					// +0x08
};

class BfmeDtorBase_00077560
{
public:
	~BfmeDtorBase_00077560(void);			// retail 0x009A1A40

private:
	int m_bfmeFields[2];					// +0x00
};

class Gen_00077560 : public BfmeDtorBase_00077560
{
public:
	~Gen_00077560(void);

private:
	BfmeVecMember m_bfmeVector;				// +0x08
};

class BfmeDtorPair_0049A4B0
{
public:
	BfmeDtorPair_0049A4B0(void) : m_bfmeA(0), m_bfmeB(0) {}

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class BfmeDtorSlot_0049A4B0
{
public:
	BfmeDtorSlot_0049A4B0(void) : m_bfmeC(0) {}
	~BfmeDtorSlot_0049A4B0(void);

private:
	int m_bfmeC;
};

class BfmeDtorBase_0049A4B0 : public BfmeDtorPair_0049A4B0
{
public:
	BfmeDtorBase_0049A4B0(void) : BfmeDtorPair_0049A4B0(), m_bfmeSlot() {}
	~BfmeDtorBase_0049A4B0(void);			// retail 0x00026AB2

private:
	BfmeDtorSlot_0049A4B0 m_bfmeSlot;				// +0x08
};

class Gen_0049A4B0 : public BfmeDtorBase_0049A4B0
{
public:
	Gen_0049A4B0(void *first);
	~Gen_0049A4B0(void);

private:
	BfmeVecMember m_bfmeVector;				// +0x0C
};

class BfmeDtorBase_00619F60
{
public:
	~BfmeDtorBase_00619F60(void);			// retail 0x00887940

private:
	int m_bfmeFields[1];					// +0x00
};

class Gen_00619F60 : public BfmeDtorBase_00619F60
{
public:
	~Gen_00619F60(void);

private:
	BfmeVecMember m_bfmeVector;				// +0x04
};

// ??1Gen_00077560@@QAE@XZ
Gen_00077560::~Gen_00077560(void)
{
}

// ??0Gen_0049A4B0@@QAE@PAX@Z
Gen_0049A4B0::Gen_0049A4B0(void *first)
	: BfmeDtorBase_0049A4B0(), m_bfmeVector()
{
	m_bfmeVector.bfmeStart(first, 0, &first);
}

// ??1Gen_0049A4B0@@QAE@XZ
Gen_0049A4B0::~Gen_0049A4B0(void)
{
}

// ??1Gen_00619F60@@QAE@XZ
Gen_00619F60::~Gen_00619F60(void)
{
}

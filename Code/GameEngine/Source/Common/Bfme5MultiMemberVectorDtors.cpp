// Two destructors over several members, one of them a vector.
//
// Members go in reverse declaration order and the state word counts down as
// each is destroyed, byte-wide once only the low byte changes. The vector's
// destructor is inline, so it shows up as the size-dispatch release rather
// than a call, wherever it happens to fall in that sequence.
//
// One of the two has a base whose destructor folds in -- the second vftable
// store at the exit -- and a one-statement body ahead of the members; the
// other has no base at all and an empty body, so its vptr is stored once on
// entry and never again.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void bfmeRelease(void *block, unsigned int bytes)
{
	if (bytes > 0x80)
		bfmeFreeScalar(block);
	else
		bfmeDeallocate(block, bytes);
}

class BfmeVecMemberW
{
public:
	~BfmeVecMemberW(void)
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

class BfmeTailW
{
public:
	~BfmeTailW(void);					// retail 0x00887940

private:
	int m_bfmeField;
};

class BfmeBaseW
{
public:
	virtual ~BfmeBaseW(void) {}
};

class Gen_001BA9E0 : public BfmeBaseW
{
public:
	virtual ~Gen_001BA9E0(void);

	void bfmeFinish(void);					// retail 0x00023ECA

private:
	BfmeVecMemberW m_bfmeVector;				// +0x04
	int m_bfmePad[2];					// +0x10
	BfmeTailW m_bfmeA;					// +0x18
	BfmeTailW m_bfmeB;					// +0x1C
};

// ??1Gen_001BA9E0@@UAE@XZ
Gen_001BA9E0::~Gen_001BA9E0(void)
{
	bfmeFinish();
}

class BfmeOtherX
{
public:
	~BfmeOtherX(void);					// retail 0x00024D8E

private:
	int m_bfmeField;
};

class TerrainType
{
public:
	virtual ~TerrainType(void);

private:
	BfmeTailW m_bfmeA;					// +0x04
	BfmeTailW m_bfmeB;					// +0x08
	int m_bfmeGap;						// +0x0C
	BfmeVecMemberW m_bfmeVector;				// +0x10
	int m_bfmePad[2];					// +0x1C
	BfmeOtherX m_bfmeD;					// +0x24
};

// ??1TerrainType@@UAE@XZ
TerrainType::~TerrainType(void)
{
}

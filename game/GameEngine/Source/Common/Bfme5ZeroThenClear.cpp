// Constructors that zero their fields and then empty the vectors they just
// zeroed.
//
// Retail reloads the members after the zeroes instead of folding the copy
// away, and the only source shape that does that is the zeroes coming from
// member constructors and an initializer list. Assigned in the body -- even
// through a cast pointer, a helper or a private method -- MSVC propagates the
// zeroes into the copy and the whole thing collapses.

extern "C" __declspec(dllimport) void * __cdecl memmove(void *destination, const void *source, unsigned int bytes);




inline void **bfmeCopySlots(void **destination, void **first, void **last)
{
	if (first == last)
		return destination;

	int bytes = (char *)last - (char *)first;

	return (void **)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecU
{
public:
	BfmeVecU(void)
	{
		m_bfmeStart = 0;
		m_bfmeFinish = 0;
		m_bfmeEnd = 0;
	}

	void bfmeErase(void **first, void **last)
	{
		m_bfmeFinish = bfmeCopySlots(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	void **m_bfmeStart;
	void **m_bfmeFinish;
	void **m_bfmeEnd;
};

class Gen_003C55F0
{
public:
	Gen_003C55F0(void);

private:
	BfmeVecU m_bfmeFirst;					// +0x00
	int m_bfmeGapA;						// +0x0C
	int m_bfmeGapB;						// +0x10
	BfmeVecU m_bfmeSecond;					// +0x14
	BfmeVecU m_bfmeThird;					// +0x20
};

// ??0Gen_003C55F0@@QAE@XZ
Gen_003C55F0::Gen_003C55F0(void) : m_bfmeGapA(0), m_bfmeGapB(0)
{

	m_bfmeFirst.bfmeClear();

	m_bfmeSecond.bfmeClear();

	m_bfmeThird.bfmeClear();
}

inline int *bfmeCopyRange(int *destination, const int *first, const int *last)
{
	if (first == last)
		return destination;

	int bytes = (const char *)last - (const char *)first;

	return (int *)((char *)memmove(destination, first, bytes) + bytes);
}

class BfmeVecV
{
public:
	BfmeVecV(void)
	{
		m_bfmeStart = 0;
		m_bfmeFinish = 0;
		m_bfmeEnd = 0;
	}

	void bfmeErase(int *first, int *last)
	{
		m_bfmeFinish = bfmeCopyRange(first, last, m_bfmeFinish);
	}

	void bfmeClear(void)
	{
		bfmeErase(m_bfmeStart, m_bfmeFinish);
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

class Gen_0061A3D0;

template <class T> class StringBase
{
private:
	StringBase(const StringBase<T> &source);		// retail 0x00887B60

	void *m_bfmeData;					// +0x00

	friend class Gen_0061A3D0;
};

class Gen_0061A3D0 : public StringBase<char>
{
public:
	Gen_0061A3D0(const StringBase<char> &source);

private:
	BfmeVecV m_bfmeVector;					// +0x04
	int m_bfmeGap[2];					// +0x10
	bool m_bfmeFlag;					// +0x18
	int m_bfmeCountA;					// +0x1C
	int m_bfmeCountB;					// +0x20
	int m_bfmeCountC;					// +0x24
	int m_bfmeCountD;					// +0x28
};

// ??0Gen_0061A3D0@@QAE@ABV?$StringBase@D@@@Z
Gen_0061A3D0::Gen_0061A3D0(const StringBase<char> &source)
	: StringBase<char>(source), m_bfmeFlag(true), m_bfmeCountA(0), m_bfmeCountB(0),
	  m_bfmeCountC(0), m_bfmeCountD(0)
{
	m_bfmeVector.bfmeClear();
}

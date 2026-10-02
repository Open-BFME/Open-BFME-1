// stlport
// A vector destructor whose base folds in.
//
// Empty in source. The vector member releases its block by size, and the base
// destructor is inline, so it shows up as the second vftable store rather than
// a call -- the first store is the most-derived one on entry.
//
// The unwind frame and the state word going to zero are there for the member,
// which has a destructor; the state never returns to -1 because the base needs
// nothing unwound.

#include <memory>

inline void bfmeRelease(void *block, unsigned int bytes)
{
	// STLport's inline dispatch calls the matched operator delete (0x00881EB0)
	// or __node_alloc<true, 0>::_M_deallocate (0x0082E5F0).
	_STL::__node_alloc<true, 0>::deallocate(block, bytes);
}

class BfmeVecMemberY
{
public:
	~BfmeVecMemberY(void)
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

class BfmeDtorBaseY
{
public:
	virtual ~BfmeDtorBaseY(void) {}

private:
	int m_bfmeField;					// +0x04
};

class Gen_000D1730 : public BfmeDtorBaseY
{
public:
	virtual ~Gen_000D1730(void);

private:
	BfmeVecMemberY m_bfmeVector;				// +0x08
};

// ??1Gen_000D1730@@UAE@XZ
Gen_000D1730::~Gen_000D1730(void)
{
}


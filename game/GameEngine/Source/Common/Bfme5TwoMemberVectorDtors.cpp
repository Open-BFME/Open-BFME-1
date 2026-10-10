// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

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

class BfmeVecMemberZ
{
public:
	~BfmeVecMemberZ(void)
	{
		int *start = m_bfmeStart;

		if (start)
			_STL::__node_alloc<true, 0>::deallocate(start, sizeof(int) * (m_bfmeEnd - start));
	}

private:
	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
	int *m_bfmeEnd;						// +0x08
};

// Retail's second members are twelve-byte STLport vectors; the ILTs reach
// the matched destructor specializations at 0x0035A980 and 0x0035AA50.
struct Gen0035A980;
struct Gen0035AA50;
template <> _STL::vector<Gen0035A980>::~vector();
template <> _STL::vector<Gen0035AA50>::~vector();
class BfmeSecondZ;

void __cdecl bfmeUnregister(BfmeSecondZ *second);		// retail 0x00035328

class Gen_0035B8A0
{
public:
	~Gen_0035B8A0(void);

private:
	BfmeVecMemberZ m_bfmeFirst;				// +0x00
	_STL::vector<Gen0035A980> m_bfmeSecond;				// +0x0C
};

// ??1Gen_0035B8A0@@QAE@XZ
Gen_0035B8A0::~Gen_0035B8A0(void)
{
	bfmeUnregister((BfmeSecondZ *)&m_bfmeSecond);
}

class BfmeSecondY;

void __cdecl bfmeUnregisterY(BfmeSecondY *second);		// retail 0x0002F0EF

class Gen_0035B960
{
public:
	~Gen_0035B960(void);

private:
	BfmeVecMemberZ m_bfmeFirst;				// +0x00
	_STL::vector<Gen0035AA50> m_bfmeSecond;				// +0x0C
};

// ??1Gen_0035B960@@QAE@XZ
Gen_0035B960::~Gen_0035B960(void)
{
	bfmeUnregisterY((BfmeSecondY *)&m_bfmeSecond);
}

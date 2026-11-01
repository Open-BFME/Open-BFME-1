// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Q4Sort0034BFC0 compares particle-system template names without case.
// targets/game/reverse/symbols.csv resolves its ILT at 0x00024B81 to this body at
// 0x0033D5E0, and the adjacent median, partition, and sort bodies use the
// same comparator type.
//
// Retail evaluates the right-hand getName call first.  Keeping both calls in
// one expression reproduces the returned AsciiString temporaries and their
// cleanup at 0x00887940 without adding copy constructors.
//
// The operator is defined in the class, as the sort's own TU had it: the
// optimiser declines to expand it (two AsciiString temporaries under EH), and
// __partial_sort<int *, int, Q4Sort0034BFC0> (retail 0x0034B8D0, 121 bytes)
// then keeps the comparator value cached in EBP and reloads `last` from its
// argument slot, as retail does.  An out-of-line declaration swaps the two.

#include <algorithm>

template <typename T>
class StringBase
{
public:
	__declspec(nothrow) int compareNoCase(const StringBase<T> &other) const;

private:
	void *m_data;
private:
	void releaseBuffer(void);
	friend class AsciiString;
};

class AsciiString : public StringBase<char>
{
public:
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	__declspec(nothrow) int compareNoCase(const AsciiString &other) const
	{
		return ((const StringBase<char> *)this)->compareNoCase(
			*(const StringBase<char> *)&other);
	}
};

namespace FXParticleSystem
{

class ParticleSystemTemplate
{
public:
	AsciiString getName() const;
};

}

struct Q4Sort0034BFC0
{
	bool operator()(int a, int b) const
	{
		return ((const FXParticleSystem::ParticleSystemTemplate *)a)->getName().compareNoCase(
			((const FXParticleSystem::ParticleSystemTemplate *)b)->getName()) < 0;
	}
};

// Retail 0x0034B8D0: the heap-select fallback of the Q4Sort0034BFC0 sort;
// its __make_heap, __adjust_heap and sort_heap calls go through ILTs
// 0x0000F74F, 0x0000A20E and 0x0002720F, whose bodies call this comparator.
template void _STL::__partial_sort<int *, int, Q4Sort0034BFC0>(
	int *, int *, int *, int *, Q4Sort0034BFC0);

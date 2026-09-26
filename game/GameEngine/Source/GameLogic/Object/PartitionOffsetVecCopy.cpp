// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: _STL::__copy over vector<ICoord2D> elements, retail 0x003B5F40, 68 bytes.
//
// PartitionManager.cpp cannot host this row. It claims three bodies that all call
// "vector<ICoord2D>::operator=", and retail encodes TWO DIFFERENT functions for
// them: this one reaches the ILT 0x00026C6A -> 0x001E7330, whose element span is
// divided by eight (sar edi,3), while the __copy_backward at 0x000BCCE0 and the
// fill reach 0x00018A70 -> 0x000BC4B0, which divides by four (sar edi,2). One
// symbol cannot pin two bodies, so the eight-byte-element instantiation is spelled
// here over a TU-local PmICoord2D and pinned on a name of its own.
//
// ICoord2D is two ints, so eight bytes is the element width this __copy wants; the
// four-byte body stays under the spelling PartitionManager.cpp keeps.
//
// The loop returns the ADVANCED result and the n<=0 arm returns the argument, which
// is why retail reloads it from the stack instead of reusing a register.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct PmICoord2D
{
	int x;
	int y;
};

namespace _STL
{

template <class Type>
class allocator {};

struct random_access_iterator_tag {};

template <class Type, class Allocator>
class vector
{
public:
	vector &operator=(const vector &that);

private:
	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template <class RandomAccessIterator, class OutputIterator, class Distance>
OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last,
	OutputIterator result, const random_access_iterator_tag &, Distance *)
{
	for (Distance n = last - first; n > 0; --n, ++first, ++result)
		*result = *first;
	return result;
}

typedef vector<PmICoord2D, allocator<PmICoord2D> > PmOffsetVec;

template PmOffsetVec *__copy(PmOffsetVec *, PmOffsetVec *, PmOffsetVec *,
	const random_access_iterator_tag &, int *);

}

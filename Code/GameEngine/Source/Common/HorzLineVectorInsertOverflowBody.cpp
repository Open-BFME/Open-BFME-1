// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<HorzLine> reallocating insert, retail 0x00069070,
// 314 bytes. The name sat on the 5-byte incremental-link thunk at 0x00017FB2
// and the body it jumps to carried only a machine byte-dump row.
//
// The address places it: DiscreteCircle::removeDuplicates ends at 0x00068EB5 and
// DiscreteCircle::generateEdgePairs starts at 0x00069250, both matched out of
// discrete_circle.cpp, and vector<HorzLine>::push_back is one of the names
// folded at 0x00069200.
//
// The element is 12 bytes -- three Ints -- so both size computations go through
// the signed divide-by-twelve magic multiply and the new end-of-storage is
// formed with lea/lea rather than a shift. The bulk phases stay out of line,
// __uninitialized_copy through the ILT at 0x0000C61C and __uninitialized_fill_n
// through the ILT at 0x0002E91A, and this instantiation takes its input
// iterators non-const. Retail hands the helpers' empty dispatch tag the address
// of its own trailing bool argument rather than spending a frame slot on it.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DiscreteCircle.h
struct HorzLine
{
	int m_yPos;
	int m_xStart;
	int m_xEnd;
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *block);
void __cdecl vectorSmallDeallocate(void *block, unsigned int bytes);

struct __false_type
{
};

template <class Type>
class allocator
{
};

// Both reach retail's shared 12-byte-element helpers through their link thunks;
// naming them apart from the _STL spellings keeps those names on their real
// bodies at 0x00068C50 and 0x00068CA0.
HorzLine *__cdecl BfmeHorzLineUninitializedCopy(
	HorzLine *first, HorzLine *last, HorzLine *result, const __false_type &);

HorzLine *__cdecl BfmeHorzLineUninitializedFillN(
	HorzLine *result, unsigned int count,
	const HorzLine &value, const __false_type &);

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd)
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if (length)
	{
		unsigned int bytes = length * sizeof(Type);
		if (bytes > 128)
			newStart = (Type *)vectorLargeAllocate(bytes);
		else
			newStart = (Type *)vectorSmallAllocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = BfmeHorzLineUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeHorzLineUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeHorzLineUninitializedCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

template class vector<HorzLine, allocator<HorzLine> >;
}

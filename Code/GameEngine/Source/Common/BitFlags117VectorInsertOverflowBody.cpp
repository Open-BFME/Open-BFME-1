// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<BitFlags<117> > reallocating insert, retail
// 0x0074DB50, 271 bytes. The body carried only a machine byte-dump row and the
// name was one of four sharing the 5-byte incremental-link thunk at 0x0000AE93,
// which jumps to 0x0075A330 -- the vector<W3DRopeDraw::SegInfo> body.
//
// Both bulk phases name it outright: __uninitialized_copy at 0x0074AA10 through
// the ILT at 0x00018FED and __uninitialized_fill_n at 0x00749450 through the ILT
// at 0x0002E32F both carry the BitFlags<117> spelling in the ledger.
//
// 117 bits is four dwords, so the element is 16 bytes and trivially copied: the
// size arithmetic shifts the byte distance by four and the single-element insert
// opens into four dword moves. Retail hands the helpers' empty dispatch tag the
// address of its own trailing bool argument rather than spending a frame slot
// on it.

template <int Count>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
private:
	unsigned int m_bits[( Count + 31 ) / 32];
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

// Both reach the helpers the ledger names for this element through their link
// thunks; naming them apart from the _STL spellings keeps those names on their
// real bodies at 0x0074AA10 and 0x00749450. This instantiation takes its input
// iterators non-const.
BitFlags<117> *__cdecl BfmeBitFlags117UninitializedCopy(
	BitFlags<117> *first, BitFlags<117> *last,
	BitFlags<117> *result, const __false_type &);

BitFlags<117> *__cdecl BfmeBitFlags117UninitializedFillN(
	BitFlags<117> *result, unsigned int count,
	const BitFlags<117> &value, const __false_type &);

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

	Type *newFinish = BfmeBitFlags117UninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeBitFlags117UninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeBitFlags117UninitializedCopy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	if (_M_start)
	{
		unsigned int bytes = (unsigned int)(_M_end_of_storage - _M_start) * sizeof(Type);
		if (bytes > 128)
			vectorLargeDeallocate(_M_start);
		else
			vectorSmallDeallocate(_M_start, bytes);
	}

	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}

template class vector<BitFlags<117>, allocator<BitFlags<117> > >;
}

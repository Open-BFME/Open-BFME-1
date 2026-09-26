// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<tConnInfoStruct> reallocating insert, retail
// 0x00638FF0, 328 bytes. The name sat on the 5-byte incremental-link thunk at
// 0x0004ABF6 and the body it jumps to carried only a machine byte-dump row.
//
// The callees confirm the element: both bulk phases reach helpers the ledger
// already names for tConnInfoStruct out of StagingRoomGameInfo.cpp --
// __uninitialized_copy at 0x00637E40 through the ILT at 0x00007018 and
// __uninitialized_fill_n at 0x00637EA0 through the ILT at 0x000099FD.
//
// The element is 20 bytes: a state word, two addresses and two ports, each port
// costing a short plus two bytes of padding. Both size computations go through
// the signed divide-by-twenty magic multiply and the byte count is a scale-4
// lea followed by a shift of two. Retail hands the helpers' empty dispatch tag
// the address of its own trailing bool argument rather than spending a frame
// slot on it.

struct tConnInfoStruct
{
	unsigned int State;
	unsigned long LocalIP;
	unsigned short LocalPort;
	unsigned long RemoteIP;
	unsigned short RemotePort;
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

// Both reach the helpers the ledger already names for this element through
// their link thunks; naming them apart from the _STL spellings keeps those
// names on their real bodies at 0x00637E40 and 0x00637EA0.
tConnInfoStruct *__cdecl BfmeConnInfoUninitializedCopy(
	tConnInfoStruct *first, tConnInfoStruct *last, tConnInfoStruct *result, const __false_type &);

tConnInfoStruct *__cdecl BfmeConnInfoUninitializedFillN(
	tConnInfoStruct *result, unsigned int count,
	const tConnInfoStruct &value, const __false_type &);

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

	Type *newFinish = BfmeConnInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeConnInfoUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeConnInfoUninitializedCopy(position, _M_finish, newFinish,
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

template class vector<tConnInfoStruct, allocator<tConnInfoStruct> >;
}

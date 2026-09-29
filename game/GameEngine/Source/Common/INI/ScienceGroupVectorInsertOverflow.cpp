// Retail 0x000BDF20, 284 bytes: STLport's
// vector<vector<W4ScienceType> >::_M_insert_overflow, the reallocating insert
// that the grow branch of _M_fill_insert (0x000BE090, matched in
// ScienceGroupVectorFillInsert.cpp) reaches through the ILT thunk
// ?j_00032bd2@@YAXXZ when the ScienceVec vector has no spare capacity.
// Its third caller, ?Rva000BE440@@YAXPAVINI@@PAX1PBX@Z (0x000BE440, matched
// from Rva000BE440ScienceGroups.cpp), types the same receiver.
//
// The name this TU carries used to be the
// vector<vector<UICoord2D> > spelling the 2026-08-11 Open-BFME5
// VectorVectorICoord2DInsertOverflowThunk.cpp lift brought in; that is
// contradicted by the callees.  The element the four copy loops stride is 12
// bytes (add esi,0xc / add edi,0xc, and 12*(oldSize+growth) at the
// allocation), and every copy of one goes through the construct helper
// 0x0000E705 -> 0x000BC360, whose own body calls 0x000BB890 through
// ?j_000012c1@@YAXXZ.  0x000BB890 is the vector copy constructor that derives
// its inner count with `sar ecx,2` and copies `mov esi,[eax]; mov [ecx],esi`
// -- a four-byte element.  ICoord2D is {long x, long y}: eight bytes, sar 3.
// The teardown callee 0x0002211F -> 0x000BDCA0 closes the same loop at 12
// bytes.  The 12-byte element is therefore a vector over a 4-byte type, and
// the matched 0x000BE090 caller fixes which one: ScienceVec =
// vector<ScienceType>.  See
// targets/game/reverse/identity_evidence/000bdf20-science-type-insert-overflow.md.
//
// No /EHsc: retail built this instantiation without an SEH frame.  The copy
// helper is deliberately not spelled _STL::_Construct -- giving it its own
// name lets this call site pin to the ILT it really calls without disturbing
// the _Construct names the ledger pins elsewhere.

enum ScienceType
{
	SCIENCE_INVALID = -1
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

template <class Type>
void __cdecl BfmeElementConstruct(Type *destination, const Type &value);

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			BfmeElementConstruct(result, *first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count,
	const Type &value)
{
	for (; count > 0; --count)
	{
		BfmeElementConstruct(result, value);
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
	void _M_clear();

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

	Type *newFinish = uninitialized_copy(_M_start, position, newStart);

	if (fillLength == 1)
	{
		BfmeElementConstruct(newFinish, value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = uninitialized_copy(position, _M_finish, newFinish);

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

}

typedef _STL::vector<ScienceType, _STL::allocator<ScienceType> > ScienceVec;

// ?_M_insert_overflow@?$vector@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@V?$allocator@V?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@_STL@@@2@@_STL@@IAEXPAV?$vector@W4ScienceType@@V?$allocator@W4ScienceType@@@_STL@@@2@ABV32@ABU__false_type@2@I_N@Z
template class _STL::vector<ScienceVec, _STL::allocator<ScienceVec> >;

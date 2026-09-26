// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport reallocating insert for a 24-byte vector element, retail
// 0x009F56C0, 334 bytes. The body carried only a machine byte-dump row and no
// name.
//
// The element type is not recoverable: both bulk phases go to the 24-byte
// helpers at 0x009F4580 and 0x009F45D0, which the ledger holds only under
// synthetic Gen_p24pod spellings. So the element is named for the address of the
// body it belongs to and modelled by width.
//
// 24 bytes is what the bytes say: both size computations go through the signed
// divide-by-twenty-four magic multiply and the byte count is a scale-2 lea plus
// a shift of three. Unlike the rest of this family the two helper calls are
// direct, not through link thunks -- the body sits above 0x009F0000, past the
// thunk table's reach. Retail hands the helpers' empty dispatch tag the address
// of its own trailing bool argument rather than spending a frame slot on it.

struct Rva009F56C0Element
{
	unsigned char m_data[24];
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

// Both helpers are called directly rather than through a link thunk -- this
// body sits above 0x009F0000, past the incremental-link thunk table's reach.
Rva009F56C0Element *__cdecl BfmeRva009F56C0Copy(
	Rva009F56C0Element *first, Rva009F56C0Element *last, Rva009F56C0Element *result, const __false_type &);

Rva009F56C0Element *__cdecl BfmeRva009F56C0FillN(
	Rva009F56C0Element *result, unsigned int count,
	const Rva009F56C0Element &value, const __false_type &);

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

	Type *newFinish = BfmeRva009F56C0Copy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeRva009F56C0FillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeRva009F56C0Copy(position, _M_finish, newFinish,
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

template class vector<Rva009F56C0Element, allocator<Rva009F56C0Element> >;
}

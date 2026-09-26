// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport reallocating insert for a 12-byte vector element, retail
// 0x00531220, 314 bytes. The body carried only a machine byte-dump row and no name.
//
// The element type is not recoverable from this body or its callees: both bulk
// phases go to that TU's own copies of the 12-byte-element helpers (0x0052D110
// and 0x0052D160, through the ILTs at 0x00017B9D and 0x00023A0B), and the
// ledger holds those only under synthetic Gen_p12pod spellings. So the element
// is named for the address of the body it belongs to and modelled by width.
//
// Twelve bytes is what the bytes say: both size computations go through the
// signed divide-by-twelve magic multiply and the new end-of-storage is a pair of
// leas. Retail hands the helpers' empty dispatch tag the address of its own
// trailing bool argument rather than spending a frame slot on it.

struct Rva00531220Element
{
	unsigned char m_data[12];
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

// Both reach this TU's own copies of the shared 12-byte-element helpers through
// their link thunks, at 0x0052D110 and 0x0052D160.
Rva00531220Element *__cdecl BfmeRva00531220Copy(
	Rva00531220Element *first, Rva00531220Element *last, Rva00531220Element *result, const __false_type &);

Rva00531220Element *__cdecl BfmeRva00531220FillN(
	Rva00531220Element *result, unsigned int count,
	const Rva00531220Element &value, const __false_type &);

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

	Type *newFinish = BfmeRva00531220Copy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeRva00531220FillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeRva00531220Copy(position, _M_finish, newFinish,
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

template class vector<Rva00531220Element, allocator<Rva00531220Element> >;
}

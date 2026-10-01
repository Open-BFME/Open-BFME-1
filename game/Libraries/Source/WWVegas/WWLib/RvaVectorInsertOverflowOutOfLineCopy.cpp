// Open-BFME5: STLport vector<T>::_M_insert_overflow for the instantiations
// whose trailing uninitialized copy stayed OUT OF LINE.  The growth path is the
// one already converted in Rva006F2C70VectorInsertOverflow.cpp -- grow to the
// old size plus the larger of the old size and the fill length, copy everything
// before the insertion point, the inserted run, and, only when the at-end flag
// is clear, everything after it, then _M_clear and the three pointers rewritten
// -- but where that file's bodies inline the last copy loop, these bodies call
// it.  The element width is the imul the copy loops stride by and the magic
// multiply that divides the byte distance; each width is confirmed by the
// matched push_back caller in RvaVectorPushBack.cpp, which is also what names
// each of these bodies.  What the element IS does not follow -- every phase is a
// call -- so each is a byte array named for the address of its push_back.

struct Rva003A35A0Element
{
	char m_body[ 184 ];
};

struct Rva0077CC10Element
{
	char m_body[ 188 ];
};

struct Rva00607770Element
{
	char m_body[ 496 ];
};

struct Rva00608FE0Element
{
	char m_body[ 528 ];
};

struct Rva00365020Element
{
	char m_body[ 180 ];
};

struct Rva003AC170Element
{
	char m_body[ 220 ];
};

struct Gen_t_00363a60_k4;
struct Gen_t_00363a60_p12cd;
struct Elem000000B4;
Elem000000B4 *Rva00363AC0(Elem000000B4 *, Elem000000B4 *, Elem000000B4 *);
struct Gen_t_003a2460_k4;
struct Gen_t_003a2460_p12cd;
struct Elem000000B8;
Elem000000B8 *Rva003A24F0(Elem000000B8 *, Elem000000B8 *, Elem000000B8 *);
struct Gen_t_003abf20_k4;
struct Gen_t_003abf20_p12cd;
struct Elem000000DC;
Elem000000DC *Rva003ABF80(Elem000000DC *, Elem000000DC *, Elem000000DC *);
struct Gen_t_00607280_k4;
struct Gen_t_00607280_p12cd;
struct Elem000001F0;
Elem000001F0 *Rva006072E0(Elem000001F0 *, Elem000001F0 *, Elem000001F0 *);
struct Gen_t_00608af0_k4;
struct Gen_t_00608af0_p12cd;
struct Elem00000210;
Elem00000210 *Rva00608B50(Elem00000210 *, Elem00000210 *, Elem00000210 *);
struct Gen_t_0013a760_k4;
struct Gen_t_0013a760_p12cd;
struct Elem000000BC;
Elem000000BC *Rva007747E0(Elem000000BC *, Elem000000BC *, Elem000000BC *);
struct S4Poly00362990;
struct Gen00606F70;
struct S4Elem00608D40;

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

template <class First, class Second> struct pair;
template <class Destination, class Source>
void _Construct(Destination *, const Source &);
template <class Type> struct RvaConstructionPair;
template <> struct RvaConstructionPair<Rva00365020Element> { typedef pair<const Gen_t_00363a60_k4, Gen_t_00363a60_p12cd> Type; };
template <> struct RvaConstructionPair<Rva003A35A0Element> { typedef pair<const Gen_t_003a2460_k4, Gen_t_003a2460_p12cd> Type; };
template <> struct RvaConstructionPair<Rva003AC170Element> { typedef pair<const Gen_t_003abf20_k4, Gen_t_003abf20_p12cd> Type; };
template <> struct RvaConstructionPair<Rva00607770Element> { typedef pair<const Gen_t_00607280_k4, Gen_t_00607280_p12cd> Type; };
template <> struct RvaConstructionPair<Rva00608FE0Element> { typedef pair<const Gen_t_00608af0_k4, Gen_t_00608af0_p12cd> Type; };
template <> struct RvaConstructionPair<Rva0077CC10Element> { typedef pair<const Gen_t_0013a760_k4, Gen_t_0013a760_p12cd> Type; };

template <class Type>
__forceinline void BfmeElementConstruct(Type *destination, const Type &value)
{
    typedef typename RvaConstructionPair<Type>::Type Pair;
    _Construct<Pair, Pair>((Pair *)destination, reinterpret_cast<const Pair &>(value));
}

// Retail passes an unused cdecl tag; the cast preserves that stack argument.
__forceinline Rva00365020Element *BfmeRva00365020Copy(Rva00365020Element *const &first,
    Rva00365020Element *const &last, Rva00365020Element *const &result, const __false_type &tag)
{
    typedef Rva00365020Element *(__cdecl *CopyWithTag)(Rva00365020Element *, Rva00365020Element *, Rva00365020Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva00363AC0)(first, last, result, tag);
}

__forceinline Rva003A35A0Element *BfmeRva003A35A0Copy(Rva003A35A0Element *const &first,
    Rva003A35A0Element *const &last, Rva003A35A0Element *const &result, const __false_type &tag)
{
    typedef Rva003A35A0Element *(__cdecl *CopyWithTag)(Rva003A35A0Element *, Rva003A35A0Element *, Rva003A35A0Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva003A24F0)(first, last, result, tag);
}

__forceinline Rva003AC170Element *BfmeRva003AC170Copy(Rva003AC170Element *const &first,
    Rva003AC170Element *const &last, Rva003AC170Element *const &result, const __false_type &tag)
{
    typedef Rva003AC170Element *(__cdecl *CopyWithTag)(Rva003AC170Element *, Rva003AC170Element *, Rva003AC170Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva003ABF80)(first, last, result, tag);
}

__forceinline Rva00607770Element *BfmeRva00607770Copy(Rva00607770Element *const &first,
    Rva00607770Element *const &last, Rva00607770Element *const &result, const __false_type &tag)
{
    typedef Rva00607770Element *(__cdecl *CopyWithTag)(Rva00607770Element *, Rva00607770Element *, Rva00607770Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva006072E0)(first, last, result, tag);
}

__forceinline Rva00608FE0Element *BfmeRva00608FE0Copy(Rva00608FE0Element *const &first,
    Rva00608FE0Element *const &last, Rva00608FE0Element *const &result, const __false_type &tag)
{
    typedef Rva00608FE0Element *(__cdecl *CopyWithTag)(Rva00608FE0Element *, Rva00608FE0Element *, Rva00608FE0Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva00608B50)(first, last, result, tag);
}

__forceinline Rva0077CC10Element *BfmeRva0077CC10Copy(Rva0077CC10Element *const &first,
    Rva0077CC10Element *const &last, Rva0077CC10Element *const &result, const __false_type &tag)
{
    typedef Rva0077CC10Element *(__cdecl *CopyWithTag)(Rva0077CC10Element *, Rva0077CC10Element *, Rva0077CC10Element *, const __false_type &);
    return reinterpret_cast<CopyWithTag>(::Rva007747E0)(first, last, result, tag);
}

// The trailing copies are pinned under per-element names, so one overload
// set on the tag argument is what lets a single template body reach each.
// The pointers go by reference: a by-value parameter survives inlining as a
// temp, and that temp lands in a different register than the direct load.
__forceinline Rva003A35A0Element *uninitialized_copy(
	Rva003A35A0Element *const &first, Rva003A35A0Element *const &last,
	Rva003A35A0Element *const &result, const __false_type &tag)
{
	return BfmeRva003A35A0Copy(first, last, result, tag);
}

__forceinline Rva0077CC10Element *uninitialized_copy(
	Rva0077CC10Element *const &first, Rva0077CC10Element *const &last,
	Rva0077CC10Element *const &result, const __false_type &tag)
{
	return BfmeRva0077CC10Copy(first, last, result, tag);
}

__forceinline Rva00607770Element *uninitialized_copy(
	Rva00607770Element *const &first, Rva00607770Element *const &last,
	Rva00607770Element *const &result, const __false_type &tag)
{
	return BfmeRva00607770Copy(first, last, result, tag);
}

__forceinline Rva00608FE0Element *uninitialized_copy(
	Rva00608FE0Element *const &first, Rva00608FE0Element *const &last,
	Rva00608FE0Element *const &result, const __false_type &tag)
{
	return BfmeRva00608FE0Copy(first, last, result, tag);
}

__forceinline Rva00365020Element *uninitialized_copy(
	Rva00365020Element *const &first, Rva00365020Element *const &last,
	Rva00365020Element *const &result, const __false_type &tag)
{
	return BfmeRva00365020Copy(first, last, result, tag);
}

__forceinline Rva003AC170Element *uninitialized_copy(
	Rva003AC170Element *const &first, Rva003AC170Element *const &last,
	Rva003AC170Element *const &result, const __false_type &tag)
{
	return BfmeRva003AC170Copy(first, last, result, tag);
}

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
__forceinline Type *uninitialized_fill_n(Type *result, unsigned int count, const Type &value)
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
public:
    ~vector();
protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);
	void _M_clear();

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <> __forceinline void vector<Rva00365020Element, allocator<Rva00365020Element> >::_M_clear()
{
    reinterpret_cast<vector<S4Poly00362990, allocator<S4Poly00362990> > *>(this)->~vector();
}

template <> __forceinline void vector<Rva00607770Element, allocator<Rva00607770Element> >::_M_clear()
{
    reinterpret_cast<vector<Gen00606F70, allocator<Gen00606F70> > *>(this)->~vector();
}

template <> __forceinline void vector<Rva00608FE0Element, allocator<Rva00608FE0Element> >::_M_clear()
{
    reinterpret_cast<vector<S4Elem00608D40, allocator<S4Elem00608D40> > *>(this)->~vector();
}

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
		newFinish = uninitialized_copy(position, _M_finish, newFinish,
			reinterpret_cast<const __false_type &>(atEnd));

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

// ?_M_insert_overflow@?$vector@URva003A35A0Element@@V?$allocator@URva003A35A0Element@@@_STL@@@_STL@@IAEXPAURva003A35A0Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva003A35A0Element, allocator<Rva003A35A0Element> >;

// ?_M_insert_overflow@?$vector@URva0077CC10Element@@V?$allocator@URva0077CC10Element@@@_STL@@@_STL@@IAEXPAURva0077CC10Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva0077CC10Element, allocator<Rva0077CC10Element> >;

// ?_M_insert_overflow@?$vector@URva00607770Element@@V?$allocator@URva00607770Element@@@_STL@@@_STL@@IAEXPAURva00607770Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00607770Element, allocator<Rva00607770Element> >;

// ?_M_insert_overflow@?$vector@URva00608FE0Element@@V?$allocator@URva00608FE0Element@@@_STL@@@_STL@@IAEXPAURva00608FE0Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00608FE0Element, allocator<Rva00608FE0Element> >;

// ?_M_insert_overflow@?$vector@URva00365020Element@@V?$allocator@URva00365020Element@@@_STL@@@_STL@@IAEXPAURva00365020Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva00365020Element, allocator<Rva00365020Element> >;

// ?_M_insert_overflow@?$vector@URva003AC170Element@@V?$allocator@URva003AC170Element@@@_STL@@@_STL@@IAEXPAURva003AC170Element@@ABU3@ABU__false_type@2@I_N@Z
template class vector<Rva003AC170Element, allocator<Rva003AC170Element> >;
}

// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<ParkingPlaceBehavior::RunwayInfo> reallocating
// insert, retail 0x0074DCB0, 344 bytes. The body carried only a machine
// byte-dump row and no name at all -- this spelling was nowhere in the ledger.
//
// The tail move names it: __uninitialized_copy at 0x0074AAC0, reached through
// the ILT at 0x00021A1C, is the ledger's RunwayInfo spelling.
//
// The element is 36 bytes -- two Coord3Ds, two ObjectIDs and a Bool with its
// three bytes of padding -- so the size arithmetic is the signed
// divide-by-thirty-six magic multiply, the byte count is a scale-8 lea plus a
// shift of two, and each per-element copy is a 9-dword rep movsd behind the
// placement-new null check.
//
// Like the vector<WeaponTemplateSet> body this is a hybrid: the leading copy and
// the fill inline, the tail move out of line. Retail hands that helper's empty
// dispatch tag the address of its own trailing bool argument rather than
// spending a frame slot on it.

enum ObjectID
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
class ParkingPlaceBehavior
{
public:
	struct RunwayInfo
	{
		Coord3D m_start;
		Coord3D m_end;
		ObjectID m_inUseBy;
		ObjectID m_nextInLineForTakeoff;
		bool m_wasInLine;
	};
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
static void vectorSmallDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	friend void vectorSmallDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorLargeAllocate(unsigned int bytes) { return ::operator new(bytes); }
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }
static inline void vectorLargeDeallocate(void *block) { ::operator delete(block); }
static inline void vectorSmallDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

struct __false_type
{
};

// The tail move is the one phase retail leaves out of line; it reaches
// __uninitialized_copy at 0x0074AAC0 through the ILT at 0x00021A1C, so the name
// is declared apart from the _STL spelling that owns the real body.
ParkingPlaceBehavior::RunwayInfo *__cdecl BfmeRunwayInfoUninitializedCopy(
	ParkingPlaceBehavior::RunwayInfo *first, ParkingPlaceBehavior::RunwayInfo *last, ParkingPlaceBehavior::RunwayInfo *result,
	const __false_type &);

template <class Type>
class allocator {};

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			new (result) Type(*first);
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
		new (result) Type(value);
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
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
		newFinish = BfmeRunwayInfoUninitializedCopy(position, _M_finish, newFinish,
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

template class vector<ParkingPlaceBehavior::RunwayInfo, allocator<ParkingPlaceBehavior::RunwayInfo> >;
}

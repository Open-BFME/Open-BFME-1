// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<W3DModelDraw::WeaponRecoilInfo> reallocating
// insert, retail 0x002109B0, 314 bytes. The name shared the 5-byte
// incremental-link thunk at 0x0000E868 with the vector<State::TransitionInfo>
// spelling, and the body it jumps to carried only a machine byte-dump row.
//
// The callees settle which of the two owns it: both bulk phases reach helpers
// the ledger already names for WeaponRecoilInfo -- __uninitialized_copy at
// 0x0020E2C0 through the ILT at 0x00027525 and __uninitialized_fill_n at
// 0x0020E310 through the ILT at 0x00049459 -- and both sit a couple of KB below
// this body. The TransitionInfo spelling keeps its thunk row.
//
// The element is 12 bytes -- a state enum and two Reals -- so both size
// computations go through the signed divide-by-twelve magic multiply and the
// new end-of-storage is a pair of leas. Retail hands the helpers' empty dispatch
// tag the address of its own trailing bool argument rather than spending a frame
// slot on it.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
class W3DModelDraw
{
public:
	// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DModelDraw.h
	struct WeaponRecoilInfo
	{
		int m_state;
		float m_shift;
		float m_recoilRate;
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

template <class Input, class Output>
Output __cdecl __uninitialized_copy(Input first, Input last, Output result,
	const __false_type &tag);

template <class Output, class Size, class Value>
Output __cdecl __uninitialized_fill_n(Output result, Size count,
	const Value &value, const __false_type &tag);

template <class Type>
class allocator
{
};

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

	Type *newFinish = __uninitialized_copy<W3DModelDraw::WeaponRecoilInfo *, W3DModelDraw::WeaponRecoilInfo *>(
		_M_start, position, newStart, reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = __uninitialized_fill_n<W3DModelDraw::WeaponRecoilInfo *, unsigned int, W3DModelDraw::WeaponRecoilInfo>(
			newFinish, fillLength, value, reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = __uninitialized_copy<W3DModelDraw::WeaponRecoilInfo *, W3DModelDraw::WeaponRecoilInfo *>(
			position, _M_finish, newFinish, reinterpret_cast<const __false_type &>(atEnd));

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

template class vector<W3DModelDraw::WeaponRecoilInfo, allocator<W3DModelDraw::WeaponRecoilInfo> >;
}

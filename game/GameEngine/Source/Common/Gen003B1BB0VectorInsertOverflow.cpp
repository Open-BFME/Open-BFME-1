// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// The retail body at 0x003B1340 grows a 16-byte STLport vector payload.
// The vector pin and the Gen003B1DF0 caller identify the template instance.

struct Gen_t_003b1bb0_p16cd
{
	char m_body[ 0x10 ];
};

struct P6Elem003B1DF0
{
	char m_body[ 0x10 ];
};

// Retail's overflow body at 0x003B1340 calls the linker-assigned
// vector<W3DAnimationInfo>::_M_clear at 0x003B0E90, not a
// vector<Gen_t_003b1bb0_p16cd>::_M_clear, so the call is made through that
// instantiation instead of being aliased onto it. Only the name matters here;
// the clear body itself lives in W3DAnimationInfoVectorClearBody.cpp.
class W3DAnimationInfo;

void __cdecl Bfme003B1DF0Construct(
	P6Elem003B1DF0 *destination, const P6Elem003B1DF0 &value);

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

class __new_alloc
{
public:
	static void *__cdecl allocate(unsigned int bytes);
};

template <class Type>
__forceinline void construct(Type *destination, const Type &value)
{
	Bfme003B1DF0Construct(
		reinterpret_cast<P6Elem003B1DF0 *>(destination),
		reinterpret_cast<const P6Elem003B1DF0 &>(value));
}

template <class Type>
__forceinline Type *uninitialized_copy(Type *first, Type *last, Type *result)
{
	if (first != last)
	{
		do
		{
			construct(result, *first);
			++first;
			++result;
		}
		while (first != last);
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n(
	Type *result, unsigned int count, const Type &value)
{
	for (; count > 0; --count)
	{
		construct(result, value);
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
protected:
	// The overflow body below reaches the protected _M_clear of the
	// vector<W3DAnimationInfo> instance the linker gave it; a friend, not a
	// wider access level, because retail's name carries the protected code.
	template <class FriendType, class FriendAllocator>
	friend class vector;

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
			newStart = (Type *)::operator new(bytes);
		else
			newStart = (Type *)__new_alloc::allocate(bytes);
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = uninitialized_copy(_M_start, position, newStart);

	if (fillLength == 1)
	{
		construct(newFinish, value);
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n(newFinish, fillLength, value);
	}

	if (!atEnd)
	{
		Type *last = _M_finish;
		if (position != last)
			newFinish = uninitialized_copy(position, last, newFinish);
	}

	// Retail calls the linker-assigned vector<W3DAnimationInfo>::_M_clear here
	// (0x003B0E90) with this in ecx. That clear is a real matched row in
	// W3DAnimationInfoVectorClearBody.cpp, so it is called through its own name
	// instead of being aliased onto the name this instantiation would mint.
	reinterpret_cast<vector<W3DAnimationInfo,
		allocator<W3DAnimationInfo> > *>(this)->_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}
}

template class _STL::vector<Gen_t_003b1bb0_p16cd,
	_STL::allocator<Gen_t_003b1bb0_p16cd> >;

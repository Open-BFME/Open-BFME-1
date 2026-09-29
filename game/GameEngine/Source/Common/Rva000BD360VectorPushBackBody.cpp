// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<T>::push_back over a 112-byte element, retail
// 0x000BD360, 62 bytes. The body carried only a machine byte-dump row and no name.
//
// Two paths and nothing else: with room left it constructs at the finish pointer
// through the ILT at 0x0000A97A and steps the pointer by the element width;
// with none it hands the whole thing to _M_insert_overflow through the ILT at
// 0x00025275 with a fill length of one and the at-end flag set. Retail reloads
// the finish pointer from the object after the construct call rather than
// reusing the copy it already had, which is what a plain `++_M_finish` on a
// member produces.
//
// The empty dispatch tag is aliased onto the value parameter's own stack slot,
// the same trick the _M_insert_overflow family uses on its trailing bool.
//
// Identity is not recovered: the element width is the only axis, so the element
// is named for the address of the body and modelled by width.

struct P5Elem000BD360
{
	char m_body[ 0x70 ];
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

void __cdecl Bfme000BD360Construct( P5Elem000BD360 *destination, const P5Elem000BD360 &value );
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
__forceinline Type *uninitialized_copy( Type *first, Type *last, Type *result )
{
	if ( first != last )
	{
		do
		{
			Bfme000BD360Construct( result, *first );
			++first;
			++result;
		}
		while ( first != last );
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n( Type *result, unsigned int count, const Type &value )
{
	for ( ; count > 0; --count )
	{
		Bfme000BD360Construct( result, value );
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
public:
	void push_back( const Type *value );

protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
	void _M_clear();

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::push_back( const Type *value )
{
	if ( _M_finish != _M_end_of_storage )
	{
		Bfme000BD360Construct( _M_finish, *value );
		++_M_finish;
	}
	else
	{
		_M_insert_overflow( _M_finish, *value, reinterpret_cast<const __false_type &>( value ), 1, true );
	}
}

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
	unsigned int fillLength, bool atEnd )
{
	unsigned int oldSize = (unsigned int)(_M_finish - _M_start);
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if ( length )
	{
		unsigned int bytes = length * sizeof(Type);
		if ( bytes > 128 )
			newStart = (Type *)vectorLargeAllocate( bytes );
		else
			newStart = (Type *)vectorSmallAllocate( bytes );
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = uninitialized_copy( _M_start, position, newStart );

	if ( fillLength == 1 )
	{
		Bfme000BD360Construct( newFinish, value );
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n( newFinish, fillLength, value );
	}

	if ( !atEnd )
		newFinish = uninitialized_copy( position, _M_finish, newFinish );

	_M_clear();

	_M_finish = newFinish;
	_M_start = newStart;
	_M_end_of_storage = newStart + length;
}

template class vector<P5Elem000BD360, allocator<P5Elem000BD360> >;
}

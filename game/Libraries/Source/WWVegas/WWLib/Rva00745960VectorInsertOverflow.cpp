// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

struct Gen_t_007463a0_p24cd
{
	char bytes[ 24 ];
};

struct Rva007417A0Element
{
	char bytes[ 24 ];
};

// Retail reached the element copy through the ILT thunk at 0x000349FF; the
// call sites therefore name that thunk directly.
extern void j_000349ff();

static __forceinline void elementConstruct( void *destination, const void *source )
{
	typedef void (__cdecl *Fn)( void *, const void * );
	( ( Fn )( void * )j_000349ff )( destination, source );
}

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
static void nodePoolDeallocate(void *block, unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void nodePoolDeallocate(void *, unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void nodePoolDeallocate(void *block, unsigned int bytes) { __node_alloc<true, 0>::_M_deallocate(block, bytes); }

class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

template <class Type>
__forceinline Type *uninitialized_copy( Type *first, Type *last, Type *result )
{
	if ( first != last )
	{
		do
		{
			elementConstruct( result, &*first );
			++first;
			++result;
		}
		while ( first != last );
	}
	return result;
}

template <class Type>
__forceinline Type *uninitialized_fill_n( Type *result, unsigned int count,
	const Type &value )
{
	for ( ; count > 0; --count )
	{
		elementConstruct( result, &value );
		++result;
	}
	return result;
}

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *m_start;
	Type *m_finish;
	Type *m_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow( Type *position,
	const Type &value, const __false_type &, unsigned int fillLength, bool atEnd )
{
	unsigned int oldSize = ( unsigned int )( m_finish - m_start );
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if ( length != 0 )
	{
		unsigned int bytes = length * sizeof( Type );
		if ( bytes > 128 )
			newStart = ( Type * )::operator new( bytes );
		else
			newStart = ( Type * )__new_alloc::allocate( bytes );
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = uninitialized_copy( m_start, position, newStart );
	if ( fillLength == 1 )
	{
		elementConstruct( newFinish, &value );
		++newFinish;
	}
	else
	{
		newFinish = uninitialized_fill_n( newFinish, fillLength, value );
	}

	if ( !atEnd )
	{
		Type *last = m_finish;
		if ( position != last )
			newFinish = uninitialized_copy( position, last, newFinish );
	}

	Type *oldStart = m_start;
	if ( oldStart != 0 )
	{
		unsigned int oldBytes = ( unsigned int )( m_end_of_storage - oldStart ) * sizeof( Type );
		if ( oldBytes > 128 )
			::operator delete( oldStart );
		else
			_STL::nodePoolDeallocate( oldStart, oldBytes );
	}

	m_finish = newFinish;
	m_start = newStart;
	m_end_of_storage = newStart + length;
}
}

template class _STL::vector<Gen_t_007463a0_p24cd, _STL::allocator<Gen_t_007463a0_p24cd> >;

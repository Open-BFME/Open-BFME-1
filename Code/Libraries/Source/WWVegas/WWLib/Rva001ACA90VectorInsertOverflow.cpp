// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: STLport vector growth for the 48-byte generated payload at
// retail 0x001ACA90. The caller and the pinned element-construction target
// prove the container shape, but not the payload identity.

struct Gen_t_001acec0_p48cd
{
	int a[12];
	Gen_t_001acec0_p48cd();
	Gen_t_001acec0_p48cd( const Gen_t_001acec0_p48cd & );
	~Gen_t_001acec0_p48cd();
	Gen_t_001acec0_p48cd &operator=( const Gen_t_001acec0_p48cd & );
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

void *__cdecl vectorLargeAllocate( unsigned int bytes );
void *__cdecl vectorSmallAllocate( unsigned int bytes );

template <class Type>
void __cdecl _Construct( Type *destination, const Type &value );

template <class Type>
__forceinline Type *uninitialized_copy( Type *first, Type *last, Type *result )
{
	if ( first != last )
	{
		do
		{
			_Construct( result, *first );
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
		_Construct( result, value );
		++result;
	}
	return result;
}

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *address, unsigned int bytes );
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
	void _M_clear()
	{
		Type *start = _M_start;
		if ( start != 0 )
		{
			unsigned int bytes = (unsigned int)((_M_end_of_storage - start) * sizeof( Type ));
			if ( bytes > 128 )
				::operator delete( start );
			else
				__node_alloc<true, 0>::_M_deallocate( start, bytes );
		}
	}

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

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
		unsigned int bytes = length * sizeof( Type );
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
		_Construct( newFinish, value );
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

template class vector<Gen_t_001acec0_p48cd, allocator<Gen_t_001acec0_p48cd> >;
}

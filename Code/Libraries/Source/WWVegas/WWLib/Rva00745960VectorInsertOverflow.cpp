// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

struct Gen_t_007463a0_p24cd
{
	char bytes[ 24 ];
};

struct Rva007417A0Element
{
	char bytes[ 24 ];
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

template <bool threads, int instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *memory, unsigned int bytes );
};

class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

template <class Type>
void BfmeElementConstruct( void *destination, const Type &source );

template <>
void BfmeElementConstruct<Rva007417A0Element>(
	void *destination, const Rva007417A0Element &source );

template <class Type>
__forceinline Type *uninitialized_copy( Type *first, Type *last, Type *result )
{
	if ( first != last )
	{
		do
		{
			BfmeElementConstruct<Rva007417A0Element>(
				( Rva007417A0Element * )result,
				( const Rva007417A0Element & )*first );
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
		BfmeElementConstruct<Rva007417A0Element>(
			( Rva007417A0Element * )result,
			( const Rva007417A0Element & )value );
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
		BfmeElementConstruct<Rva007417A0Element>(
			( Rva007417A0Element * )newFinish,
			( const Rva007417A0Element & )value );
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
			__node_alloc<true, 0>::_M_deallocate( oldStart, oldBytes );
	}

	m_finish = newFinish;
	m_start = newStart;
	m_end_of_storage = newStart + length;
}
}

#pragma comment( linker, "/alternatename:??$BfmeElementConstruct@URva007417A0Element@@@_STL@@YAXPAURva007417A0Element@@ABU1@@Z=?j_000349ff@@YAXXZ" )

template class _STL::vector<Gen_t_007463a0_p24cd, _STL::allocator<Gen_t_007463a0_p24cd> >;

// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME: STLport vector insertion member at retail RVA 0x00282910.
// targets/game/reverse/reloc_names.csv names this 246-byte body as the
// _M_insert_overflow specialization for Gen_t_00282af0_p12pod. The local
// STLport declarations keep the copy helpers and vector clear call out of line,
// matching the retail thunks instead of generating a larger exception-aware body.

struct Gen_t_00282af0_p12pod
{
	int a[3];
};

void *operator new( unsigned int bytes );

namespace _STL
{
struct __false_type
{
};

class __new_alloc
{
public:
	static void *allocate( unsigned int bytes );
};

template <class Type>
class allocator
{
};

template <class Input, class Output>
Output __cdecl __uninitialized_copy( Input first, Input last, Output result,
	const __false_type &tag );

template <class Output, class Size, class Value>
Output __cdecl __uninitialized_fill_n( Output result, Size count,
	const Value &value, const __false_type &tag );

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );
	void _M_clear();

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &tag,
	unsigned int fillLength, bool atEnd )
{
	unsigned int oldSize = (unsigned int)( m_finish - m_start );
	const unsigned int &growth = oldSize < fillLength ? fillLength : oldSize;
	unsigned int length = growth + oldSize;

	Type *newStart;
	if ( length )
	{
		unsigned int bytes = length * sizeof( Type );
		if ( bytes > 128 )
			newStart = (Type *)::operator new( bytes );
		else
			newStart = (Type *)__new_alloc::allocate( bytes );
	}
	else
	{
		newStart = 0;
	}

	Type *newFinish = __uninitialized_copy( m_start, position, newStart,
		reinterpret_cast<const __false_type &>( atEnd ) );

	if ( fillLength == 1 )
	{
		if ( newFinish != 0 )
			*newFinish = value;
		++newFinish;
	}
	else
	{
		newFinish = __uninitialized_fill_n( newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>( atEnd ) );
	}

	if ( !atEnd )
		newFinish = __uninitialized_copy( position, m_finish, newFinish,
			reinterpret_cast<const __false_type &>( atEnd ) );

	_M_clear();

	m_start = newStart;
	m_finish = newFinish;
	m_endOfStorage = newStart + length;
}
}

template class _STL::vector<Gen_t_00282af0_p12pod,
	_STL::allocator<Gen_t_00282af0_p12pod> >;

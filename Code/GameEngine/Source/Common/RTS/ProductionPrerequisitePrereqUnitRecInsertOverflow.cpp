// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Retail's 281-byte PrereqUnitRec vector overflow body at 0x00584650.
//
// ProductionPrerequisite.cpp still owns the ordinary vector members and their
// source-level behaviour.  This focused instantiation keeps the BFME STLport
// overflow specialization's no-EH, inlined copy/fill shape independent of the
// exception-aware Zero Hour header instantiation.

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		unsigned char m_data[ 12 ];
	};
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

template <class T1, class T2>
void _Construct( T1 *destination, const T2 &value );

void *__cdecl vectorLargeAllocate( unsigned int bytes );
void *__cdecl vectorSmallAllocate( unsigned int bytes );

template <class Type, class Allocator>
class vector
{
protected:
	void _M_clear_retail();
	void _M_insert_overflow( Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd );

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type>
__forceinline Type *_uninitialized_copy( Type *first, Type *last, Type *result,
	const __false_type &tag )
{
	while ( first != last )
	{
		_Construct( result, *first );
		++first;
		++result;
	}
	return result;
}

template <class Type>
__forceinline Type *_uninitialized_fill_n( Type *result, unsigned int count,
	const Type &value, const __false_type &tag )
{
	if ( count > 0 )
	{
		do
		{
			_Construct( result, value );
			++result;
			--count;
		}
		while ( count > 0 );
	}
	return result;
}

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &tag,
	unsigned int fillLength, bool atEnd )
{
	unsigned int oldSize = (unsigned int)( _M_finish - _M_start );
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

	Type *newFinish = _uninitialized_copy( _M_start, position, newStart, tag );
	if ( fillLength == 1 )
	{
		_Construct( newFinish, value );
		++newFinish;
	}
	else
		newFinish = _uninitialized_fill_n( newFinish, fillLength, value, tag );

	if ( !atEnd )
		newFinish = _uninitialized_copy( position, _M_finish, newFinish, tag );

	_M_clear_retail();
	_M_start = newStart;
	_M_finish = newFinish;
	_M_end_of_storage = newStart + length;
}

template void vector<ProductionPrerequisite::PrereqUnitRec,
	allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_insert_overflow(
	ProductionPrerequisite::PrereqUnitRec *,
	const ProductionPrerequisite::PrereqUnitRec &, const __false_type &,
	unsigned int, bool );
}

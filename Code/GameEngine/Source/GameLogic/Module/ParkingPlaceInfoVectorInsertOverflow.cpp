// cl: /O2
// Open-BFME5: near-twin of _M_insert_overflow<Rva006AACB0Element> (twin
// 0x006A7290, Code/Libraries/Source/WWVegas/WWLib/Rva006F2C70VectorInsertOverflow.cpp).
// Same generic STLport vector growth path, but the 60-byte element is the
// real ParkingPlaceBehavior::ParkingPlaceInfo (Coord3D+Real+Coord3D+Coord3D+
// Real+Int+ExitDoorType+ObjectID+Bool = 60 bytes) rather than an opaque
// address-derived blob; the placement-construct callee is the already-pinned
// STLport ??$_Construct@UParkingPlaceInfo@ParkingPlaceBehavior@@... at
// 0x0003E4BE, and the two allocation paths call the real operator new
// (0x00881F30) and _STL::__new_alloc::allocate (0x0082E540) directly instead
// of through a local vectorLargeAllocate/vectorSmallAllocate wrapper.

#include <stddef.h>

struct Coord3D { float x, y, z; };
typedef float Real;
typedef int Int;
typedef unsigned int ObjectID;

void *operator new( size_t bytes );

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate( unsigned int n );
};

struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class T1, class T2>
void __cdecl _Construct( T1 *destination, const T2 &value );

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
__forceinline Type *uninitialized_fill_n( Type *result, unsigned int count, const Type &value )
{
	for ( ; count > 0; --count )
	{
		_Construct( result, value );
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
	void _M_clear();

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};

template <class Type, class Allocator>
void vector<Type, Allocator>::_M_insert_overflow(
	Type *position, const Type &value, const __false_type &,
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
			newStart = (Type *)operator new( bytes );
		else
			newStart = (Type *)__new_alloc::allocate( bytes );
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
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/ParkingPlaceBehavior.h
class ParkingPlaceBehavior
{
public:
	struct ParkingPlaceInfo
	{
		Coord3D		m_hangarStart;
		Real			m_hangarStartOrient;
		Coord3D		m_location;
		Coord3D		m_prep;
		Real			m_orientation;
		Int			m_runway;
		Int			m_door;
		ObjectID	m_objectInSpace;
		Int			m_reservedForExit;
	};
};

// ?_M_insert_overflow@?$vector@UParkingPlaceInfo@ParkingPlaceBehavior@@V?$allocator@UParkingPlaceInfo@ParkingPlaceBehavior@@@_STL@@@_STL@@IAEXPAUParkingPlaceInfo@ParkingPlaceBehavior@@ABU3@ABU__false_type@2@I_N@Z
template class _STL::vector<ParkingPlaceBehavior::ParkingPlaceInfo,
	_STL::allocator<ParkingPlaceBehavior::ParkingPlaceInfo> >;

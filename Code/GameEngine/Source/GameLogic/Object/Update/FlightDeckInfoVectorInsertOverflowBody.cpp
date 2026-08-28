// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS

// Open-BFME5: STLport vector<FlightDeckBehavior::FlightDeckInfo> reallocating
// insert, retail 0x00231A00, 334 bytes. The name sat on the 5-byte
// incremental-link thunk at 0x0000A47A and the body it jumps to carried only a
// machine byte-dump row.
//
// The callees confirm the element: both bulk phases reach helpers the ledger
// already names for FlightDeckInfo -- __uninitialized_copy at 0x0022FE20
// through the ILT at 0x0002894D and __uninitialized_fill_n at 0x0022FE80
// through the ILT at 0x00017E0E.
//
// The element is 24 bytes -- a Coord3D, a Real, an Int and an ObjectID -- so
// both size computations go through the signed divide-by-twenty-four magic
// multiply and the byte count is a lea followed by a shift of three. Retail
// hands the helpers' empty dispatch tag the address of its own trailing bool
// argument rather than spending a frame slot on it.

enum ObjectID
{
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
class FlightDeckBehavior
{
public:
	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FlightDeckBehavior.h
	struct FlightDeckInfo
	{
		Coord3D m_prep;
		float m_orientation;
		int m_runway;
		ObjectID m_objectInSpace;
	};
};

inline void *__cdecl operator new(unsigned int, void *where)
{
	return where;
}

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);
void __cdecl vectorLargeDeallocate(void *block);
void __cdecl vectorSmallDeallocate(void *block, unsigned int bytes);

struct __false_type
{
};

template <class Type>
class allocator
{
};

// Both reach the helpers the ledger already names for this element through
// their link thunks; naming them apart from the _STL spellings keeps those
// names on their real bodies at 0x0022FE20 and 0x0022FE80.
FlightDeckBehavior::FlightDeckInfo *__cdecl BfmeFlightDeckInfoUninitializedCopy(
	FlightDeckBehavior::FlightDeckInfo *first, FlightDeckBehavior::FlightDeckInfo *last, FlightDeckBehavior::FlightDeckInfo *result, const __false_type &);

FlightDeckBehavior::FlightDeckInfo *__cdecl BfmeFlightDeckInfoUninitializedFillN(
	FlightDeckBehavior::FlightDeckInfo *result, unsigned int count,
	const FlightDeckBehavior::FlightDeckInfo &value, const __false_type &);

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

	Type *newFinish = BfmeFlightDeckInfoUninitializedCopy(_M_start, position, newStart,
		reinterpret_cast<const __false_type &>(atEnd));

	if (fillLength == 1)
	{
		new (newFinish) Type(value);
		++newFinish;
	}
	else
	{
		newFinish = BfmeFlightDeckInfoUninitializedFillN(newFinish, fillLength, value,
			reinterpret_cast<const __false_type &>(atEnd));
	}

	if (!atEnd)
		newFinish = BfmeFlightDeckInfoUninitializedCopy(position, _M_finish, newFinish,
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

template class vector<FlightDeckBehavior::FlightDeckInfo, allocator<FlightDeckBehavior::FlightDeckInfo> >;
}

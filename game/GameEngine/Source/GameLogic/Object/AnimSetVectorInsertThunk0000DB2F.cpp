// Retail RVA 0x0000DB2F, five-byte ILT.
// The symbols pin and AnimSetVectorInsert.cpp route this thunk to 0x00755CA0.

// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

typedef int Int;

class GenericObjectCreationNugget
{
public:
	struct AnimSet
	{
		AsciiString m_bfmeName;
		Int m_bfmeFirst;
		Int m_bfmeSecond;
	};
};

namespace _STL
{
struct __false_type
{
};

class GenericObjectCreationNuggetAnimSetInsertOverflowShim
{
public:
	void insert_overflow(GenericObjectCreationNugget::AnimSet *,
		const GenericObjectCreationNugget::AnimSet &, const __false_type &,
		unsigned int, bool);
};

template <class T>
class allocator
{
};

template <class T, class Allocator>
class vector
{
public:
	void d_0000db2f(T *position, const T &value, const __false_type &tag,
		unsigned int fillLength, bool atEnd)
	{
		((GenericObjectCreationNuggetAnimSetInsertOverflowShim *)this)->insert_overflow(
			position, value, tag, fillLength, atEnd);
	}
};

template class vector<GenericObjectCreationNugget::AnimSet,
	allocator<GenericObjectCreationNugget::AnimSet> >;
}

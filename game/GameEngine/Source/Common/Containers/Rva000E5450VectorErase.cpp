// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"

struct Rva000E5450Record
{
	unsigned int word0;
	unsigned int word4;
	AsciiString name;

	Rva000E5450Record &operator=(const Rva000E5450Record &other)
	{
		word0 = other.word0;
		word4 = other.word4;
		name = other.name;
		return *this;
	}

	~Rva000E5450Record();
};

template Rva000E5450Record *_STL::vector<Rva000E5450Record,
	_STL::allocator<Rva000E5450Record> >::erase(
	Rva000E5450Record *, Rva000E5450Record *);

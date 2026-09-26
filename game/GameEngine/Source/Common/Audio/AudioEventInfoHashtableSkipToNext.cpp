// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "Common/STLTypedefs.h"
#include <hash_map>

struct AudioEventInfo;

// The callsite at 0x00460DA0 resolves its bucket operation to the concrete
// Rva004613F0 hashtable copy.  This is the same STLport iterator algorithm as
// the AudioEventInfo map, but retaining that independent value/extractor name
// makes the relocation identity honest instead of aliasing two copies.
struct Rva004613F0Value
{
	const AsciiString first;
	AudioEventInfo *second;
};

struct Rva004613F0ExtractKey
{
	const AsciiString &operator()(const Rva004613F0Value &value) const
	{
		return value.first;
	}
};

typedef _STL::hashtable<
	Rva004613F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004613F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004613F0Value> > Rva004613F0Hashtable;

template struct _STL::_Hashtable_iterator<
	Rva004613F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004613F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004613F0Value> >;

struct Rva00461360Value
{
	const AsciiString first;
	AudioEventInfo *second;
};

struct Rva00461360ExtractKey
{
	const AsciiString &operator()(const Rva00461360Value &value) const
	{
		return value.first;
	}
};

template struct _STL::_Hashtable_iterator<
	Rva00461360Value, AsciiString, rts::hash<AsciiString>,
	Rva00461360ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461360Value> >;

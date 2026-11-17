// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


enum BuildableStatus
{
	BUILDABLE_STATUS_PLACEHOLDER
};

namespace rts
{
	template <class T> struct hash;
	template <class T> struct equal_to;

	template <> struct hash<AsciiString>
	{
		unsigned int operator()(AsciiString value) const;
	};

	template <> struct equal_to<AsciiString>
	{
		int operator()(const AsciiString &left, const AsciiString &right) const;
	};
}

#include <hash_map>

typedef std::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>, rts::equal_to<AsciiString> > BuildableStatusMap;

// Use the separately verified retail provider (BuildableStatusHashResize.cpp); suppress this competing copy.
namespace _STL { template <> void hashtable<pair<const AsciiString, BuildableStatus>, AsciiString, rts::hash<AsciiString>, _Select1st<pair<const AsciiString, BuildableStatus> >, rts::equal_to<AsciiString>, allocator<pair<const AsciiString, BuildableStatus> > >::resize(unsigned int); }

template BuildableStatus &BuildableStatusMap::operator[](const AsciiString &key);

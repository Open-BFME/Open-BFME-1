// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME7: INI field parser at 0x002542F0 (151 B): the token becomes an
// AsciiString pushed onto the list<AsciiString> member at instance+0x34.
// STLport exceptions off (inline push_back: node from the static-lib node
// allocator then the placement copy under the EH state the string copy
// constructor still gets) with the allocator reached directly.
// The canonical AsciiString header inlines its wrappers around the matched
// StringBase<char> constructors (0x00888BC0, 0x00887B60) and releaseBuffer
// (0x00887940).

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "../../../Include/Common/INI/INI.h"

struct Rva002542F0Owner
{
	char m_unreconstructed[ 0x34 ];
	_STL::list<AsciiString> m_names;
};

class Rva002542F0
{
public:
	static void parseStringListEntry( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseStringListEntry@Rva002542F0@@SAXPAVINI@@PAX1PBX@Z
void Rva002542F0::parseStringListEntry( INI *ini, void *instance, void *, const void * )
{
	AsciiString name( ini->getNextToken() );
	((Rva002542F0Owner *)instance)->m_names.push_back( name );
}

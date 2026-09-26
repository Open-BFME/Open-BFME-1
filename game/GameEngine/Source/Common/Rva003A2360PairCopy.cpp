// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// The retail caller at 0x003A2460 is STLport _Construct over a pair whose
// copy body is 0x003A2360.  The key is known only to be a four-byte POD.  The
// second member's offsets and lifetimes are independently fixed by the body:
// forty raw bytes, ten non-trivial Coord3D objects, three raw words, a narrow
// StringBase object, and one trailing word.  Keep the owner neutral until a
// named caller identifies this map's semantic type.

#include <map>

#include "StringInline.h"
#include "coord3d.h"

struct Rva003A2360Element
{
	int m_key;
	int m_prefix[10];
	Coord3D m_points[10];
	int m_wordA;
	int m_wordB;
	int m_wordC;
	AsciiString m_name;
	int m_tail;
};

template void _STL::_Construct(Rva003A2360Element *, const Rva003A2360Element &);

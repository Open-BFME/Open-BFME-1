// cl: /DNDEBUG /MD /EHsc
// stlport

// Open-BFME: STLport GeometryRecord placement-copy helper, retail 0x000FD650.
//
// GeometryInfo's record vector proves the 0x10-byte element shape: three
// scalar words followed by AsciiString at +0x0c.  Retail performs a guarded
// placement copy of exactly one such element; the guard is the STLport
// placement-new null check retained by this compiler.

#include <memory>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char> and its copy is the
// trivial forwarder at 0x0005EE50, so a call site that copies one encodes the
// base body at 0x00887B60 directly. The delegation has to be visible here for
// this TU to encode the same call.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


struct GeometryRecord
{
	int m_first;
	int m_second;
	int m_third;
	AsciiString m_name;
};

// ??$_Construct@UGeometryRecord@@U1@@_STL@@YAXPAUGeometryRecord@@ABU1@@Z
template void _STL::_Construct(GeometryRecord *, const GeometryRecord &);

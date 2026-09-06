// ?_M_fill_insert@?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@QAEXPAUCoord3D@@IABU3@@Z
// partial score=0.4 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: STLport vector<Coord3D>::_M_fill_insert, retail 0x000B7AF0,
// 310 bytes. Fuzzy twin (ratio 0.938) of the vector<12-byte-record>::_M_fill_insert
// at 0x0076D560 (Rva0076D560VectorFillInsert.cpp, 306B) built with
// _STLP_NO_EXCEPTIONS -- this one keeps STLport exceptions on (the extra 4
// bytes are the try/catch EH-frame setup), and the element is the real
// Coord3D already used by the landed vector<Coord3D> erase/clear/resize
// bodies in this same source directory (BezierSegment.cpp,
// Coord3DVectorResizeThunk.cpp).

#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	float x;
	float y;
	float z;
};

template void _STL::vector<Coord3D, _STL::allocator<Coord3D> >::_M_fill_insert(
	Coord3D *, unsigned int, const Coord3D &);

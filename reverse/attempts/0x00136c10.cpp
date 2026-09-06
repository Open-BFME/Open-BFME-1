// ?d_00136c10@@YAXXZ
// partial score=0.55 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

// Open-BFME7: STLport vector<T>::operator= for the 0xEC (236-byte) element
// family, retail 0x00136C10, 258 bytes. Fuzzy twin of
// Rva003B6A40VectorAssign.cpp's vector<Rva003AC170Element>::operator=
// (271 B, element width 0xDC): same shape, element width 0xEC.
//
// The per-element copy call resolves to the already-matched, width-0xEC
// generic copier declared in Bfme5AllocateAndCopy.cpp
// (?bfmeCopyInto_00134BB0@@YAXPBUBfmeCopyElem_00134BB0@@0PAU1@PAI@Z,
// retail 0x00133F50, reached here through ILT 0x0002C14C) -- that helper
// takes (first, last, result, counter), the exception-safe
// uninitialized-copy shape, so this TU is built with ordinary (non
// -D_STLP_NO_EXCEPTIONS) STLport rather than the fuzzy twin's /D_STLP_NO_EXCEPTIONS.

#include <vector>

struct Elem236
{
	char m_body[0xEC];
	Elem236();
	Elem236(const Elem236 &other);
	~Elem236();
	Elem236 &operator=(const Elem236 &other);
};

template class _STL::vector<Elem236>;

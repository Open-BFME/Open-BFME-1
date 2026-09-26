// Retail 0x007E8640, 98 bytes: the bounded string copy the FESL setters at
// 0x00801470 and 0x008014A0 call. Two assertions and a strncpy, and the
// assertion text is what identifies it -- the stringised conditions still in
// the image are "src" at line 33 and "strlen(src) < dstSize" at line 34, both
// against
//
//     ..\..\source\include\fesl/internal/util.h
//
// so the second argument is called dstSize and the third src, which is the
// PADIPBD in the decoration. The reporter and its fourth vftable slot are the
// same ones U2FeslGameBrowserAsserts.cpp uses.
//
// The length test is inlined: MSVC's strlen intrinsic walks from src with a
// lea of src+1 to subtract, and the comparison against dstSize is jb because
// strlen is unsigned.

typedef unsigned int UnsignedInt;

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

extern Rva007EB810Diag *Rva007EB810Get();

extern "C" UnsignedInt __cdecl strlen(const char *string);
extern "C" char *__cdecl strncpy(char *dest, const char *source, UnsignedInt count);

#pragma intrinsic(strlen)

// ?Rva007E8640Copy@@YAXPADIPBD@Z
void Rva007E8640Copy(char *dst, UnsignedInt dstSize, const char *src)
{
	if (!src)
		Rva007EB810Get()->fail("src",
		                       "..\\..\\source\\include\\fesl/internal/util.h",
		                       33);

	if (!(strlen(src) < dstSize))
		Rva007EB810Get()->fail("strlen(src) < dstSize",
		                       "..\\..\\source\\include\\fesl/internal/util.h",
		                       34);

	strncpy(dst, src, dstSize);
}

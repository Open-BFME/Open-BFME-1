#ifndef D3DX_PNG_CONFIG_H
#define D3DX_PNG_CONFIG_H

#ifdef _PNG_H
#error D3DXPngConfig.h must precede png.h
#endif

#define PNG_CALLBACK __cdecl

// VC7.1 needs a compile-time type check that emits no runtime provider.
template<class A, class B> struct D3DXPngSameType { enum { value = 0 }; };
template<class A> struct D3DXPngSameType<A, A> { enum { value = 1 }; };

// These archive-disabled features change libpng's shared structs, not just its API.
#define PNG_NO_READ_USER_TRANSFORM 1
#define PNG_NO_WRITE_USER_TRANSFORM 1
#define PNG_NO_READ_bKGD 1
#define PNG_NO_READ_BACKGROUND 1
#define PNG_NO_CONSOLE_IO 1
#define PNG_NO_READ_cHRM 1
#define PNG_NO_READ_tEXt 1
#define PNG_NO_WRITE_tEXt 1
#define PNG_NO_READ_zTXt 1
#define PNG_NO_WRITE_zTXt 1
#define PNG_NO_READ_tIME 1
#define PNG_NO_WRITE_tIME 1
#define PNG_NO_READ_sBIT 1
#define PNG_NO_WRITE_sBIT 1
#define PNG_NO_WRITE_bKGD 1
#define PNG_NO_WRITE_cHRM 1
#define PNG_NO_READ_oFFs 1
#define PNG_NO_WRITE_oFFs 1
#define PNG_NO_READ_pHYs 1
#define PNG_NO_WRITE_pHYs 1
#define PNG_NO_READ_hIST 1
#define PNG_NO_WRITE_hIST 1
#define PNG_NO_READ_pCAL 1
#define PNG_NO_WRITE_pCAL 1
#define PNG_NO_PROGRESSIVE_READ 1
#define PNG_NO_STDIO 1
#define PNG_NO_READ_RGB_TO_GRAY 1

#endif

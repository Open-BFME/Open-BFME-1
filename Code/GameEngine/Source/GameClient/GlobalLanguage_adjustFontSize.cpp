// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// GlobalLanguageData::adjustFontSize, retail 0x00439000.
//
// The point size scaled by the display width over 1024 and floored. Two details
// the bytes settle:
//
//  - the floor is the CRT's double floor() reached through the import table at
//    0x013593B8, with the result narrowed back to Real, i.e. BaseType.h's
//    REAL_TO_INT_FLOOR spelled out (MSVC 7.1 does not fold floorf to that).
//  - the final narrowing is fast_float2long_round, BaseType.h's inline-asm
//    fld/fistp pair, NOT a C cast. That is the whole residue this row sat on:
//    every spelling of `(Int)` emits `fistp qword` plus a low-half load, with
//    or without /QIfist, because the C conversion is defined to be able to
//    outrange a dword. The x87 shape is only reachable from the helper the
//    original source actually calls.
//
// The point size also goes through its own Real local; multiplying the int
// directly folds to fimul and consumes the ratio, where retail keeps the ratio
// in st(1) and discards it with fstp st(0).

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor( double );

// BaseType.h, verbatim
__forceinline long fast_float2long_round( float f )
{
	long i;

	__asm {
		fld [f]
		fistp [i]
	}

	return i;
}

#define REAL_TO_INT_FLOOR(x)	(fast_float2long_round((Real)floor((double)(x))))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	// Read as a member, not through a getter: a getter spills the resolution to
	// a stack slot instead of fild-ing it in place.
	unsigned char m_unreconstructed_00[ 0x2C ];
	Int m_xResolution;									///< retail this+0x2C
};

extern GlobalData *TheGlobalData;								///< retail [0x012ED5C8]

class GlobalLanguageData
{
public:
	Int adjustFontSize( Int theFontSize );
};

Int GlobalLanguageData::adjustFontSize( Int theFontSize )
{
	Real ratio = TheGlobalData->m_xResolution / 1024.0f;
	Real size = theFontSize;
	return REAL_TO_INT_FLOOR( size * ratio );
}

// cl: -I game/Libraries/Source/WWVegas/WWLib -I game/Libraries/Source/WWVegas/WWMath -I game/Libraries/Source/WWVegas/WWDebug -I game/Libraries/Source/WWVegas/WWSaveLoad -I game/Libraries/Include
//
// Rotation overloads from
// game/Libraries/Source/WWVegas/WWMath/matrix3.h, emitted out of line.
// This TU groups Create_Z_Rotation_Matrix3 and Matrix3::Rotate_Y emitters.
//
// WHAT THE BYTES SHOW.  Both bodies take a hidden pointer in the first stack
// slot, write nine floats through it at +0x00..+0x20 and return with a plain
// `ret`: __cdecl returning a 36-byte class by value, i.e. a 3x3 matrix of
// Vector3 rows.  The nine values are, in order,
//
//     [0] = c   [1] = -s   [2] = 0
//     [3] = s   [4] = c    [5] = 0
//     [6] = 0   [7] = 0    [8] = 1
//
// which is a rotation about Z.  `Create_Z_Rotation_Matrix3(float s, float c)`
// in matrix3.h writes exactly those nine assignments in exactly that order into
// a local it then returns, and MSVC's named-return optimisation is what turns
// the local into the caller's buffer -- there is no copy in either body.
//
// THE SECOND OVERLOAD COMPUTES ITS OWN SINE AND COSINE: `fld` the angle,
// duplicate it, `fsin` one copy and `fcos` the other with an `fxch` between.
// That is `Create_Z_Rotation_Matrix3(sinf(rad), cosf(rad))` with the two-argument
// overload inlined into it, which is what matrix3.h's one-argument overload is.
// The ZERO STORES ARE HOISTED and the constant 1.0f is written last; that
// interleaving is the scheduler's, not the source's -- the source's own order
// survives in the float stores, which go down the x87 stack in the order the
// three rows are assigned.
//
// WHY THIS FILE EXISTS.  Both overloads are WWINLINE, which
// game/Libraries/Source/WWVegas/WWLib/always.h defines as __forceinline, so no
// ordinary caller leaves a body behind -- yet retail has both out of line at
// 0x0060C460 and 0x0060C4B0.  Taking the address of a __forceinline function is
// what makes MSVC emit the standalone copy, so that is what the two helpers
// below do.  They are the scaffold, not the claim: neither exists in retail.

#include "matrix3.h"

typedef Matrix3 ( *CreateZRotationFromSinCos )( float, float );
typedef Matrix3 ( *CreateZRotationFromRadians )( float );

// ?emitCreateZRotationFromSinCos@@YAP6A?AVMatrix3@@MM@ZXZ absent-from-retail
CreateZRotationFromSinCos emitCreateZRotationFromSinCos( void )
{
	return &Create_Z_Rotation_Matrix3;
}

// ?emitCreateZRotationFromRadians@@YAP6A?AVMatrix3@@M@ZXZ absent-from-retail
CreateZRotationFromRadians emitCreateZRotationFromRadians( void )
{
	return &Create_Z_Rotation_Matrix3;
}

// Address-taking emitters for Matrix3::Rotate_Y, for the same WWINLINE reason.
typedef void ( Matrix3::*RotateYFromRadians )( float );
typedef void ( Matrix3::*RotateYFromSinCos )( float, float );

// ?emitRotateYFromRadians@@YAP8Matrix3@@AEXM@ZXZ absent-from-retail
RotateYFromRadians emitRotateYFromRadians( void )
{
	return static_cast<RotateYFromRadians>( &Matrix3::Rotate_Y );
}

// ?emitRotateYFromSinCos@@YAP8Matrix3@@AEXMM@ZXZ absent-from-retail
RotateYFromSinCos emitRotateYFromSinCos( void )
{
	return static_cast<RotateYFromSinCos>( &Matrix3::Rotate_Y );
}

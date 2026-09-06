// cl: -I Code/Libraries/Source/WWVegas/WWLib -I Code/Libraries/Source/WWVegas/WWMath -I Code/Libraries/Source/WWVegas/WWDebug -I Code/Libraries/Source/WWVegas/WWSaveLoad -I Code/Libraries/Include
//
// The two `Matrix3::Rotate_Y` overloads from
// Code/Libraries/Source/WWVegas/WWMath/matrix3.h, emitted out of line.
// Same scaffold as U4CreateZRotationMatrix3.cpp: both overloads are WWINLINE
// (== __forceinline via always.h), so taking their address is what makes
// MSVC emit a standalone body. Neither helper below exists in retail.

#include "matrix3.h"

typedef void ( Matrix3::*U4RotYFromRadians )( float );
typedef void ( Matrix3::*U4RotYFromSinCos )( float, float );

// ?u4RotYFromRadians@@YAP8Matrix3@@AEXM@ZXZ absent-from-retail
U4RotYFromRadians u4RotYFromRadians( void )
{
	return static_cast<U4RotYFromRadians>( &Matrix3::Rotate_Y );
}

// ?u4RotYFromSinCos@@YAP8Matrix3@@AEXMM@ZXZ absent-from-retail
U4RotYFromSinCos u4RotYFromSinCos( void )
{
	return static_cast<U4RotYFromSinCos>( &Matrix3::Rotate_Y );
}

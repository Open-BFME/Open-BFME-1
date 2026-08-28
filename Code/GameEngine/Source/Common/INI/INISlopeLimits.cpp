// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception

// FILE: INISlopeLimits.cpp ///////////////////////////////////////////////////
//
// The SlopeLimits block, retail 0x003D64F0. BFME-only; the INI block table in
// .data names it.
//
// No field table and no subsystem: the block is two positional tokens, each an
// angle in degrees, and each is stored as its TANGENT - retail multiplies by
// 0x3C8EFA35 (PI/180) and takes fptan, which is what tan() compiles to under
// /Oi. A slope limit compared against a height delta over a run wants the
// tangent, not the angle, which is why the conversion happens once here at
// parse time rather than at every test.
//
// The pair lives at 0x012F1064 and 0x012F1068 and nothing in the image names
// it; the array is spelled for the two values this parser writes.
//
// The scan is not INI::scanReal. That one runs the token through
// preprocessMacro first and reports the substituted text; retail sscanfs the
// raw token here and reports it unchanged, so the scan is spelled out inline
// rather than borrowed.
//
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <math.h>

#include "Common/INIException.h"

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
};

// PI/180 as a float: the 0x3C8EFA35 retail multiplies by.
static const Real RADS_PER_DEGREE = 0.0174532925199432955f;

extern Real TheSlopeLimits[ 2 ];			// 0x012F1064

// ?parseSlopeLimits@@YAXPAVINI@@@Z
void parseSlopeLimits( INI *ini )
{
	// Written as a signed index, not a pointer walk: retail closes the loop with
	// jl, and MSVC only keeps the signed test after strength-reducing the index
	// into the pointer it actually increments. A `Real *' loop compares unsigned
	// and closes with jb.
	for( int i = 0; i < 2; ++i )
	{
		const char *token = ini->getNextToken();

		Real degrees;
		if( sscanf( token, "%f", &degrees ) != 1 )
			throw INIException( 3, "Expected floating point value in '%s'", token );

		TheSlopeLimits[ i ] = tan( degrees * RADS_PER_DEGREE );
	}
}

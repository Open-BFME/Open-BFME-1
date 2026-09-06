// ?Rva000697B0ScanTangentAngle@@YAMPBD@Z
// partial score=0.95 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: the function-curve tangent scanner at 0x000697B0 (136 B): the
// token is read through INI::scanReal as an angle in degrees which must lie
// in (-89.9 89.9) (INIException(3 ...) either side with the two messages at
// VA 0x010759B0 and 0x01075958) and the tangent of the angle in radians is
// returned (the degree-to-radian constant at VA 0x01075954 then the inline
// fptan).  Address-derived name.

#include <math.h>
#pragma intrinsic( tan )

typedef int Int;
typedef float Real;

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	static Real scanReal( const char *token );
};

extern const Real Rva000697B0MaxAngle;
extern const Real Rva000697B0MinAngle;
extern const Real Rva000697B0DegreesToRadians;

// ?Rva000697B0ScanTangentAngle@@YAMPBD@Z
Real Rva000697B0ScanTangentAngle( const char *token )
{
	Real angle = INI::scanReal( token );
	if( angle > Rva000697B0MaxAngle )
		throw INIException( 3, "Function curve tangent angle value must be less than 89.9 degrees" );
	if( angle < Rva000697B0MinAngle )
		throw INIException( 3, "Function curve tangent angle value must be greater than -89.9 degrees" );
	return (Real)tan( Rva000697B0DegreesToRadians * angle );
}

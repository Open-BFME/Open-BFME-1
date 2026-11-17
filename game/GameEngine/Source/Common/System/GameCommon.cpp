// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// stlport
#include "PreRTS.h"
#include "Common/GameCommon.h"

// GameCommon.cpp owns this enum table upstream. Retail VA 0x012A9FB4
// has the same four names and null terminator; each keyword owns its
// independently verified retail storage rather than a compiler literal pin.
extern const char g_Va01087B00[] = "REGULAR";
extern const char g_Va01073AA0[] = "VETERAN";
extern const char g_Va01073A98[] = "ELITE";
extern const char g_Va01087AF8[] = "HEROIC";

const char *TheVeterancyNames[] =
{
	g_Va01087B00,
	g_Va01073AA0,
	g_Va01073A98,
	g_Va01087AF8,
	NULL
};

//-------------------------------------------------------------------------------------------------
Real normalizeAngle(Real angle)
{
	while (angle > PI)
		angle -= 2*PI;

	while (angle <= -PI)
		angle += 2*PI;

	return angle;
}

// BFME 1 matched frame-conversion helpers reference this four-byte datum
// at VA 0x012A86A8. Retail bytes CD CC 4C 3E establish 0.2f.
// BFME 2 aa505f34 INI_parseVelocityReal.cpp uses its own 0.2 global;
// its address and spelling are not transferred to BFME 1.
extern const float g_Va012A86A8 = 0.2f;

// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME W3DTruckDrawModuleData destructor.  The matched module-data factory at
// 0x006BF4F0 allocates 0x1C4 bytes and calls the constructor at 0x0077F830.
// Retail's destructor at 0x0077F920 tears down the 21 consecutive strings at
// +0x15C..+0x1AC in reverse declaration order, then destroys the +0 base.

#include "ascii_string.h"

class S4Base0077C1F0
{
public:
	virtual ~S4Base0077C1F0();

private:
	char m_fields[ 0x158 ];
};

class W3DTruckDrawModuleData : public S4Base0077C1F0
{
public:
	virtual ~W3DTruckDrawModuleData();

private:
	AsciiString m_dustEffectName;
	AsciiString m_dirtEffectName;
	AsciiString m_powerslideEffectName;
	AsciiString m_frontLeftTireBoneName;
	AsciiString m_frontRightTireBoneName;
	AsciiString m_rearLeftTireBoneName;
	AsciiString m_rearRightTireBoneName;
	AsciiString m_midFrontLeftTireBoneName;
	AsciiString m_midFrontRightTireBoneName;
	AsciiString m_midRearLeftTireBoneName;
	AsciiString m_midRearRightTireBoneName;
	AsciiString m_midMidLeftTireBoneName;
	AsciiString m_midMidRightTireBoneName;
	AsciiString m_string13;
	AsciiString m_string14;
	AsciiString m_string15;
	AsciiString m_string16;
	AsciiString m_string17;
	AsciiString m_string18;
	AsciiString m_cabBoneName;
	AsciiString m_trailerBoneName;
	char m_tail[ 0x14 ];
};

W3DTruckDrawModuleData::~W3DTruckDrawModuleData()
{
}

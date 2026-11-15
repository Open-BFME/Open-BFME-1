// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AsciiString getAttackFilename();
	AsciiString getFilename();
	AsciiString getDecayFilename();
};

class RvaAudioEventFilenameForPortion
{
public:
	AsciiString getFilenameForPlayPortion();

private:
	unsigned char m_pad00[0x60];
	int m_portionToPlay;
};

AsciiString RvaAudioEventFilenameForPortion::getFilenameForPlayPortion()
{
	switch (m_portionToPlay)
	{
	case 0:
		return ((AudioEventRTS *)this)->getAttackFilename();
	case 1:
		return ((AudioEventRTS *)this)->getFilename();
	case 2:
		return ((AudioEventRTS *)this)->getDecayFilename();
	default:
		return AsciiString::TheEmptyString;
	}
}

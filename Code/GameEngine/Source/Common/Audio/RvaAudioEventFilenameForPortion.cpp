// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	static const AsciiString TheEmptyString;

private:
	const char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
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

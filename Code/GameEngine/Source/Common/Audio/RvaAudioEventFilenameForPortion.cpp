// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();
	static const AsciiString TheEmptyString;

private:
	const char *m_data;
};

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

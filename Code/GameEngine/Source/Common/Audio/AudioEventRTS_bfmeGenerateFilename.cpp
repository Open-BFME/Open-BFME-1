// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// AudioManager::getAudioLengthMS and isMusicAlreadyLoaded call this body;
// their Zero Hour twins call generateFilename at those sites. BFME split
// delay + lazy filename off the 400-byte generateFilename at 0x000B3970.
// ILT 0x00046A33 is already pinned as AudioEventRTS::bfmeGenerateFilename.

typedef unsigned char Byte;

float __cdecl GetGameAudioRandomValueReal(float low, float high, char *file, int line);

class AudioEventInfoDelayView
{
public:
	Byte m_pad00[0x28];
	int m_delayMin;
	int m_delayMax;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	void bfmeGenerateFilename();
	void generateFilename();

private:
	Byte m_pad00[0x08];
	AudioEventInfoDelayView *m_eventInfo;
	Byte m_pad0C[0x36];
	Byte m_isLogicalAudio;
	Byte m_pad43[0x03];
	Byte m_filenameDirty;
	Byte m_pad47;
	Byte m_shouldRegenerateFilename;
	Byte m_pad49[0x0B];
	float m_delay;
};

void AudioEventRTS::bfmeGenerateFilename()
{
	if (m_eventInfo == 0)
		return;

	int maximumDelay = m_eventInfo->m_delayMax;
	int minimumDelay = m_eventInfo->m_delayMin;
	m_delay = GetGameAudioRandomValueReal(
		(float)minimumDelay,
		(float)maximumDelay,
		"F:\\bfme\\Code\\gameengine\\Source\\Common\\Audio\\AudioEventRTS.cpp",
		490);

	if (m_shouldRegenerateFilename || m_isLogicalAudio)
	{
		m_filenameDirty = 1;
		m_shouldRegenerateFilename = 0;
		if (m_isLogicalAudio)
			generateFilename();
	}
}

// cl: /DNDEBUG /MD /EHsc
// readable body of ?isPositionalAudio@AudioEventRTS@@: Code/GameEngine/Source/Common/Audio/AudioEventRTS.cpp

// Open-BFME5: AudioEventRTS::isPositionalAudio, retail RVA 0x000B28F0.
// The BFME AudioEventRTS layout places AudioEventInfo::m_type at +0x38,
// the owner id at +0x2C, and the owner type at +0x30.  The caller-side
// AudioEventRTS declarations in AudioEventRTS.cpp and GameSounds.cpp provide
// the identity; this TU keeps the recovered layout local to this body.
struct AudioEventInfoSlice
{
	char m_pad[0x38];
	unsigned char m_type;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	bool isPositionalAudio() const;

private:
	char m_pad0[8];
	const AudioEventInfoSlice *m_eventInfo;
	char m_pad1[0x20];
	unsigned int m_ownerID;
	int m_ownerType;
};

bool AudioEventRTS::isPositionalAudio() const
{
	if (m_eventInfo != 0 && (m_eventInfo->m_type & 2) == 0)
		goto not_positional;

	switch (m_ownerType)
	{
		case 0:
			return true;
		case 1:
		case 2:
		case 5:
			if (m_ownerID == 0)
				goto not_positional;
			return true;
		default:
			goto not_positional;
	}

not_positional:
	return false;
}

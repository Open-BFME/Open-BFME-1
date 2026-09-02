// ?isPositionalAudio@AudioEventRTS@@QBE_NXZ
// partial score=0.99 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS::isPositionalAudio, retail 0x000B28F0.
// BFME adds a sixth owner state.  Positional owners are always positional;
// drawable, object, and the sixth state require a nonzero owner id.

struct AudioEventInfoSlice
{
	char m_pad[0x38];
	unsigned char m_type;
};

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

positional:
	return true;
not_positional:
	return false;
}

void AudioEventRTSIsPositionalAudioBoundary()
{
}

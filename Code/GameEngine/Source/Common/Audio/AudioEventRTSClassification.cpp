// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS sound-class mapper, retail 0x000B2950, 68B.
// Reads AudioEventInfo +0x84 (0..4) and maps to ST_* style flags.
// Case 2 calls isPositionalAudio (ILT 0x0000F380 -> 0x000B28F0).

struct AudioEventInfo
{
	unsigned char m_pad00[0x38];
	unsigned char m_type;
	unsigned char m_pad39[0x4B];
	unsigned int m_soundClass;
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	__declspec(noinline) bool isPositionalAudio(void) const;

private:
	void *m_vftable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
	char m_pad0C[0x20];
	unsigned int m_ownerID;
	int m_ownerType;
};

// ?getSoundClass@AudioEventRTS@@QBEIXZ
unsigned int AudioEventRTS::getSoundClass(void) const
{
	if (!m_eventInfo)
		return 0;

	switch (m_eventInfo->m_soundClass)
	{
	case 0:
		return 1;
	case 3:
		return 16;
	case 1:
		return 8;
	case 4:
		return 2;
	case 2:
		return isPositionalAudio() ? 4 : 2;
	default:
		return 0;
	}
}

// Retail RVA 0x000B28F0; the class mapper above calls this through its ILT.
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

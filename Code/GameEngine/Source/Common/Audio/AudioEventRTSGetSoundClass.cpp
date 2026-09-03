// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AudioEventRTS sound-class mapper, retail 0x000B2950, 68B.
// Reads AudioEventInfo +0x84 (0..4) and maps to ST_* style flags.
// Case 2 calls isPositionalAudio (ILT 0x0000F380 -> 0x000B28F0).

struct AudioEventInfo
{
	unsigned char m_pad[0x84];
	unsigned int m_soundClass;
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;
	bool isPositionalAudio(void) const;

private:
	void *m_vftable;
	void *m_filenameToLoad;
	const AudioEventInfo *m_eventInfo;
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

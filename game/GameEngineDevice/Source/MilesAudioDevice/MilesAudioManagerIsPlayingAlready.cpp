// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

#include "ascii_string.h"

template <> inline int StringBase<char>::compare(const StringBase<char> &str) const
{
	int otherLength = str.m_data ? str.m_data->length : 0;
	const char *otherData = str.m_data ? str.m_data->data : (const char *)"";
	int length = m_data ? m_data->length : 0;
	const char *data = m_data ? m_data->data : (const char *)"";
	int result = memcmp(data, otherData, length < otherLength ? length : otherLength);
	return result ? result : length - otherLength;
}

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;

	const AsciiString &getEventName() const
	{
		return *(const AsciiString *)((const char *)this + 0x14);
	}
};

struct PlayingAudio
{
	unsigned char prefix[0x14];
	AudioEventRTS *audioEventRTS;
};

typedef _STL::list<PlayingAudio *> PlayingAudioList;

class MilesAudioManager
{
public:
	bool isPlayingAlready(AudioEventRTS *event) const;

private:
	unsigned char prefix[0x9c8];
	PlayingAudioList playingSounds;
	PlayingAudioList playing3DSounds;
};

// ?isPlayingAlready@MilesAudioManager@@QBE_NPAVAudioEventRTS@@@Z
bool MilesAudioManager::isPlayingAlready(AudioEventRTS *event) const
{
	PlayingAudioList::const_iterator it;
	if (!event->isPositionalAudio())
	{
		for (it = playingSounds.begin(); it != playingSounds.end(); ++it)
		{
			if ((*it)->audioEventRTS->getEventName().StringBase<char>::compare(event->getEventName()) == 0)
				return true;
		}
	}
	else
	{
		for (it = playing3DSounds.begin(); it != playing3DSounds.end(); ++it)
		{
			if ((*it)->audioEventRTS->getEventName().StringBase<char>::compare(event->getEventName()) == 0)
				return true;
		}
	}

	return false;
}

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
			if ((*it)->audioEventRTS->getEventName().compare(event->getEventName()) == 0)
				return true;
		}
	}
	else
	{
		for (it = playing3DSounds.begin(); it != playing3DSounds.end(); ++it)
		{
			if ((*it)->audioEventRTS->getEventName().compare(event->getEventName()) == 0)
				return true;
		}
	}

	return false;
}

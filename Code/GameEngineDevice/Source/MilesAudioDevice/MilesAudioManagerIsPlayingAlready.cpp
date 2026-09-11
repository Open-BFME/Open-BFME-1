// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
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

class AsciiString
{
public:
	int compare(const AsciiString &other) const
	{
		const AsciiString *self = this;
		const AsciiString *that = &other;
		int thatLength = that->m_data ? that->m_data->length : 0;
		const char *thatText = that->m_data ? &that->m_data->data[0] : (const char *)"";
		int selfLength = self->m_data ? self->m_data->length : 0;
		const char *selfText = self->m_data ? &self->m_data->data[0] : (const char *)"";
		int count = selfLength < thatLength ? selfLength : thatLength;
		int result = memcmp(selfText, thatText, count);
		if (result != 0)
			return result;
		return selfLength - thatLength;
	}

	BfmeAsciiStringData *m_data;
};

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

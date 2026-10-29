// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?method@Rva006B2110@@QBE_NPAVAudioEventRTS@@@Z
//
// Retail 0x006B2110 (228 B, ret 4 at +0xE1): the lower-priority test the
// matched SoundManager::canPlayNow (0x006B64A0) reaches through ILT 0x0001D1B0
// with one AudioEventRTS argument and a byte result. It walks the 2D list at
// +0x9C8 or the 3D list at +0x9CC (isPositionalAudio, as in the matched
// MilesAudioManager::isPlayingAlready) and returns true for the first playing
// sound whose event priority is lower, or equal with a lower faded volume.
// The faded volume is the 0x006AE150 compute() result times the clamped
// 1 - fadeFrame / fadeAudioFrames factor of the matched sibling 0x006B1A00.
// Zero Hour's MilesAudioManager::isPlayingLowerPriority compares priorities
// only and the ILT order contradicts that decorated name here, so the class
// keeps the address-derived name canPlayNow already declares.
//
// Shape notes: the inline const-reference helper reproduces retail's
// `mov edx,ecx` element copy (sibling 0x006B1FC0 has it too). Each rank is
// one {priority, volume} record as in 0x006B1FC0 findLowestPrioritySound:
// the priority word stays in a register, the volume in the record's upper
// word (retail sub esp,8 with the volume at [esp+0x14]).

#include <list>

typedef float Real;

#define Rva006B2110One (1.0f)
#define Rva006B2110Zero (0.0f)

struct AudioEventInfo
{
	char m_prefix[0x34];
	int m_priority;
};

class AudioEventRTS
{
public:
	bool isPositionalAudio() const;

	unsigned char m_prefix[8];
	AudioEventInfo *m_info;
};

struct PlayingAudio
{
	unsigned char m_prefix[0x14];
	AudioEventRTS *m_event;
	char m_pad18[0x10];
	Real m_fadeFrame;
};

struct PlayingAudioRef
{
	PlayingAudio *m_audio;
	PlayingAudio *operator->(void) const
	{
		return m_audio;
	}
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;

struct Rva006B2110AudioSettings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

struct Rva006B2110Rank
{
	int m_priority;
	Real m_volume;
};

class Rva006AE150Argument;
class Rva006AE150Owner
{
public:
	virtual void rva006AE150UnusedVirtual(void) {}
	Real compute(Rva006AE150Argument *argument, int apply);

private:
	char m_basePad[8];
};

class Rva006B2110 : public Rva006AE150Owner
{
public:
	bool method(AudioEventRTS *event) const;
	Real getFadedVolume(const PlayingAudioRef &playing)
	{
		AudioEventRTS *event = playing->m_event;
		Real volume = compute((Rva006AE150Argument *)event, 1);
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)m_audioSettings->m_fadeAudioFrames);
		if (fade < Rva006B2110Zero)
			fade = Rva006B2110Zero;
		else if (fade > Rva006B2110One)
			fade = Rva006B2110One;
		return volume * fade;
	}

private:
	Rva006B2110AudioSettings *m_audioSettings;
	char m_pad10[0x9b8];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
};

bool Rva006B2110::method(AudioEventRTS *event) const
{
	Rva006B2110 *self = const_cast<Rva006B2110 *>(this);
	Rva006B2110Rank rank;
	rank.m_priority = event->m_info->m_priority;
	rank.m_volume = self->compute((Rva006AE150Argument *)event, 1);

	const PlayingAudioList *list;
	if (event->isPositionalAudio())
		list = &m_playing3DSounds;
	else
		list = &m_playingSounds;

	for (PlayingAudioList::const_iterator it = list->begin(); it != list->end(); ++it)
	{
		AudioEventRTS *other = (*it)->m_event;
		Rva006B2110Rank otherRank;
		otherRank.m_volume = self->getFadedVolume(*it);
		otherRank.m_priority = other->m_info->m_priority;
		if (otherRank.m_priority < rank.m_priority)
			return true;
		if (otherRank.m_priority > rank.m_priority)
			continue;
		if (otherRank.m_volume < rank.m_volume)
			return true;
	}
	return false;
}

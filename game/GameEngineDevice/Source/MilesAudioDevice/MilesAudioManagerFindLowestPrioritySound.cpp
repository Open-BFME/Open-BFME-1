// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?findLowestPrioritySound@MilesAudioManager@@AAEPAVAudioEventRTS@@PAV2@@Z
//
// Retail 0x006B1FC0 (258 B, ret 4 at +0xFF): reached through ILT 0x000280F6
// from the matched MilesAudioManagerStopChain unit, whose call site already
// documents it as Zero Hour's findLowestPrioritySound; ilt_oracle CONFIRMS
// this private non-const decoration. Starting from the event's own priority
// and volume (0x006AE150 compute()), it returns the playing event on the 2D
// (+0x9C8) or 3D (+0x9CC) list with the lowest priority, ties broken by the
// lower faded volume (compute() times the clamped 1 - fadeFrame /
// fadeAudioFrames factor of the matched 0x006B1A00), or null.
//
// BFME ranks by priority and volume together, unlike Zero Hour's priority-only
// scan. Retail keeps each rank as one {priority, volume} record: the priority
// word stays in a register, the volume in the record's upper word, and the
// winning rank is copied as a whole (mov ebp,ecx plus the volume dword).
#include <list>

typedef float Real;

#define Rva006B1FC0One (1.0f)
#define Rva006B1FC0Zero (0.0f)

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

struct Rva006B1FC0AudioSettings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

struct Rva006B1FC0Rank
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

class MilesAudioManager : public Rva006AE150Owner
{
private:
	AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event);
	Real getFadedVolume(const PlayingAudioRef &playing)
	{
		AudioEventRTS *event = playing->m_event;
		Real volume = compute((Rva006AE150Argument *)event, 1);
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)m_audioSettings->m_fadeAudioFrames);
		if (fade < Rva006B1FC0Zero)
			fade = Rva006B1FC0Zero;
		else if (fade > Rva006B1FC0One)
			fade = Rva006B1FC0One;
		return volume * fade;
	}

private:
	Rva006B1FC0AudioSettings *m_audioSettings;
	char m_pad10[0x9b8];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
};

AudioEventRTS *MilesAudioManager::findLowestPrioritySound(AudioEventRTS *event)
{
	Rva006B1FC0Rank lowestRank;
	lowestRank.m_priority = event->m_info->m_priority;
	AudioEventRTS *lowest = 0;
	lowestRank.m_volume = compute((Rva006AE150Argument *)event, 1);

	const PlayingAudioList *list;
	if (event->isPositionalAudio())
		list = &m_playing3DSounds;
	else
		list = &m_playingSounds;

	for (PlayingAudioList::const_iterator it = list->begin(); it != list->end(); ++it)
	{
		AudioEventRTS *other = (*it)->m_event;
		Rva006B1FC0Rank rank;
		rank.m_volume = getFadedVolume(*it);
		rank.m_priority = other->m_info->m_priority;
		if (rank.m_priority < lowestRank.m_priority ||
			(rank.m_priority <= lowestRank.m_priority && rank.m_volume < lowestRank.m_volume))
		{
			lowest = other;
			lowestRank = rank;
		}
	}
	return lowest;
}

// ?isPlayingLowerPriority@Rva006B2110Owner@@QAE_NPAURva006B2110AudioEvent@@@Z
// partial score=0.84 date=2026-09-03
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// Audio preemption tests from the BFME Miles audio manager.

#define _STLP_NO_EXCEPTIONS 1
#include <list>

struct Rva006B2110AudioEventInfo
{
	char m_pad00[0x28];
	float m_volume;
	char m_pad2c[0x08];
	int m_priority;
};

struct Rva006B2110AudioEvent
{
	char m_pad00[0x08];
	Rva006B2110AudioEventInfo *m_info;
	char m_pad0c[0x1c];
	bool __declspec(nothrow) isPositionalAudio() const;
};

struct Rva006B2110PlayingAudio
{
	char m_pad00[0x14];
	Rva006B2110AudioEvent *m_event;
	char m_pad18[0x10];
	float m_volume;
};

struct Rva006B2110ListNode
{
	Rva006B2110ListNode *m_next;
	Rva006B2110ListNode *m_prev;
	Rva006B2110PlayingAudio *m_value;
};

struct Rva006B2110ListView
{
	Rva006B2110ListNode *m_node;
};

struct Rva006B2110VolumeConfig
{
	char m_pad00[0x3c];
	int m_divisor;
};

enum Rva006B2110AudioPriority
{
	Rva006B2110PriorityLowest = 0,
	Rva006B2110PriorityNormal = 1,
	Rva006B2110PriorityHigh = 2,
	Rva006B2110PriorityCritical = 3
};

extern void j_0002918b();
extern void j_0000f380();

static __forceinline float rva006B2110Clamp(float value)
{
	if (value < 0.0f)
		value = 0.0f;
	else if (value > 1.0f)
		value = 1.0f;
	return value;
}

static __forceinline float rva006B2110Multiply(float left, float right)
{
	return left * right;
}

class Rva006B2110Owner
{
public:
	float __declspec(nothrow) getEffectiveVolume(Rva006B2110AudioEvent *event, int scale);
	Rva006B2110AudioEvent *findLowestPrioritySound(Rva006B2110AudioEvent *event);
	bool isPlayingLowerPriority(Rva006B2110AudioEvent *event);
	char m_pad00[0x0c];
	Rva006B2110VolumeConfig *m_volumeConfig;
	char m_pad10[0x9b8];
	_STL::list<Rva006B2110PlayingAudio *> m_playingSounds;
	_STL::list<Rva006B2110PlayingAudio *> m_playing3DSounds;
};

Rva006B2110AudioEvent *Rva006B2110Owner::findLowestPrioritySound(
	Rva006B2110AudioEvent *event)
{
	Rva006B2110AudioPriority priority =
		(Rva006B2110AudioPriority)event->m_info->m_priority;
	register Rva006B2110AudioEvent *lowest = 0;
	register Rva006B2110AudioPriority lowestPriority = priority;
	float lowestVolume = getEffectiveVolume(event, 1);
	float candidateVolume = 0.0f;

	_STL::list<Rva006B2110PlayingAudio *> *playing;
	if (event->isPositionalAudio())
		playing = &m_playing3DSounds;
	else
		playing = &m_playingSounds;

	_STL::list<Rva006B2110PlayingAudio *>::const_iterator it;
	for (it = playing->begin(); it != playing->end(); ++it)
	{
		const Rva006B2110PlayingAudio *playingAudio = *it;
		Rva006B2110AudioEvent *candidate = playingAudio->m_event;
		candidateVolume = getEffectiveVolume(playingAudio->m_event, 1);
		float attenuation = 1.0f -
			playingAudio->m_volume / (float)m_volumeConfig->m_divisor;
		if (attenuation < 0.0f)
			attenuation = 0.0f;
		else if (attenuation > 1.0f)
			attenuation = 1.0f;
		candidateVolume = attenuation * candidateVolume;
		Rva006B2110AudioPriority candidatePriority =
			(Rva006B2110AudioPriority)candidate->m_info->m_priority;
        if (candidatePriority < lowestPriority ||
            (candidatePriority == lowestPriority && candidateVolume < lowestVolume))
		{
			lowest = candidate;
			lowestPriority = candidatePriority;
			lowestVolume = candidateVolume;
		}
	}
	return lowest;
}

bool Rva006B2110Owner::isPlayingLowerPriority(
	Rva006B2110AudioEvent *event)
{
	register Rva006B2110Owner *self = this;
	register int priority = event->m_info->m_priority;
	typedef float (Rva006B2110Owner::*Effective)(Rva006B2110AudioEvent *, int);
	union
	{
		void (__cdecl *freeFunction)();
		Effective memberFunction;
	} initialEffective;
	initialEffective.freeFunction = ::j_0002918b;
	float volume = (self->*initialEffective.memberFunction)(event, 1);

	_STL::list<Rva006B2110PlayingAudio *> *playing;
	typedef bool (Rva006B2110AudioEvent::*IsPositional)(void) const;
	union
	{
		void (__cdecl *freeFunction)();
		IsPositional memberFunction;
	} positional;
	positional.freeFunction = ::j_0000f380;
	if ((event->*positional.memberFunction)())
		playing = &self->m_playing3DSounds;
	else
		playing = &self->m_playingSounds;

	_STL::list<Rva006B2110PlayingAudio *>::iterator it;
	for (it = playing->begin(); it != playing->end(); ++it)
	{
		Rva006B2110PlayingAudio *playingAudio = *it;
		Rva006B2110AudioEvent *candidate = playingAudio->m_event;
		union
		{
			void (__cdecl *freeFunction)();
			Effective memberFunction;
		} candidateEffective;
		candidateEffective.freeFunction = ::j_0002918b;
		float candidateVolume = rva006B2110Multiply(
			(self->*candidateEffective.memberFunction)(playingAudio->m_event, 1),
			rva006B2110Clamp(1.0f -
			playingAudio->m_volume /
			(float)self->m_volumeConfig->m_divisor));
		int candidatePriority = candidate->m_info->m_priority;
		if (candidatePriority < priority)
			return true;
		if (candidatePriority > priority)
			continue;
		if (candidateVolume >= volume)
			return true;
	}
	return false;
}

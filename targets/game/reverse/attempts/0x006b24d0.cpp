// ?rva006B24D0@MilesAudioManager@@QAEXABVAsciiString@@MH@Z
// partial score=0.9977 date=2026-10-05
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
//
// Retail 0x006B24D0 (1772 B, ret 0xC). Reached through ILT 0x00023D21 from
// Rva006B4310Owner::update006B4310, Rva006B43E0Owner::update006B43E0 and
// Rva006B44A0Owner::clear006B44A0, which pass (const AsciiString &, float,
// int).  The owner is the BFME MilesAudioManager (mutex +0x95C, playing lists
// +0x9C8/+0x9CC/+0x9D0, handle table +0xB44, settings +0xC; see
// MilesAudioManagerStopAudio.cpp and MilesAudioManagerUpdateFadeVolume006B1A00.cpp).
// Zero Hour's adjustVolumeOfPlayingAudio(name, volume) is the nearest
// relative, but this body takes a category, never reads the float, and also
// walks two per-category queues and a per-category event vector, so the
// identity stays address-derived.

#include <list>
#include <deque>
#include <vector>
#include "ascii_string.h"
enum TimeOfDay { TIME_OF_DAY_INVALID = 0, TIME_OF_DAY_FIRST = 1, TIME_OF_DAY_MORNING = TIME_OF_DAY_FIRST, TIME_OF_DAY_AFTERNOON, TIME_OF_DAY_EVENING, TIME_OF_DAY_NIGHT, TIME_OF_DAY_COUNT };

typedef float Real;
typedef void *HSAMPLE;
typedef void *H3DSAMPLE;
typedef void *HSTREAM;

extern "C" __declspec(dllimport) void __stdcall _AIL_sample_volume_pan(
	HSAMPLE sample, Real *volume, Real *pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_sample_volume_pan(
	HSAMPLE sample, Real volume, Real pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_3D_sample_volume(
	H3DSAMPLE sample, Real volume);
extern "C" __declspec(dllimport) void __stdcall _AIL_stream_volume_pan(
	HSTREAM stream, Real *volume, Real *pan);
extern "C" __declspec(dllimport) void __stdcall _AIL_set_stream_volume_pan(
	HSTREAM stream, Real volume, Real pan);
__forceinline void queryStreamPan(Real *pan, HSTREAM stream)
{
	_AIL_stream_volume_pan(stream, 0, pan);
}

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

#define Rva006B24D0One (*(const Real *)0x01075334)
#define Rva006B24D0Zero (*(const Real *)0x01075350)

class Rva006B24D0EventInfo
{
public:
	virtual void slot00();
	virtual const AsciiString &getName() const;

	char m_pad004[0x84 - 4];
	int m_type84;
};

class AudioEventRTS
{
public:
	char m_pad000[8];
	Rva006B24D0EventInfo *m_eventInfo;
	char m_pad00c[0x28 - 0xc];
	TimeOfDay m_timeOfDay;
	TimeOfDay getTimeOfDay() const { return m_timeOfDay; }
	bool isTimeOfDay(int value) const { return m_timeOfDay == value; }
	char m_pad02c[0x78 - 0x2c];
};

class RefCountedPlayingAudio
{
public:
	virtual ~RefCountedPlayingAudio();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
	}

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

private:
	long m_refCount;
};

class Rva006B24D0AudioEventRef
{
public:
	AudioEventRTS *operator->() const { return ptr; }
	AudioEventRTS *ptr;
};

class PlayingAudio : public RefCountedPlayingAudio
{
public:
	void *m_milesHandle;
	int m_type;
	int m_status;
	Rva006B24D0AudioEventRef m_audioEventRTS;
	void *m_file;
	char m_pad1c[0x0c];
	Real m_fadeFrame;
};

class PlayingAudioRef
{
public:
	PlayingAudioRef(void) : m_ptr(0) {}

	~PlayingAudioRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	PlayingAudioRef &operator=(const PlayingAudioRef &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				other.m_ptr->Add_Ref();
			if (m_ptr)
				m_ptr->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	operator PlayingAudio *(void) const { return m_ptr; }
	PlayingAudio *operator->(void) const { return m_ptr; }

private:
	PlayingAudio *m_ptr;
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;
typedef _STL::deque<PlayingAudioRef> PlayingAudioQueue;

// The name test reads the header inline: a non-empty selector only.
struct Rva006B24D0NameHeader
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
};

class Rva006B24D0Name
{
public:
	bool isSet() const { return m_data && m_data->m_length != 0; }

private:
	Rva006B24D0NameHeader *m_data;
};

struct Rva006B24D0Settings
{
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

struct Rva006B24D0Slot
{
	char m_pad0[4];
	void *m_slot;
	char m_pad8[0x38];
};

typedef _STL::vector<AudioEventRTS> Rva006B24D0EventVector;

class Rva006AE150Argument;
class Rva006AE150Owner
{
public:
	virtual void rva006AE150UnusedVirtual(void) {}
	Real compute(Rva006AE150Argument *argument, int apply);

private:
	char m_basePad[8];
};

class Rva006AD590Owner
{
public:
	void bfmeAdjustPriorityAndVolume(AudioEventRTS *event);
};

class MilesAudioManager : public Rva006AE150Owner
{
public:
	void rva006B24D0(const AsciiString &eventName, Real unused, int category);

private:
	__forceinline void adjust(AudioEventRTS *event)
	{
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(event);
	}

	__forceinline Real fadedVolume(PlayingAudio *playing)
	{
		Real volume = compute((Rva006AE150Argument *)playing->m_audioEventRTS.ptr, 1);
		Rva006B24D0Settings *settings = m_settings;
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)settings->m_fadeAudioFrames);
		if (fade < Rva006B24D0Zero)
			fade = Rva006B24D0Zero;
		else if (fade > Rva006B24D0One)
			fade = Rva006B24D0One;
		return volume * fade;
	}

	Rva006B24D0Settings *m_settings;
	char m_pad010[0x94 - 0x10];
	Rva006B24D0EventVector m_pendingEvents[3];
	char m_pad0b8[0x9c8 - 0xb8];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	PlayingAudioQueue m_queues[3][2];
	char m_padac4[0xb44 - 0x9d4 - 6 * sizeof(PlayingAudioQueue)];
	Rva006B24D0Slot *m_slotTable;
};

typedef char Rva006B24D0QueueSize[(sizeof(PlayingAudioQueue) == 0x28) ? 1 : -1];

// ?rva006B24D0@MilesAudioManager@@QAEXABVAsciiString@@MH@Z
void MilesAudioManager::rva006B24D0(const AsciiString &eventName, Real unused, int category)
{
	PlayingAudioRef playing;
	const Rva006B24D0Name &name = (const Rva006B24D0Name &)eventName;
	PlayingAudioList::iterator it;
	Real pan;

	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
	{
		playing = *it;
		if (!playing)
			continue;
		if (name.isSet())
		{
			AudioEventRTS *event = playing->m_audioEventRTS.ptr;
			const AsciiString &candidateName = event->m_eventInfo->getName();
			if (((const StringBase<char> &)candidateName).compare(eventName) != 0)
				continue;
		}
		if (playing->m_audioEventRTS->getTimeOfDay() != category)
			continue;
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(playing->m_audioEventRTS.ptr);
		Real volume = compute((Rva006AE150Argument *)playing->m_audioEventRTS.ptr, 1);
		Rva006B24D0Settings *settings = m_settings;
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)settings->m_fadeAudioFrames);
		if (fade < Rva006B24D0Zero)
			fade = Rva006B24D0Zero;
		else if (fade > Rva006B24D0One)
			fade = Rva006B24D0One;
		volume = volume * fade;
		_AIL_sample_volume_pan(playing->m_milesHandle, 0, &pan);
		_AIL_set_sample_volume_pan(playing->m_milesHandle, volume, pan);
	}

	for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
	{
		playing = *it;
		if (!playing)
			continue;
		if (name.isSet())
		{
			AudioEventRTS *event = playing->m_audioEventRTS.ptr;
			const AsciiString &candidateName = event->m_eventInfo->getName();
			if (candidateName.compare(eventName) != 0)
				continue;
		}
		if (!playing->m_audioEventRTS->isTimeOfDay(category))
			continue;
		H3DSAMPLE sample3D;
		switch (playing->m_type)
		{
		case 1:
			sample3D = (H3DSAMPLE)playing->m_milesHandle;
			break;
		case 2:
			sample3D = m_slotTable[(int)(long)playing->m_milesHandle].m_slot;
			break;
		default:
			continue;
		}
		if (!sample3D)
			continue;
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(playing->m_audioEventRTS.ptr);
		Real volume = compute((Rva006AE150Argument *)playing->m_audioEventRTS.ptr, 1);
		Rva006B24D0Settings *settings = m_settings;
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)settings->m_fadeAudioFrames);
		if (fade < Rva006B24D0Zero)
			fade = Rva006B24D0Zero;
		else if (fade > Rva006B24D0One)
			fade = Rva006B24D0One;
		volume = volume * fade;
		_AIL_set_3D_sample_volume(sample3D, volume);
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (!playing)
			continue;
		if (name.isSet())
		{
			AudioEventRTS *event = playing->m_audioEventRTS.ptr;
			const AsciiString &candidateName = event->m_eventInfo->getName();
			if (candidateName.compare(eventName) != 0)
				continue;
		}
		if (playing->m_audioEventRTS->getTimeOfDay() != category)
			continue;
		if (playing->m_audioEventRTS->m_eventInfo->m_type84 == 3)
			continue;
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(playing->m_audioEventRTS.ptr);
		AudioEventRTS *event = playing->m_audioEventRTS.ptr;
		Real volume = compute((Rva006AE150Argument *)event, 1);
		Rva006B24D0Settings *settings = m_settings;
		Real fade = 1.0f - (playing->m_fadeFrame / (Real)settings->m_fadeAudioFrames);
		if (fade < Rva006B24D0Zero)
			fade = Rva006B24D0Zero;
		else if (fade > Rva006B24D0One)
			fade = Rva006B24D0One;
		volume = volume * fade;
		HSTREAM streamHandle = playing->m_milesHandle;
		queryStreamPan(&pan, streamHandle);
		_AIL_set_stream_volume_pan(playing->m_milesHandle, volume, pan);
	}

	for (int q = 0; q < 2; ++q)
	{
		PlayingAudioQueue &queue = m_queues[category][q];
		PlayingAudioQueue::iterator qit = queue.begin();
		PlayingAudioQueue::iterator qend = queue.end();
		for (; qit != qend; ++qit)
		{
			playing = *qit;
			if (!playing)
				continue;
			if (name.isSet() &&
				playing->m_audioEventRTS->m_eventInfo->getName().compare(eventName) != 0)
				continue;
			if (playing->m_audioEventRTS->getTimeOfDay() != category)
				continue;
			((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(playing->m_audioEventRTS.ptr);
		}
	}

	Rva006B24D0EventVector::iterator end = m_pendingEvents[category].end();
	Rva006B24D0EventVector::iterator event = m_pendingEvents[category].begin();
	for (; event != end; ++event)
	{
		if (name.isSet() && event->m_eventInfo->getName().compare(eventName) != 0)
			continue;
		AudioEventRTS *adjustedEvent = playing->m_audioEventRTS.ptr;
		((Rva006AD590Owner *)this)->bfmeAdjustPriorityAndVolume(adjustedEvent);
	}
}

// ?resumeAudio@MilesAudioManager@@UAEXIHH@Z
// partial score=0.3 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Scratch reconstruction of the BFME MilesAudioManager resumeAudio body.

#include <list>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_pause_stream(
	void *stream, int pause);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);


enum AudioAffect
{
	AudioAffect_Music = 0x01,
	AudioAffect_Sound = 0x02,
	AudioAffect_Sound3D = 0x04,
	AudioAffect_Speech = 0x08,
	AudioAffect_AmbientStream = 0x10,
	AudioAffect_SystemSetting = 0x20
};

enum PlayingAudioType
{
	PAT_Sample,
	PAT_3DSample,
	PAT_Stream,
	PAT_Invalid
};

enum PlayingStatus
{
	PS_Playing,
	PS_Stopped,
	PS_Paused
};

class AudioEventRTS
{
public:
	unsigned int getSoundClass(void) const;

	private:
	char m_pad00[0x28];

	public:
	int m_timeOfDay;
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

class PlayingAudio : public RefCountedPlayingAudio
{
public:
	void *m_milesHandle;
	PlayingAudioType m_type;
	volatile PlayingStatus m_status;
	AudioEventRTS *m_audioEventRTS;
	char m_pad18[0x21];
	unsigned char m_pauseFlags[4];
	char m_pad3d[3];
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

class MilesAudioScopedMutex
{
public:
	__forceinline MilesAudioScopedMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	__forceinline ~MilesAudioScopedMutex(void)
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
	}

private:
	void *m_mutex;
	unsigned char m_held;
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;

class MilesAudioManager
{
public:
	virtual void resumeAudio(unsigned int which, int mask, int clear);
	void releasePlayingAudioRef(PlayingAudioRef *playing);
	void updateAudioState(unsigned int which, int mask, int clear);

private:
	char m_pad004[0x61c - 4];
	unsigned int m_suppressedAudio;
	unsigned int m_systemSuppressedAudio;
	char m_pad624[0x63c - 0x624];
	unsigned int m_audioStates[3];
	char m_pad648[0x95c - 0x648];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
};

#pragma comment(linker, "/alternatename:?releasePlayingAudioRef@MilesAudioManager@@QAEXPAVPlayingAudioRef@@@Z=?j_0002e668@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateAudioState@MilesAudioManager@@QAEXIHH@Z=?j_0000e04d@@YAXXZ")

void MilesAudioManager::resumeAudio(unsigned int which, int mask, int clear)
{
	MilesAudioScopedMutex guard(m_mutex);
	PlayingAudioList::iterator it;
	PlayingAudioRef playing;

	if (which & AudioAffect_Sound)
	{
		for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
				int timeOfDay = playing->m_audioEventRTS->m_timeOfDay;
				if (mask & (1 << timeOfDay))
				{
					if (which & AudioAffect_SystemSetting)
						playing->m_pauseFlags[1] = 0;
					else
						playing->m_pauseFlags[0] = 0;

					if (playing->m_pauseFlags[0] || playing->m_pauseFlags[1] ||
						playing->m_pauseFlags[2] || playing->m_pauseFlags[3])
						AIL_stop_sample(playing->m_milesHandle);
					else
						AIL_resume_sample(playing->m_milesHandle);
				}
			}
		}
	}

	if (which & AudioAffect_Sound3D)
	{
		for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
				int timeOfDay = playing->m_audioEventRTS->m_timeOfDay;
				if (mask & (1 << timeOfDay))
				{
					if (which & AudioAffect_SystemSetting)
						playing->m_pauseFlags[1] = 0;
					else
						playing->m_pauseFlags[0] = 0;
					releasePlayingAudioRef(&playing);
				}
			}
		}
	}

	if (which & AudioAffect_AmbientStream)
	{
		for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
		{
			playing = *it;
			if (playing && (mask & (1 << playing->m_audioEventRTS->m_timeOfDay)) &&
				(which & playing->m_audioEventRTS->getSoundClass()))
			{
				if (which & AudioAffect_SystemSetting)
					playing->m_pauseFlags[1] = 0;
				else
					playing->m_pauseFlags[0] = 0;
				if (playing->m_pauseFlags[0] || playing->m_pauseFlags[1] ||
					playing->m_pauseFlags[2] || playing->m_pauseFlags[3])
					AIL_pause_stream(playing->m_milesHandle, 1);
				else
					AIL_pause_stream(playing->m_milesHandle, 0);
			}
		}
	}

	if (which & AudioAffect_AmbientStream)
	{
		if (which & AudioAffect_SystemSetting)
			m_systemSuppressedAudio &= ~mask;
		else
			m_suppressedAudio &= ~mask;
		updateAudioState(which, mask, clear);

		if (!clear)
		{
			unsigned int *state = m_audioStates;
			for (int i = 0; i < 3; ++i, ++state)
			{
				if (mask & (1 << i))
				{
					if (which & AudioAffect_SystemSetting)
						state[3] &= ~(which & ~AudioAffect_SystemSetting);
					else
						*state &= ~which;
				}
			}
		}
	}
}

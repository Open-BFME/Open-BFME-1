// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's MilesAudioManager::stopAudio keeps the three-list structure of the
// Generals implementation, but stores intrusive references and protects the
// lists with the manager mutex.  Retail vtable 0x0111C0C0 slot +0x28 routes
// through 0x0004839C to this body; the owner body at 0x006ACF50 installs that
// vtable and accesses the same mutex (+0x95C) and handle-state table (+0xB44).

#include <list>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) void *__stdcall AIL_register_EOS_callback(
	void *sample, void *callback);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_sample(void *sample);
extern "C" __declspec(dllimport) void *__stdcall AIL_register_3D_EOS_callback(
	void *sample, void *callback);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(void *sample);
extern "C" __declspec(dllimport) void *__stdcall AIL_register_stream_callback(
	void *stream, void *callback);
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
	AudioAffect_Speech = 0x08
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
	virtual void stopAudio(AudioAffect which);

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	char m_pad9d4[0xb44 - 0x9d4];
	unsigned char *m_handleState;
};

void MilesAudioManager::stopAudio(AudioAffect which)
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
				AIL_register_EOS_callback(playing->m_milesHandle, 0);
				AIL_stop_sample(playing->m_milesHandle);
				playing->m_status = PS_Stopped;
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
				if (playing->m_type == PAT_3DSample)
				{
					AIL_register_3D_EOS_callback(playing->m_milesHandle, 0);
					AIL_stop_3D_sample(playing->m_milesHandle);
					playing->m_status = PS_Stopped;
				}
				else
				{
					m_handleState[(unsigned int)playing->m_milesHandle * 64 + 1] = 1;
				}
			}
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (playing && (which & playing->m_audioEventRTS->getSoundClass()))
		{
			AIL_register_stream_callback(playing->m_milesHandle, 0);
			AIL_pause_stream(playing->m_milesHandle, 1);
			playing->m_status = PS_Stopped;
		}
	}
}

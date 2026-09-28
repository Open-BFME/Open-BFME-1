// ?pauseAudio@MilesAudioManager@@UAEXW4AudioAffect@@HH@Z
// partial score=0.48826 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Retail 006A8540 pauseAudio: vtable 0111C0C0 slot +2C via 000194B1.
// BfmeGameLogicPause_setGamePaused calls the three-argument signature.
// Intrusive reference and mutex layout are shared with landed stopAudio.

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
extern "C" __declspec(dllimport) void __stdcall AIL_resume_sample(void *sample);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(void *sample);
extern "C" __declspec(dllimport) void __stdcall AIL_resume_3D_sample(void *sample);
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
    char pad00[0x28];
    unsigned int dword28;
    unsigned int getAffectIndex006A8540() const { return dword28; }
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
    char m_pad18[0x39-0x18];
    bool m_flag39, m_flag3a, m_flag3b, m_flag3c;
    bool isPaused006A8540() const { return m_flag39 || m_flag3a || m_flag3b || m_flag3c; }
};

class PlayingAudioRef
{
    friend class MilesAudioManager;
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
	virtual void pauseAudio(AudioAffect which, int affectMask, int clearStates);
    void resume3D(PlayingAudioRef *playing);

private:
	char m_pad004[0x61c - 4];
    unsigned int m_audioAffects, m_systemAffects;
    char m_pad624[0x63c-0x624];
    unsigned int m_audioStates[3], m_systemStates[3];
    char m_pad654[0x95c-0x654];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	char m_pad9d4[0xb44 - 0x9d4];
	unsigned char *m_handleState;
};

class RequestFlags006A6B40 {
public:
    void apply(unsigned int classes, unsigned int types, bool value);
};

void MilesAudioManager::resume3D(PlayingAudioRef *playingRef)
{
	PlayingAudioRef *ref = playingRef;
	PlayingAudio *playing = ref->m_ptr;
	PlayingAudioType type = playing->m_type;
	void *sample;

	switch (type)
	{
		case PAT_3DSample:
			sample = playing->m_milesHandle;
			break;
		case PAT_Stream:
		{
			unsigned int handle = (unsigned int)playing->m_milesHandle;
			sample = *(void **)(m_handleState + handle * 64 + 4);
			break;
		}
		default:
			return;
	}

	if (!sample)
		return;

	do
	{
		if (playing->m_flag39)
			break;
		if (playing->m_flag3a)
			break;
		if (playing->m_flag3b)
			break;
		if (playing->m_flag3c)
			break;
		goto resumePlaying;
	}
	while (false);

	if (AIL_3D_sample_status(sample) != 2)
		AIL_stop_3D_sample(sample);
	return;

resumePlaying:
	{
		if (type == PAT_Stream)
		{
			unsigned int handle = (unsigned int)playing->m_milesHandle;
			unsigned char *state = m_handleState + handle * 64;
			if (state[1])
				return;
			if (AIL_3D_sample_status(*(void **)(state + 4)) == 8)
				return AIL_resume_3D_sample(*(void **)(state + 4));
		}
		else if (AIL_3D_sample_status(ref->m_ptr->m_milesHandle) == 8)
			return AIL_resume_3D_sample(ref->m_ptr->m_milesHandle);

		return;
	}
}

static inline bool HasAffect006A8540(int mask, unsigned int index) { return (mask & (1 << index)) != 0; }

void MilesAudioManager::pauseAudio(AudioAffect which, int affectMask, int clearStates)
{
    MilesAudioScopedMutex guard(m_mutex);
    PlayingAudioList::iterator it;
    PlayingAudioRef playing;
    if (which & 2) {
        for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it) {
            playing = *it;
            if (playing) {
                unsigned int index = playing->m_audioEventRTS->getAffectIndex006A8540();
                if (affectMask & (1 << index)) {
                if (which & 0x20) playing->m_flag3a = true;
                else playing->m_flag39 = true;
                if (playing->isPaused006A8540())
                    AIL_stop_sample(playing->m_milesHandle);
                else AIL_resume_sample(playing->m_milesHandle);
                }
            }
        }
    }
    if (which & 4) {
        for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it) {
            playing = *it;
            if (playing) {
                unsigned int index = playing->m_audioEventRTS->getAffectIndex006A8540();
                if (affectMask & (1 << index)) {
                if (which & 0x20) playing->m_flag3a = true;
                else playing->m_flag39 = true;
                resume3D(&playing);
                }
            }
        }
    }
    for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it) {
        playing = *it;
        if (playing && HasAffect006A8540(affectMask, playing->m_audioEventRTS->getAffectIndex006A8540()) &&
            (which & playing->m_audioEventRTS->getSoundClass())) {
            if (which & 0x20) playing->m_flag3a = true;
            else playing->m_flag39 = true;
            bool pause = playing->isPaused006A8540();
            AIL_pause_stream(playing->m_milesHandle, pause);
        }
    }
    if (which & 0x10) {
        if (which & 0x20) m_systemAffects |= affectMask;
        else m_audioAffects |= affectMask;
    }
    ((RequestFlags006A6B40 *)this)->apply(which, affectMask, true);
    if (!clearStates) {
        for (int i = 0; i < 3; ++i) {
            if (affectMask & (1 << i)) {
                if (which & 0x20) m_systemStates[i] |= (which & ~0x20);
                else m_audioStates[i] |= which;
            }
        }
    }
}

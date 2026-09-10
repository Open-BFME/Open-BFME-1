// ?resumeAudio@MilesAudioManager@@UAEXIHH@Z
// partial score=0.55 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// BFME's MilesAudioManager::resumeAudio is the vtable slot at
// 0x0111C0C0 + 0x30.  The BFME caller view in
// GameClient/GUI/GUICallbacks/Menus/BfmeGameLogicPause_setGamePaused.cpp
// proves the three-argument ABI: (which, affectMask, clearStates).

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

// These are the retail ILT entries used by the body.  They are direct calls
// to existing addresses, not alternate-name substitutions or local stubs.
class PlayingAudioRef;
extern void j_0002e668(void);
extern void j_0000e04d(void);
extern void j_00015a69(void);

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

	unsigned int getTimeOfDay(void) const
	{
		return m_timeOfDay;
	}

private:
	void *m_vftable;
	char m_pad004[0x28 - 4];
	unsigned int m_timeOfDay;
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
	int m_type;
	volatile PlayingStatus m_status;
	AudioEventRTS *m_audioEventRTS;
	char m_pad018[0x39 - 0x18];
	bool m_flag39;
	bool m_flag3a;
	bool m_flag3b;
	bool m_flag3c;
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
	virtual void resumeAudio(unsigned int which, int affectMask, int clearStates);

private:
	char m_pad004[0x61c - 4];
	unsigned int m_audioAffects;
	unsigned int m_systemAffects;
	char m_pad624[0x63c - 0x624];
	unsigned int m_audioStates[3];
	unsigned int m_systemStates[3];
	char m_pad654[0x95c - 0x654];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
};

typedef void (MilesAudioManager::*Resume3D)(PlayingAudioRef *);
typedef void (MilesAudioManager::*UpdateAudioState)(unsigned int, unsigned int, int);

void MilesAudioManager::resumeAudio(unsigned int which, int affectMask, int clearStates)
{
	MilesAudioManager *manager = this;
	MilesAudioScopedMutex guard(manager->m_mutex);
	PlayingAudioList::iterator it;
	PlayingAudioRef playing;

	if (which & 2)
	{
		for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
				AudioEventRTS *event = playing->m_audioEventRTS;
				if (affectMask & (1 << event->getTimeOfDay()))
				{
					if (which & 0x20)
						playing->m_flag3a = false;
					else
						playing->m_flag39 = false;

					if (playing->m_flag39 || playing->m_flag3a ||
						playing->m_flag3b || playing->m_flag3c)
						AIL_stop_sample(playing->m_milesHandle);
					else
						AIL_resume_sample(playing->m_milesHandle);
				}
			}
		}
	}

	if (which & 4)
	{
		for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
		{
			playing = *it;
			if (playing)
			{
				AudioEventRTS *event = playing->m_audioEventRTS;
				if (affectMask & (1 << event->getTimeOfDay()))
				{
					if (which & 0x20)
						playing->m_flag3a = false;
					else
						playing->m_flag39 = false;

					Resume3D resume3D;
					union
					{
						void (*asFunction)(void);
						Resume3D asMember;
					} call;
					call.asFunction = j_0002e668;
					(reinterpret_cast<MilesAudioManager *>(this)->*call.asMember)(&playing);
				}
			}
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (playing)
		{
			AudioEventRTS *event = playing->m_audioEventRTS;
			if (affectMask & (1 << event->getTimeOfDay()))
			{
				union
				{
					void (*asFunction)(void);
					unsigned int (AudioEventRTS::*asMember)(void) const;
				} getSoundClass;
				getSoundClass.asFunction = j_00015a69;
				if (which & (event->*getSoundClass.asMember)())
				{
					if (which & 0x20)
						playing->m_flag3a = false;
					else
						playing->m_flag39 = false;

					bool pause = playing->m_flag39 || playing->m_flag3a ||
						playing->m_flag3b || playing->m_flag3c;
					AIL_pause_stream(playing->m_milesHandle, pause ? 1 : 0);
				}
			}
		}
	}

	if (which & 0x10)
	{
		if (which & 0x20)
			m_systemAffects &= ~static_cast<unsigned int>(affectMask);
		else
			m_audioAffects &= ~static_cast<unsigned int>(affectMask);
	}

	union
	{
		void (*asFunction)(void);
		UpdateAudioState asMember;
	} call;
	call.asFunction = j_0000e04d;
	(manager->*call.asMember)(which, affectMask, 0);

	if (!clearStates)
	{
		unsigned int *audioState = m_audioStates;
		unsigned int *systemState = m_systemStates;
		for (unsigned int i = 0; i < 3; ++i)
		{
			if (!(affectMask & (1 << i)))
			{
				if (which & 0x20)
					*systemState &= ~(which & ~0x20u);
				else
					*audioState &= ~which;
			}
			++audioState;
			++systemState;
		}
	}
}

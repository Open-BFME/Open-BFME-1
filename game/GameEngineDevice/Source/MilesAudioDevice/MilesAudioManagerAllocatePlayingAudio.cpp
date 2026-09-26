// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x0069AAA0 returns a counted PlayingAudio handle by value.
// MilesAudioManager::allocatePlayingAudio creates the 0x40-byte object and
// changes its initial stopped status to playing before the handle returns.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

enum PlayingStatus
{
	PS_Playing,
	PS_Stopped,
	PS_Paused
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
	PlayingAudio();
	virtual ~PlayingAudio();

	void *m_milesHandle;
	int m_type;
	volatile PlayingStatus m_status;
	char m_tail[0x2c];
};

class PlayingAudioRef
{
public:
	PlayingAudioRef(void) : m_ptr(0) {}

	PlayingAudioRef(PlayingAudio *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}

	PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}

	~PlayingAudioRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	PlayingAudio *operator->(void) const
	{
		return m_ptr;
	}

private:
	PlayingAudio *m_ptr;
};

class MilesAudioManager
{
public:
	PlayingAudioRef allocatePlayingAudio(void);
};

// ?allocatePlayingAudio@MilesAudioManager@@QAE?AVPlayingAudioRef@@XZ
PlayingAudioRef MilesAudioManager::allocatePlayingAudio(void)
{
	PlayingAudioRef audio = new PlayingAudio;
	audio->m_status = PS_Playing;
	return audio;
}

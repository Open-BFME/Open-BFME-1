// ?rva006B0410@Rva006B0630Owner@@QAEXE@Z
// partial score=0.272093 date=2026-09-25
// Draft for retail 0x006B0410, the audio-provider refresh called by the
// landed Rva006B0630Owner::rva006B0410(unsigned char).
// cl: /O2 /Ob2 /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
#include <list>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern float g_Va0112E8B0;

// Existing APIs from Rva006ABFD0AudioLoop.cpp and
// AudioEventRTS_bfmeGenerateFilename.cpp.
class Rva006ABFD0Event
{
public:
	bool hasMoreLoops() const;
	void advance();
	void advanceNextPlayPortion();
	void clamp(float low, float high);
	char m_pad[0x44];
	unsigned char m_flag;
};

class AudioEventRTS
{
public:
	void bfmeGenerateFilename();
};

class RefCountedPlayingAudio
{
public:
	virtual ~RefCountedPlayingAudio();
	void Add_Ref() { InterlockedIncrement(&m_refCount); }
	void Release_Ref()
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}
	long m_refCount;
};

class PlayingAudio : public RefCountedPlayingAudio
{
public:
	char m_pad008[0x14 - 8];
	AudioEventRTS *m_audioEventRTS;
};

class PlayingAudioRef
{
public:
	PlayingAudioRef() : m_ptr(0) {}
	PlayingAudioRef(PlayingAudio *p) : m_ptr(p) { if (m_ptr) m_ptr->Add_Ref(); }
	PlayingAudioRef(const PlayingAudioRef &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			m_ptr->Add_Ref();
	}
	~PlayingAudioRef()
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}
	operator PlayingAudio *() const { return m_ptr; }
	PlayingAudio *operator->() const { return m_ptr; }
	PlayingAudio *m_ptr;
};

typedef _STL::list<PlayingAudioRef> PlayingAudioList;
typedef char PlayingAudioListMustBeFourBytes[
	(sizeof(PlayingAudioList) == 4) ? 1 : -1];

class Rva006ABFD0Playing
{
public:
	char m_pad00[0x0c];
	int m_type;
	char m_pad10[4];
	Rva006ABFD0Event *m_event;
};

class Rva006ABFD0Slot
{
public:
	Rva006ABFD0Playing *m_playing;
};

class Rva006ABFD0
{
public:
	friend class Rva006B0630Owner;

private:
	void add(Rva006ABFD0Slot *slot);
};

class MilesAudioManager
{
public:
	void rva006A59F0(PlayingAudio *release);
	private:
	friend class Rva006B0630Owner;
	void setHardwareAccelerated(unsigned char accelerated);
};

class Rva0069AB70Owner
{
public:
	void closeProvider();
};

class BfmeOwnerVOB
{
public:
	void bfmeClearVOB();
};

class Rva00695AB0Owner
{
public:
	void setRoomType(int room);
};

class Rva006B0630Owner
{
public:
	void rva006B0410(unsigned char enabled);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	char m_pad04[0x954];
	int m_selectedProvider;
	void *m_mutex;
	char m_pad960[0x6c];
	PlayingAudioList m_playingAudio;
	char m_padListEnd[0xB54 - 0x9cc - sizeof(PlayingAudioList)];
	int m_roomType;
};

class Rva006B0410MutexGuard
{
public:
	Rva006B0410MutexGuard(void *handle)
	{
		m_owned = false;
		m_handle = handle;
		if (WaitForSingleObject(m_handle, 0xffffffffu) != 0x102u)
			m_owned = true;
	}
	~Rva006B0410MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}
	bool m_owned;
	void *m_handle;
};

void Rva006B0630Owner::rva006B0410(unsigned char enabled)
{
	if (m_selectedProvider != -1)
	{
		Rva006B0410MutexGuard guard(m_mutex);
		for (PlayingAudioList::iterator it = m_playingAudio.begin();
			it != m_playingAudio.end(); )
		{
			PlayingAudio *audio = it->m_ptr;
			PlayingAudioRef local(audio);
			Rva006ABFD0Playing *playing =
				reinterpret_cast<Rva006ABFD0Playing *>(audio);
			if (playing->m_event->hasMoreLoops())
			{
				reinterpret_cast<AudioEventRTS *>(playing->m_event)->bfmeGenerateFilename();
				if (playing->m_event->hasMoreLoops())
				{
					playing->m_event->advanceNextPlayPortion();
					playing->m_event->clamp(34.3333321f, g_Va0112E8B0);
					playing->m_event->m_flag = 1;
					((Rva006ABFD0 *)this)->add(
						reinterpret_cast<Rva006ABFD0Slot *>(&local));
				}
			}
		((MilesAudioManager *)this)->rva006A59F0(audio);
			it = m_playingAudio.erase(it);
		}
		((BfmeOwnerVOB *)this)->bfmeClearVOB();
		((Rva0069AB70Owner *)this)->closeProvider();
	}
	((MilesAudioManager *)this)->setHardwareAccelerated(enabled);
	if (m_selectedProvider != -1)
	{
		((Rva00695AB0Owner *)this)->setRoomType(m_roomType);
		slot14();
	}
}

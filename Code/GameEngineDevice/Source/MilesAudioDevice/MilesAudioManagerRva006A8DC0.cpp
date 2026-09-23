// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail vtable 0x0111C0C0 (MilesAudioManager) slot 20 routes through ILT
// 0x00018075 to this body.  It keeps the Zero Hour killAudioEventImmediately
// order -- pending requests, then the 3D, 2D and stream lists at +0x9cc,
// +0x9c8 and +0x9d0 -- but BFME holds the manager mutex (+0x95c), also drops
// the request from the handle-keyed table at +0x50, scans the six
// PlayingAudioRef deques at +0x9d4, keeps going after the first match and
// reports whether anything was killed.

#include <list>
#include <deque>

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

typedef unsigned int AudioHandle;

enum RequestType
{
	AR_Play
};

class AudioEventRTS
{
public:
	AudioHandle getPlayingHandle(void) const { return m_playingHandle; }

private:
	char m_pad000[0xc];
	AudioHandle m_playingHandle;
};

class RefCountedPlayingAudio
{
public:
	virtual ~RefCountedPlayingAudio();

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
	char m_pad008[0x14 - 8];
	AudioEventRTS *m_audioEventRTS;
};

class PlayingAudioRef
{
public:
	~PlayingAudioRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	operator PlayingAudio *(void) const { return m_ptr; }
	PlayingAudio *operator->(void) const { return m_ptr; }

private:
	PlayingAudio *m_ptr;
};

// The AudioRequest destructor at 0x006912A0 carries this ledger name.
class BfmeHostESG
{
public:
	~BfmeHostESG();
};

struct AudioRequest : public BfmeHostESG
{
	RequestType m_request;
	unsigned int dword_4;
	AudioHandle m_handleToInteractOn;
};

// Handle-keyed request table at +0x50: find is 0x006A1650, erase 0x006A0810.
struct Rva006A0810Node
{
	Rva006A0810Node *m_next;
	AudioRequest *m_request;
};

struct SelfPair006A1650
{
	Rva006A0810Node *m_value;
	void *m_owner;
};

class Rva006A1650Maker
{
public:
	SelfPair006A1650 *make(SelfPair006A1650 *result, void *argument);
};

class Rva006A0810Table
{
public:
	void erase(Rva006A0810Node **it);
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

typedef _STL::list<AudioRequest *> AudioRequestList;
typedef _STL::list<PlayingAudioRef> PlayingAudioList;
typedef _STL::deque<PlayingAudioRef> PlayingAudioDeque;

class MilesAudioManager
{
public:
	virtual bool rva006A8DC0(AudioHandle audioEvent);

	void rva006A59F0(PlayingAudio *release);

private:
	char m_pad004[0x4c - 4];
	AudioRequestList m_audioRequests;
	Rva006A0810Table m_requestTable050;
	char m_pad051[0x95c - 0x51];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	PlayingAudioDeque m_deques9d4[3][2];
};

bool MilesAudioManager::rva006A8DC0(AudioHandle audioEvent)
{
	MilesAudioScopedMutex guard(m_mutex);
	bool killed = false;

	{
		SelfPair006A1650 found;
		((Rva006A1650Maker *)&m_requestTable050)->make(&found, (void *)audioEvent);
		if (found.m_value)
		{
			AudioRequest *req = found.m_value->m_request;
			SelfPair006A1650 it = found;
			m_requestTable050.erase(&it.m_value);
			delete req;
			killed = true;
		}
	}

	AudioRequestList::iterator ait = m_audioRequests.begin();
	while (ait != m_audioRequests.end())
	{
		AudioRequest *req = *ait;
		if (req && req->m_request == AR_Play && req->m_handleToInteractOn == audioEvent)
		{
			delete req;
			ait = m_audioRequests.erase(ait);
			killed = true;
		}
		else
		{
			++ait;
		}
	}

	PlayingAudioList::iterator it;
	for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
	{
		PlayingAudio *audio = *it;
		if (!audio)
			continue;

		if (audio->m_audioEventRTS->getPlayingHandle() == audioEvent)
		{
			rva006A59F0(*it);
			m_playing3DSounds.erase(it);
			killed = true;
			break;
		}
	}

	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
	{
		PlayingAudio *audio = *it;
		if (!audio)
			continue;

		if (audio->m_audioEventRTS->getPlayingHandle() == audioEvent)
		{
			rva006A59F0(*it);
			m_playingSounds.erase(it);
			killed = true;
			break;
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		PlayingAudio *audio = *it;
		if (!audio)
			continue;

		if (audio->m_audioEventRTS->getPlayingHandle() == audioEvent)
		{
			rva006A59F0(*it);
			m_playingStreams.erase(it);
			killed = true;
			break;
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			PlayingAudioDeque &queue = m_deques9d4[i][j];
			for (PlayingAudioDeque::iterator qit = queue.begin(); qit != queue.end(); ++qit)
			{
				PlayingAudio *audio = *qit;
				if (!audio)
					continue;

				if (audio->m_audioEventRTS->getPlayingHandle() == audioEvent)
				{
					rva006A59F0(*qit);
					queue.erase(qit);
					killed = true;
					break;
				}
			}
		}
	}

	return killed;
}

// ?rva006A9200@MilesAudioManager@@QAEXI@Z
// partial score=0.94 date=2026-09-28
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva006A9200@MilesAudioManager@@QAEXI@Z
// Retail 0x006A9200, 1179 bytes (ret 4 at +0x498; the 1168 B gen row is short).
// MilesAudioManager: callers setHardwareAccelerated (0x006A9910) and
// rva006B86D0 are matched MilesAudioManager methods.  Shape of Zero Hour
// stopAllAudioImmediately with a which-mask: release+erase matching entries
// of the three PlayingAudioRef lists (+0x9C8/+0x9CC/+0x9D0) through
// rva006A59F0 (ILT 0x0002669D), per set bit i<3 clear the 0x78-byte event
// vector at +0x94+12i and drain two PlayingAudioRef deques at +0x9D4+0x50i,
// and for bit 2 AIL_quick_unload every m_audioForcePlayed (+0x9BC) handle
// then clear it.  Built with /O2 default inlining (/Ob2): retail inlines
// deque::_M_pop_back_aux and _List_base::clear, which /Ob1 leaves out of line.
// Remaining residue: ours keeps this in ebx for the whole body; retail spills
// this to [esp+0x14] and caches InterlockedIncrement in ebx during the list
// loops, so the frame is 0x24 vs 0x28 and every later slot shifts by 4; and
// retail routes the mask shift count through eax (mov eax,[eax+0x28];
// mov ecx,eax).

#include <list>
#include <vector>
#include <deque>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

typedef struct _AUDIO *HAUDIO;
extern "C" __declspec(dllimport) void __stdcall AIL_quick_unload(HAUDIO audio);

class AudioEventRTS
{
public:
	AudioEventRTS &operator=(const AudioEventRTS &other);
	~AudioEventRTS();
	int getField28(void) const { return m_28; }

	char m_pad000[0x28];
	int m_28;
	char m_pad02c[0x70 - 0x2c];
};

class Rva0069C9D0Element : public AudioEventRTS
{
public:
	Rva0069C9D0Element &operator=(const Rva0069C9D0Element &other)
	{
		AudioEventRTS::operator=(other);
		m_word70 = other.m_word70;
		m_byte74 = other.m_byte74;
		return *this;
	}

private:
	unsigned int m_word70;
	unsigned char m_byte74;
	char m_pad75[3];
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
	volatile int m_status;
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

typedef _STL::list<PlayingAudioRef> PlayingAudioList;
typedef _STL::deque<PlayingAudioRef> PlayingAudioDeque;

class MilesAudioManager
{
public:
	void rva006A9200(unsigned int which);
	void rva006A59F0(PlayingAudio *playing);

private:
	char m_pad000[0x94];
	_STL::vector<Rva0069C9D0Element> m_vectors094[3];		// +0x094
	char m_pad0b8[0x9bc - 0xb8];
	_STL::list<HAUDIO> m_audioForcePlayed;				// +0x9bc
	char m_pad9c0[0x9c8 - 0x9c0];
	PlayingAudioList m_playingSounds;					// +0x9c8
	PlayingAudioList m_playing3DSounds;					// +0x9cc
	PlayingAudioList m_playingStreams;					// +0x9d0
	PlayingAudioDeque m_deques9d4[3][2];				// +0x9d4
};

void MilesAudioManager::rva006A9200(unsigned int which)
{
	PlayingAudioRef playing;
	PlayingAudioList::iterator it;

	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); )
	{
		playing = *it;
		if (playing && (which & (1 << playing->m_audioEventRTS->getField28())))
		{
			rva006A59F0(playing);
			it = m_playingSounds.erase(it);
		}
		else
			++it;
	}

	for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); )
	{
		playing = *it;
		if (playing && (which & (1 << playing->m_audioEventRTS->getField28())))
		{
			rva006A59F0(playing);
			it = m_playing3DSounds.erase(it);
		}
		else
			++it;
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); )
	{
		playing = *it;
		if (playing && (which & (1 << playing->m_audioEventRTS->getField28())))
		{
			rva006A59F0(playing);
			it = m_playingStreams.erase(it);
		}
		else
			++it;
	}

	for (int i = 0; i < 3; ++i)
	{
		if (which & (1 << i))
		{
			m_vectors094[i].clear();
			PlayingAudioDeque *deque = m_deques9d4[i];
			for (int j = 0; j < 2; ++j, ++deque)
			{
				while (!deque->empty())
				{
					rva006A59F0(deque->back());
					deque->pop_back();
				}
			}
		}
	}

	if (which & 4)
	{
		_STL::list<HAUDIO>::iterator hit;
		for (hit = m_audioForcePlayed.begin(); hit != m_audioForcePlayed.end(); ++hit)
		{
			if (*hit)
				AIL_quick_unload(*hit);
		}
		m_audioForcePlayed.clear();
	}
}

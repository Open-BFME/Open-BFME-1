// ?rva006A6080@MilesAudioManager@@QAE_NABVAsciiString@@HHI@Z
// partial score=0.9942 date=2026-09-30
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common
// stlport
// Retail 006A6080: stream and indexed-deque loop-budget predicate.
// Shared MilesAudioManager mutex/list/cell layouts witnessed by 006A5600,
// 006A57D0 and 0069D2C0. No evidence supplies this method's semantic name.
// The inline event and playing-audio accessors set retail's register choices
// (loop 1 and the loop-2 compare); 5 register bytes remain at +0x25B/+0x293.

#include <list>
#include <deque>
#include "ascii_string.h"
struct Rva006990E0Kind
{
	unsigned char m_pad0[0x3c];
	unsigned char m_flag;
	unsigned char m_pad3d[0x84 - 0x3d];
	unsigned int m_kind;
};

struct Rva006990E0Request
{
	unsigned char m_pad0[8];
	Rva006990E0Kind *m_kind;
	unsigned char m_pad0c[0x68 - 0xc];
	int m_value;
};

// Native static helper visibility avoids a fabricated ECX dummy argument.
// Its emitted 88 bytes independently probe exact against 006990E0.
static int rva006990E0(Rva006990E0Request *request)
{
	Rva006990E0Kind *kind = request->m_kind;
	if (kind == 0)
		return 1;

	switch (kind->m_kind)
	{
	case 0:
		{
			int value = request->m_value;
			if (value == -1)
				goto full;
			if (value >= 1)
				return value;
			return 1;
		}
	case 1:
	case 4:
		return (kind->m_flag & 1) ? 1000000 : 1;
	case 3:
full:
		return 1000000;
	default:
		return 1;
	}
}


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

extern "C" __declspec(dllimport) int __stdcall AIL_stream_loop_count(void *stream);
class AudioEventRTS {
public:
    char m_pad00[8];
    Rva006990E0Kind *m_eventInfo;
    char m_pad0c[8];
    AsciiString m_eventName;
    char m_pad18[0x28-0x18];
    int dword28;
    char m_pad2c[0x64-0x2c];
    unsigned int dword64;
    Rva006990E0Kind *getEventInfo() const { return m_eventInfo; }
    int getDword28() const { return dword28; }
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
    void *getHandle() const { return m_milesHandle; }
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


typedef _STL::deque<PlayingAudioRef> PlayingAudioDeque006A6080;
class MilesAudioManager {
public:
    bool rva006A6080(const AsciiString &name, int threshold, int index, unsigned int layer);
private:
    char m_pad00[0x95c];
    void *m_mutex;
    char m_pad960[0x9d0-0x960];
    PlayingAudioList m_playingStreams;
    PlayingAudioDeque006A6080 m_cells[6];
};

bool MilesAudioManager::rva006A6080(const AsciiString &name, int threshold, int index, unsigned int layer)
{
    MilesAudioScopedMutex guard(m_mutex);
    PlayingAudioList::iterator listIt;
    PlayingAudioRef playing;
    for (listIt = m_playingStreams.begin(); listIt != m_playingStreams.end(); ++listIt) {
        playing = *listIt;
        if (playing) {
            AudioEventRTS *event = playing->m_audioEventRTS;
            if (event->getEventInfo()->m_kind == 0 && event->dword28 == index && event->dword64 == layer &&
                event->m_eventName.StringBase<char>::compare(name) == 0) {
                if (rva006990E0((Rva006990E0Request *)event) - AIL_stream_loop_count(playing->m_milesHandle) >= threshold) return true;
            }
        }
    }
    PlayingAudioDeque006A6080 &cell = m_cells[layer + index * 2];
    for (PlayingAudioDeque006A6080::iterator it = cell.begin(); it != cell.end(); ++it) {
        playing = *it;
        if (playing) {
            AudioEventRTS *event = playing->m_audioEventRTS;
            if (event->getEventInfo()->m_kind == 0 && event->getDword28() == index &&
                event->m_eventName.compare(name) == 0) {
                if (rva006990E0((Rva006990E0Request *)event) - AIL_stream_loop_count(playing->getHandle()) >= threshold) return true;
            }
        }
    }
    return false;
}

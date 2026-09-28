// ?rva006A59F0@MilesAudioManager@@QAEXPAVPlayingAudio@@@Z
// partial score=0.26 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline
// stlport
//
// Retail 0x006A59F0 (885 B, ret 4; jump table to +0x388): the non-virtual
// MilesAudioManager member the ledger pins as rva006A59F0 (ILT 0x0002669D).
// The matched callers MilesAudioManager::rva006A8DC0 (vtable 0x0111C0C0 slot
// 20) and rva006A5E60 hand it one PlayingAudio.  It is Zero Hour's
// releaseMilesHandles widened by BFME: sound-effect counters (+0x610/+0x614)
// or the channel mask at +0x624 first, a script flag named by the event's
// +0x6c string, then per PlayingAudio type the Miles callback/stop, the
// handle map lookup under the Miles mutex (maps at +0xb08/+0xb1c/+0xb30 of
// the matched constructor's layout) and the free-handle lists at +0x9c0 and
// +0x9c4; type 3 clears a +0xb44 slot under the manager mutex.  No caller
// proves a semantic name, so the address token stays.
#define _STLP_NO_EXCEPTIONS 1
#include "StringInline.h"
#include <hash_map>
#include <list>

typedef int Int;
typedef bool Bool;

typedef struct _SAMPLE *HSAMPLE;
typedef struct h3DPOBJECT *H3DSAMPLE;
typedef struct _STREAM *HSTREAM;

extern "C" {
__declspec(dllimport) void *__stdcall AIL_register_EOS_callback(HSAMPLE sample, void *callback);
__declspec(dllimport) void *__stdcall AIL_register_3D_EOS_callback(H3DSAMPLE sample, void *callback);
__declspec(dllimport) void *__stdcall AIL_register_stream_callback(HSTREAM stream, void *callback);
__declspec(dllimport) void __stdcall AIL_stop_sample(HSAMPLE sample);
__declspec(dllimport) void __stdcall AIL_stop_3D_sample(H3DSAMPLE sample);
__declspec(dllimport) void __stdcall AIL_close_stream(HSTREAM stream);
__declspec(dllimport) void __stdcall AIL_lock_mutex(void);
__declspec(dllimport) void __stdcall AIL_unlock_mutex(void);
__declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
__declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
}

enum PlayingAudioType
{
	PAT_Sample,
	PAT_3DSample,
	PAT_Stream,
	PAT_Slot,
	PAT_INVALID
};

// upstream layout hint: ZH AudioEventInfo; BFME offsets are this body's.
class AudioEventInfo
{
public:
	char m_pad000[0x84];
	Int m_soundType84;
	char m_pad088[4];
	void *m_begin8c;
	void *m_end90;
};

class AudioEventRTS
{
public:
	const AudioEventInfo *getAudioEventInfo(void) const { return m_eventInfo; }

	char m_pad000[8];
	const AudioEventInfo *m_eventInfo;
	char m_pad00c[0x28 - 0xc];
	Int m_channel28;
	char m_pad02c[0x6c - 0x2c];
	AsciiString m_flagName6c;
};

class PlayingAudio
{
public:
	virtual ~PlayingAudio();

	long m_refCount;
	union
	{
		HSAMPLE m_sample;
		H3DSAMPLE m_3DSample;
		HSTREAM m_stream;
		Int m_handleKey;
		Int m_slot;
	};
	Int m_type;
	Int m_status;
	AudioEventRTS *m_audioEventRTS;
	char m_pad018[0x3d - 0x18];
	Bool m_setsFlag3d;
};

class ScriptEngine
{
	friend class MilesAudioManager;

protected:
	Bool *bfmeFlagForWrite(AsciiString name);
};

extern ScriptEngine *TheScriptEngine;

// Callees whose ledger names carry their own address-derived classes.
class Rva00695DC0Counter { public: void decrement(void); };
class Rva00695DE0Counter { public: void decrement(void); };
class Rva0069F4D0Owner { public: void notify(void *arg, int index) throw(); };
class Rva006A9800Elem
{
public:
	unsigned char byte_0;
	unsigned char pad_1[3];
	H3DSAMPLE ptr_4;
	unsigned char pad_8[0x38];
};
class Rva006A9800This { public: void rvaElemClose(Rva006A9800Elem *elem); };

// Map payloads keep the address-derived names of the matched erase bodies.
struct Gen_t_006a3b20_p12cd { PlayingAudio *m_playing; Int m_4; Int m_8; };
struct Gen_t_006a3bf0_p12cd { PlayingAudio *m_playing; Int m_4; Int m_8; };
struct Gen_t_006a3cc0_p12cd { PlayingAudio *m_playing; Int m_4; Int m_8; };

// Miles global mutex held for a scope, as in QueueAudioReference006A2B50.
class Rva006A59F0MilesLock
{
public:
	Rva006A59F0MilesLock() { AIL_lock_mutex(); m_locked = true; }
	~Rva006A59F0MilesLock() { if (m_locked) AIL_unlock_mutex(); }
	void unlock() { AIL_unlock_mutex(); m_locked = false; }

private:
	Bool m_locked;
};

// Manager mutex hold; out-of-line destructor 0x006915E0 elsewhere.
class Rva006915E0
{
public:
	Rva006915E0(void *mutex) : m_held(false)
	{
		m_mutex = mutex;
		if (WaitForSingleObject(mutex, 0xFFFFFFFF) != 0x102)
			m_held = true;
	}
	~Rva006915E0() { release(); }
	void release()
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = false;
		}
	}

private:
	void *m_mutex;
	Bool m_held;
};

class MilesAudioManager
{
public:
	void rva006A59F0(PlayingAudio *release);

private:
	char m_pad000[0x624];
	unsigned int m_channelMask624;
	char m_pad628[0x95c - 0x628];
	void *m_mutex;
	char m_pad960[0x9c0 - 0x960];
	_STL::list<HSAMPLE> m_availableSamples;
	_STL::list<H3DSAMPLE> m_available3DSamples;
	char m_pad9c8[0xb08 - 0x9c8];
	_STL::hash_map<Int, Gen_t_006a3b20_p12cd> m_hashb08;
	_STL::hash_map<Int, Gen_t_006a3bf0_p12cd> m_hashb1c;
	_STL::hash_map<Int, Gen_t_006a3cc0_p12cd> m_hashb30;
	Rva006A9800Elem *m_slotsB44;
};

void MilesAudioManager::rva006A59F0(PlayingAudio *release)
{
	if (release->m_audioEventRTS && release->m_audioEventRTS->getAudioEventInfo())
	{
		switch (release->m_audioEventRTS->getAudioEventInfo()->m_soundType84)
		{
		case 2:
			if (release->m_type == PAT_Sample)
			{
				if (release->m_sample)
					((Rva00695DC0Counter *)this)->decrement();
			}
			else if (release->m_type == PAT_3DSample)
			{
				if (release->m_3DSample)
					((Rva00695DE0Counter *)this)->decrement();
			}
			break;
		case 1:
			m_channelMask624 &= ~(1 << release->m_audioEventRTS->m_channel28);
			break;
		}
		if (release->m_setsFlag3d)
			*TheScriptEngine->bfmeFlagForWrite(release->m_audioEventRTS->m_flagName6c) = true;
	}

	Bool released = false;
	switch (release->m_type)
	{
	case PAT_Sample:
		if (release->m_sample)
		{
			AIL_register_EOS_callback(release->m_sample, 0);
			AIL_stop_sample(release->m_sample);
			Rva006A59F0MilesLock lock;
			_STL::hash_map<Int, Gen_t_006a3b20_p12cd>::iterator it = m_hashb08.find(release->m_handleKey);
			if (it == m_hashb08.end())
			{
				lock.unlock();
				m_availableSamples.push_back(release->m_sample);
			}
			else if (it->second.m_playing != release)
			{
				lock.unlock();
				m_availableSamples.push_back(release->m_sample);
			}
			else
			{
				m_hashb08.erase(it);
				m_availableSamples.push_back(release->m_sample);
			}
			released = true;
		}
		break;
	case PAT_3DSample:
		if (release->m_3DSample)
		{
			AIL_register_3D_EOS_callback(release->m_3DSample, 0);
			AIL_stop_3D_sample(release->m_3DSample);
			Rva006A59F0MilesLock lock;
			_STL::hash_map<Int, Gen_t_006a3bf0_p12cd>::iterator it = m_hashb1c.find(release->m_handleKey);
			if (it == m_hashb1c.end())
				lock.unlock();
			else if (it->second.m_playing != release)
				lock.unlock();
			else
				m_hashb1c.erase(it);
			m_available3DSamples.push_back(release->m_3DSample);
			released = true;
		}
		break;
	case PAT_Stream:
		if (release->m_stream)
		{
			AIL_register_stream_callback(release->m_stream, 0);
			AIL_close_stream(release->m_stream);
			Rva006A59F0MilesLock lock;
			_STL::hash_map<Int, Gen_t_006a3cc0_p12cd>::iterator it = m_hashb30.find(release->m_handleKey);
			if (it == m_hashb30.end())
				lock.unlock();
			else if (it->second.m_playing != release)
				lock.unlock();
			else
				m_hashb30.erase(it);
			released = true;
		}
		break;
	case PAT_Slot:
		{
			Rva006915E0 lock(m_mutex);
			m_slotsB44[release->m_slot].byte_0 = 0;
		}
		AIL_stop_3D_sample(m_slotsB44[release->m_slot].ptr_4);
		((Rva006A9800This *)this)->rvaElemClose(&m_slotsB44[release->m_slot]);
		released = true;
		break;
	}
	release->m_type = PAT_INVALID;
	if (released)
	{
		AudioEventRTS *event = release->m_audioEventRTS;
		if (event && event->m_eventInfo && event->m_eventInfo->m_begin8c != event->m_eventInfo->m_end90)
			((Rva0069F4D0Owner *)this)->notify((void *)&event->m_eventInfo, event->m_channel28);
	}
}

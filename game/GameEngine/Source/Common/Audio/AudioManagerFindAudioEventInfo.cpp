// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// ?findAudioEventInfo@AudioManager@@UBE?AVAudioEventInfoRef@@ABVAsciiString@@@Z
// Retail 0x006AEA10: lock the BFME audio-event table and return a retained
// AudioEventInfoRef for one event name (empty when the name is unknown).
// Identity: the body's ILT 0x000153D9 sits in the AudioManager vtable
// (head 0x0111C0C0, installed by 0x006ACF50 and 0x006B0E00) at +0x118,
// right after newAudioEventInfo (+0x110, 0x006AE710) and addAudioEventInfo
// (+0x114, 0x006AE910) -- the Zero Hour GameAudio.h declaration order -- and
// the matched addAudioEventInfo calls +0x118 where Zero Hour calls
// findAudioEventInfo (const, as in Zero Hour GameAudio.h).  The returned
// handle has a destructor, which is why retail zeroes the return-value
// construction flag before the mutex guard.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "ascii_string.h"

#include "../../../Include/Common/ScalarTypes/Source/Long.h"

namespace rts
{
template <class T>
struct equal_to
{
	bool operator()(const T &left, const T &right) const { return left == right; }
};

template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);
extern "C" __declspec(dllimport) Long __stdcall InterlockedIncrement(
	Long volatile *addend);
extern "C" __declspec(dllimport) Long __stdcall InterlockedDecrement(
	Long volatile *addend);

class Rva006AEA10MutexGuard
{
public:
	Rva006AEA10MutexGuard(void *handle)
	{
		m_owned = 0;
		m_handle = handle;
		if (WaitForSingleObject(handle, 0xFFFFFFFF) != 0x102)
			m_owned = 1;
	}

	~Rva006AEA10MutexGuard()
	{
		if (m_owned)
			ReleaseMutex(m_handle);
	}

private:
	void *m_handle;
	char m_owned;
};

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	Long m_refCount;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_info(0) {}
	AudioEventInfoRef(AudioEventInfo *info) : m_info(info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	~AudioEventInfoRef(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	AudioEventInfo *m_info;
};

// Zero Hour AudioEventInfoHash (GameAudio.h); see AudioEventInfoHash.cpp.
typedef _STL::hash_map<AsciiString, AudioEventInfo *, rts::hash<AsciiString>,
	rts::equal_to<AsciiString> > AudioEventInfoHash;

struct Rva006AEA10Node
{
	Rva006AEA10Node *m_next;
	AsciiString m_key;
	AudioEventInfo *m_info;
};

class AudioManager
{
public:
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &eventName) const;

private:
	char m_pad04[0x6c];
	AudioEventInfoHash m_events;
	char m_pad95c[0x95c - 0x70 - sizeof(AudioEventInfoHash)];
	void *m_mutex;
};

AudioEventInfoRef AudioManager::findAudioEventInfo(const AsciiString &eventName) const
{
	Rva006AEA10MutexGuard guard(m_mutex);
	AudioEventInfoHash::const_iterator it;
	it = m_events.find(eventName);
	Rva006AEA10Node *node = *(Rva006AEA10Node **)&it;
	if (node == 0)
		return AudioEventInfoRef();
	return AudioEventInfoRef(node->m_info);
}

// ?findAudioEventInfo@AudioManager@@UBE?AVAudioEventInfoRef@@PBVAsciiString@@@Z
// partial score=0.14 date=2026-09-21
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x006AEAE0, 401 bytes.
//
// Same AudioManager mutex-at-+0x95c / hash-map-at-+0x70 layout already
// proven at Code/GameEngine/Source/Common/Audio/AudioManagerAddAudioEventInfo.cpp
// (retail 0x006AE910). That neighbour's addAudioEventInfo calls this virtual
// (findAudioEventInfo) to check for an existing entry before inserting; this
// body is the lookup itself: lock the mutex, hash_map::find(eventName), ref-
// count the hit via InterlockedIncrement, and return an AudioEventInfoRef.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "ascii_string.h"

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

bool operator==(const AsciiString &left, const AsciiString &right);

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

struct AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	AsciiString m_audioName;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(void) : m_info(0) { }

	~AudioEventInfoRef(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	AudioEventInfo *m_info;
};

class AudioManagerMutex
{
public:
	__forceinline AudioManagerMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	__forceinline ~AudioManagerMutex(void)
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

typedef _STL::hash_map<AsciiString, AudioEventInfo *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > AudioEventInfoHash;

class AudioEventInfoMap : public AudioEventInfoHash
{
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString *eventName) const;

private:
	char m_pad004[0x6c];
	AudioEventInfoMap m_allAudioEventInfo;
	char m_pad084[0x95c - 0x84];
	void *m_mutex;
};

// ?findAudioEventInfo@AudioManager@@UBE?AVAudioEventInfoRef@@PBVAsciiString@@@Z
AudioEventInfoRef AudioManager::findAudioEventInfo(const AsciiString *eventName) const
{
	AudioManagerMutex guard(((AudioManager *)this)->m_mutex);

	AudioEventInfoRef result;

	AudioEventInfoMap *map = (AudioEventInfoMap *)&m_allAudioEventInfo;
	AudioEventInfoMap::iterator it = map->find(*eventName);
	if (it != map->end())
	{
		AudioEventInfo *info = (*it).second;
		result.m_info = info;
		InterlockedIncrement(&info->m_refCount);
	}

	return result;
}

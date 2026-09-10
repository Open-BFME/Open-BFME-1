// ?d_006ae910@@YAXXZ
// partial score=0.97 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

class AsciiString
{
public:
	void *m_data;
};

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const;
};
}

bool operator==(const AsciiString &left, const AsciiString &right);

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

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
	int m_padding;
	void *m_mutex;
	unsigned char m_held;
};

extern void j_00027e03(void);

typedef _STL::hash_map<AsciiString, AudioEventInfo *, rts::hash<AsciiString>,
	_STL::equal_to<AsciiString> > AudioEventInfoHash;

class AudioEventInfoMap : public AudioEventInfoHash
{
public:
	AudioEventInfo *&operator[](const AsciiString &key)
	{
		typedef AudioEventInfo *&(AudioEventInfoMap::*Lookup)(const AsciiString &);
		union LookupBits
		{
			void (*freeFunction)(void);
			Lookup memberFunction;
		} lookup;
		lookup.freeFunction = j_00027e03;
		return (this->*lookup.memberFunction)(key);
	}
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
	virtual void slot68(); virtual void slot69();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString *eventName) const;
	virtual void addAudioEventInfo(AudioEventInfo *newEvent);

private:
	char m_pad004[0x6c];
	AudioEventInfoMap m_allAudioEventInfo;
	char m_pad084[0x630 - 0x84];
	unsigned char m_infoDirty;
	char m_pad631[0x95c - 0x631];
	void *m_mutex;
};

void AudioManager::addAudioEventInfo(AudioEventInfo *newEvent)
{
	AudioManagerMutex guard(m_mutex);
	{
		AudioEventInfoRef eventInfo = findAudioEventInfo(&newEvent->m_audioName);
		if (!eventInfo.m_info)
		{
			m_allAudioEventInfo[newEvent->m_audioName] = newEvent;
			m_infoDirty = 0;
		}
	}
}

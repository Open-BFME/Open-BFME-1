// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
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

class AudioEventRTS
{
public:
	virtual ~AudioEventRTS();

	AsciiString m_filenameToLoad;
	mutable AudioEventInfo *m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
	AudioEventInfo *getAudioEventInfo(void) const { return m_eventInfo; }
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

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

	virtual void getInfoForAudioEvent(const AudioEventRTS *eventToFindAndFill) const;

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

extern void j_0000b4e7();

void AudioManager::getInfoForAudioEvent(const AudioEventRTS *eventToFindAndFill) const
{
	AudioManagerMutex guard(m_mutex);
	if (!eventToFindAndFill)
		return;
	if (eventToFindAndFill->getAudioEventInfo())
		return;

	AudioEventInfoRef eventInfo = findAudioEventInfo(&eventToFindAndFill->m_eventName);
	typedef void (AudioEventRTS::*SetAudioEventInfo)(AudioEventInfoRef *);
	union SetAudioEventInfoBits
	{
		void (*freeFunction)(void);
		SetAudioEventInfo memberFunction;
	} setter;
	setter.freeFunction = j_0000b4e7;
	(const_cast<AudioEventRTS *>(eventToFindAndFill)->*setter.memberFunction)(&eventInfo);
}

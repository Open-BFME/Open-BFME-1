// ?addAudioEventEx@AudioManager@@QAEIPBVAudioEventRTS@@HHH@Z
// partial score=0.55 date=2026-09-09
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// Scratch reconstruction for retail 0x006B9500.  This file is deliberately
// outside Code/; it is only an inner-loop compiler experiment.

typedef unsigned int AudioHandle;

class AsciiString
{
public:
	struct Data
	{
		int references;
		unsigned short length;
		unsigned short reserved;
		char text[1];
	};

	int compareNoCase(const char *other) const;
	bool isEmpty(void) const
	{
		return !m_data || m_data->length == 0;
	}

	Data *m_data;
};

class AudioEventInfo
{
public:
	virtual void slot00();
	virtual unsigned int getKey(void) const;

	char m_pad08[0x34];
	unsigned char m_flags3c;
	char m_pad3d[0x47];
	unsigned int m_soundType;
};

class AudioEventRTS
{
public:
	void *m_vftable;
	AsciiString m_filenameToLoad;
	AudioEventInfo *m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
	char m_pad18[0x10];
	unsigned int m_timeOfDay;
	char m_pad2c[0x14];
	unsigned char m_flag40;
	unsigned char m_flag41;
	unsigned char m_flag42;
	unsigned char m_uninterruptable;
	char m_pad44[0x1c];
	unsigned char m_completed;
	char m_pad61[0x0f];
};

extern void j_00008a99();

class AudioEventHolder
{
public:
	AudioEventRTS *m_event;

	void release(void)
	{
		typedef void (AudioEventHolder::*Release)(void);
		union
		{
			void (*freeRelease)(void);
			Release memberRelease;
		} call;
		call.freeRelease = ::j_00008a99;
		(this->*call.memberRelease)();
	}

	~AudioEventHolder(void)
	{
		release();
	}
};

class AudioTimeMap
{
public:
	void *m_end;
};

struct AudioVolumeValue
{
	char m_pad00[8];
	AsciiString *m_name;
	float m_value;
};

struct AudioVolumeNode
{
	AudioVolumeNode *m_next;
	AudioVolumeValue *m_value;
};

class AudioVolumeList
{
public:
	AudioVolumeNode *m_head;
};

class AudioRequestList
{
public:
	char m_bytes[0x20];
};

struct AudioRequestScratch
{
	char m_pad00[8];
	unsigned int m_flags;
	unsigned int m_handle;
};

class AudioManager;

extern void j_00003071();
extern void j_00023321();
extern void j_00015a69();
extern void j_00041006();
extern void j_0001079e();
extern void j_000317aa();
extern void j_00001005();
extern void j_00008a99();
extern void j_0001e961();
extern void j_00001eb5();
extern void j_00029695();
extern void j_0002c5cf();
extern void j_00044e27();
extern void j_0003bead();
extern void j_0003834d();
extern void j_0003e63a();
extern void j_0000f9e8();
extern void j_000298e8();
extern void j_0000bd75();
extern void j_00007ce3();
extern void j_0001ae2e();

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class AudioManagerMutex
{
public:
	AudioManagerMutex(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xffffffffUL) != 0x102UL)
			m_held = 1;
	}

	~AudioManagerMutex(void)
	{
		if (m_held)
			ReleaseMutex(m_mutex);
	}

	void abort(void)
	{
		if (m_held)
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
	}

	void release(void)
	{
		typedef void (AudioManagerMutex::*Release)(void);
		union
		{
			void (*freeRelease)(void);
			Release memberRelease;
		} call;
		call.freeRelease = ::j_0001e961;
		(this->*call.memberRelease)();
	}

	void *m_mutex;
	unsigned char m_held;
};

class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
	AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
	AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26) AUDIO_SLOT(27)
	AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30) AUDIO_SLOT(31)
	AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42)
#undef AUDIO_SLOT
	virtual void getInfoForAudioEvent(const AudioEventRTS *event) const;
	virtual void slot44();
	virtual void slot45();
	virtual bool isOn(unsigned int soundClass) const;

	AudioHandle addAudioEventEx(const AudioEventRTS *event, int force,
		int allowLocal, int allowRemote);

	char m_pad004[0x48];
	AudioVolumeList m_adjustedVolumes;
	char m_pad050[0x5d4];
	unsigned int m_audioMask;
	char m_pad628[0x334];
	void *m_mutex;
	char m_pad960[0x38];
	AudioTimeMap m_timeMap[32];
	char m_padA18[0xdc];
	AudioRequestList m_audioRequests;
};

typedef void * (AudioTimeMap::*MapFind)(unsigned int);
typedef unsigned int (AudioManager::*MusicPlay)(const AudioEventRTS *);
typedef void (AudioManager::*MakeEvent)(AudioEventHolder *, const AudioEventRTS *);
typedef void (AudioEventRTS::*SetFlag)(bool);
typedef bool (AudioEventInfo::*Ready)(void) const;

AudioHandle AudioManager::addAudioEventEx(const AudioEventRTS *event, int force,
	int allowLocal, int allowRemote)
{
	register const AudioEventRTS *eventToAdd = event;
	AudioManagerMutex guard(m_mutex);
	AudioManager *manager = this;
	if (eventToAdd->m_eventName.isEmpty() ||
		eventToAdd->m_eventName.compareNoCase("NoSound") == 0)
	{
		guard.abort();
		return 0;
	}

	if (!eventToAdd->m_eventInfo)
	{
		manager->getInfoForAudioEvent(eventToAdd);
		if (!eventToAdd->m_eventInfo)
		{
			guard.abort();
			return 0;
		}
	}

	AudioEventInfo *info = eventToAdd->m_eventInfo;
	unsigned int key = info->getKey();
	AudioTimeMap *map = (AudioTimeMap *)((char *)manager + 0x998 +
		eventToAdd->m_timeOfDay * 12);

	MapFind find;
	union
	{
		void (*freeFind)(void);
		MapFind memberFind;
	} findCall;
	findCall.freeFind = ::j_00003071;
	find = findCall.memberFind;
	if ((map->*find)(key) != map->m_end)
		return 0;

	if (info->m_soundType == 3)
	{
		MusicPlay play;
		union
		{
			void (*freePlay)(void);
			MusicPlay memberPlay;
		} playCall;
		playCall.freePlay = ::j_00023321;
		play = playCall.memberPlay;
		AudioHandle result = (manager->*play)(eventToAdd);
		guard.release();
		return result;
	}

	unsigned int soundClass;
	{
		typedef unsigned int (AudioEventRTS::*GetClass)(void) const;
		union
		{
			void (*freeGetClass)(void);
			GetClass memberGetClass;
		} classCall;
		classCall.freeGetClass = ::j_00015a69;
		soundClass = (eventToAdd->*classCall.memberGetClass)();
	}
	if (!manager->isOn(soundClass))
		return 0;

	if (info->m_soundType == 1 &&
		((1U << eventToAdd->m_timeOfDay) & manager->m_audioMask) != 0)
		return 0;

	AudioEventHolder audioEvent;
	{
		MakeEvent make;
		union
		{
			void (*freeMake)(void);
			MakeEvent memberMake;
		} makeCall;
		makeCall.freeMake = ::j_00041006;
		make = makeCall.memberMake;
		(manager->*make)(&audioEvent, eventToAdd);
	}

	if (force == 1)
	{
		Ready ready;
		union
		{
			void (*freeReady)(void);
			Ready memberReady;
		} readyCall;
		readyCall.freeReady = ::j_00001005;
		ready = readyCall.memberReady;
		if (!((audioEvent.m_event->m_eventInfo->*ready)()))
		{
			guard.release();
			return 4;
		}
	}

	if (!audioEvent.m_event->m_completed)
	{
		if (!audioEvent.m_event->m_playingHandle)
		{
			typedef void (AudioEventRTS::*Advance)(void);
			union
			{
				void (*freeAdvance)(void);
				Advance memberAdvance;
			} advanceCall;
			advanceCall.freeAdvance = ::j_0001079e;
			(audioEvent.m_event->*advanceCall.memberAdvance)();
		}

		unsigned int playingHandle = audioEvent.m_event->m_playingHandle;
		AudioRequestScratch request;
		request.m_flags = (unsigned int)allowRemote;
		request.m_handle = playingHandle;
		AudioRequestList *requests =
			(AudioRequestList *)((char *)manager + 0xaf4);
		typedef bool (AudioRequestList::*Append)(unsigned int *, unsigned int *, int);
		union
		{
			void (*freeAppend)(void);
			Append memberAppend;
		} appendCall;
		appendCall.freeAppend = ::j_000317aa;
		if (!(requests->*appendCall.memberAppend)(
				&request.m_flags, &request.m_handle, allowLocal))
		{
			AudioHandle result = audioEvent.m_event->m_playingHandle;
			return result;
		}
	}

	{
		typedef void (AudioManager::*Prepare)(AudioEventRTS *);
		union
		{
			void (*freePrepare)(void);
			Prepare memberPrepare;
		} prepareCall;
		prepareCall.freePrepare = ::j_00001eb5;
		(manager->*prepareCall.memberPrepare)(audioEvent.m_event);
	}

	if (!audioEvent.m_event->m_uninterruptable)
	{
		typedef bool (AudioManager::*ShouldPlay)(AudioEventRTS *);
		union
		{
			void (*freeShouldPlay)(void);
			ShouldPlay memberShouldPlay;
		} shouldPlayCall;
		shouldPlayCall.freeShouldPlay = ::j_00029695;
		if (!(manager->*shouldPlayCall.memberShouldPlay)(audioEvent.m_event))
			return 3;
	}

	if (audioEvent.m_event->m_eventInfo->m_flags3c & 0x20)
	{
		typedef void (AudioEventRTS::*SetLogical)(bool);
		union
		{
			void (*freeSetLogical)(void);
			SetLogical memberSetLogical;
		} logicalCall;
		logicalCall.freeSetLogical = ::j_0002c5cf;
		(audioEvent.m_event->*logicalCall.memberSetLogical)(true);
	}

	int soundType = audioEvent.m_event->m_eventInfo->m_soundType;
	bool dispatched;
	if (soundType == 0)
	{
		typedef void (AudioManager::*DispatchMusic)(AudioEventHolder *, int);
		union
		{
			void (*freeDispatch)(void);
			DispatchMusic memberDispatch;
		} dispatchCall;
		dispatchCall.freeDispatch = ::j_00044e27;
		(manager->*dispatchCall.memberDispatch)(&audioEvent, force);
		dispatched = true;
	}
	else
	{
		typedef bool (AudioManager::*DispatchSound)(AudioEventHolder *, int, int);
		union
		{
			void (*freeDispatch)(void);
			DispatchSound memberDispatch;
		} dispatchCall;
		dispatchCall.freeDispatch = ::j_0003bead;
		dispatched = (manager->*dispatchCall.memberDispatch)(
			&audioEvent, allowRemote, force);
	}
	if (!dispatched)
		return 0;

	AudioHandle result = audioEvent.m_event->m_playingHandle;
	guard.release();
	return result;
}

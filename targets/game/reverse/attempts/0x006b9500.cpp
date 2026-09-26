// ?addAudioEventEx@AudioManager@@QAEIPBVAudioEventRTS@@HHH@Z
// partial score=0.65 date=2026-09-15
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// Self-contained audio reconstruction; not a verified conversion.
// ?addAudioEventEx@AudioManager@@QAEIPBVAudioEventRTS@@HHH@Z
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc
// Scratch reconstruction for retail 0x006B9500.  This file is deliberately
// outside Code/; it is only an inner-loop compiler experiment.

typedef unsigned int AudioHandle;

#include "../../Code/Libraries/Source/WWVegas/WWLib/ascii_string.h"

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
		{
			ReleaseMutex(m_mutex);
			m_held = 0;
		}
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
		call.freeRelease = ::j_0003e63a;
		(this->*call.memberRelease)();
	}

	void *m_mutex;
	unsigned char m_held;
};

typedef void * (AudioTimeMap::*MapFind)(unsigned int);
typedef bool (AudioEventInfo::*Ready)(void) const;

struct PendingRequestNode
{
	PendingRequestNode *m_prev;
	PendingRequestNode *m_next;
	void *m_value;
};

struct PendingRequestIterator
{
	PendingRequestNode *m_node;
};

class PendingRequestList
{
public:
	PendingRequestIterator erase(PendingRequestIterator position)
	{
		typedef PendingRequestIterator (PendingRequestList::*Erase)(
			PendingRequestIterator);
		union
		{
			void (*freeErase)(void);
			Erase memberErase;
		} call;
		call.freeErase = ::j_00007ce3;
		return (this->*call.memberErase)(position);
	}

	PendingRequestNode *m_sentinel;
};

struct PendingMapPair
{
	unsigned int m_key;
	unsigned int m_handle;
};

struct PendingMapIterator
{
	void *m_node;
};

struct PendingMapInsertResult
{
	PendingMapIterator m_iterator;
	bool m_inserted;
};

class PendingRequestMap
{
public:
	PendingMapInsertResult insert_unique(const PendingMapPair &value)
	{
		typedef PendingMapInsertResult (PendingRequestMap::*Insert)(
			const PendingMapPair &);
		union
		{
			void (*freeInsert)(void);
			Insert memberInsert;
		} call;
		call.freeInsert = ::j_000317aa;
		return (this->*call.memberInsert)(value);
	}
};

class PendingRequestHandle
{
public:
	void *m_value;

	PendingRequestHandle(const PendingRequestHandle &other)
	{
		typedef PendingRequestHandle *(PendingRequestHandle::*Copy)(
			const PendingRequestHandle &);
		union
		{
			void (*freeCopy)(void);
			Copy memberCopy;
		} call;
		call.freeCopy = ::j_0003834d;
		(this->*call.memberCopy)(other);
	}

	~PendingRequestHandle(void)
	{
		typedef void (PendingRequestHandle::*Destroy)(void);
		union
		{
			void (*freeDestroy)(void);
			Destroy memberDestroy;
		} call;
		call.freeDestroy = ::j_000298e8;
		(this->*call.memberDestroy)();
	}
};

struct PendingRequestRecord
{
	int m_kind;
	AudioEventRTS *m_event;
	unsigned int m_field08;
	PendingRequestHandle m_waitHandle;

	void destroy(void)
	{
		typedef void (PendingRequestRecord::*Destroy)(void);
		union
		{
			void (*freeDestroy)(void);
			Destroy memberDestroy;
		} call;
		call.freeDestroy = ::j_0001ae2e;
		(this->*call.memberDestroy)();
	}
};

extern "C" __declspec(dllimport) void __stdcall Rva01358F30Wait(int interval);
extern void operator delete(void *block);

static unsigned int audio_info_sound_type(const AudioEventInfo *info)
{
	return *(const unsigned int *)((const char *)info + 0x84);
}

static unsigned char audio_info_flags(const AudioEventInfo *info)
{
	return *(const unsigned char *)((const char *)info + 0x3c);
}

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

typedef unsigned int (AudioManager::*MusicPlayAudio)(const AudioEventRTS *);
typedef void (AudioManager::*MakeEventAudio)(AudioEventHolder *,
	const AudioEventRTS *);

static void reacquire_audio_mutex(AudioManagerMutex *guard, void *mutex)
{
	typedef void (AudioManagerMutex::*Acquire)(void *, int);
	union
	{
		void (*freeAcquire)(void);
		Acquire memberAcquire;
	} call;
	call.freeAcquire = ::j_0000f9e8;
	(guard->*call.memberAcquire)(mutex, -1);
}

static void process_audio_request(AudioManager *manager,
	PendingRequestRecord *request, unsigned char *result)
{
	typedef void (AudioManager::*Process)(PendingRequestRecord *,
		unsigned char *, int);
	union
	{
		void (*freeProcess)(void);
		Process memberProcess;
	} call;
	call.freeProcess = ::j_0000bd75;
	(manager->*call.memberProcess)(request, result, 0);
}

AudioHandle AudioManager::addAudioEventEx(const AudioEventRTS *event, int force,
	int allowLocal, int allowRemote)
{
	AudioManager *manager = this;
	void *mutex = manager->m_mutex;
	AudioManagerMutex guard(mutex);
	const AudioEventRTS *eventToAdd = event;
	if (eventToAdd->m_eventName.isEmpty() ||
		eventToAdd->m_eventName.compareNoCase("NoSound") == 0)
	{
		guard.abort();
		return 1;
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
		return 1;

	if (audio_info_sound_type(eventToAdd->m_eventInfo) == 3)
	{
		MusicPlayAudio play;
		union
		{
			void (*freePlay)(void);
			MusicPlayAudio memberPlay;
		} playCall;
		playCall.freePlay = ::j_00023321;
		play = playCall.memberPlay;
		AudioHandle result = (manager->*play)(eventToAdd);
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
		return 1;

	if (audio_info_sound_type(eventToAdd->m_eventInfo) == 1 &&
		((1U << eventToAdd->m_timeOfDay) & manager->m_audioMask) != 0)
		return 1;

	AudioEventHolder audioEvent;
	{
		MakeEventAudio make;
		union
		{
			void (*freeMake)(void);
			MakeEventAudio memberMake;
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
			return 4;
		}

		if (!*(unsigned int *)((char *)audioEvent.m_event + 0x60))
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

		PendingMapPair requestValue;
		requestValue.m_key = (unsigned int)allowRemote;
		requestValue.m_handle = audioEvent.m_event->m_playingHandle;
		PendingRequestMap *requests =
			(PendingRequestMap *)((char *)manager + 0xaf4);
		typedef PendingMapInsertResult (PendingRequestMap::*Insert)(
			const PendingMapPair &);
		union
		{
			void (*freeInsert)(void);
			Insert memberInsert;
		} insertCall;
		insertCall.freeInsert = ::j_000317aa;
		PendingMapInsertResult inserted =
			(requests->*insertCall.memberInsert)(requestValue);
		if (!inserted.m_inserted)
		{
			unsigned int result = *(unsigned int *)(
				(char *)inserted.m_iterator.m_node + 0x14);
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

	if (audio_info_flags(audioEvent.m_event->m_eventInfo) & 0x20)
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

	int soundType = audio_info_sound_type(eventToAdd->m_eventInfo);
	bool dispatched;
	if (soundType == 0)
	{
		typedef bool (AudioManager::*DispatchMusic)(AudioEventHolder *, int);
		union
		{
			void (*freeDispatch)(void);
			DispatchMusic memberDispatch;
		} dispatchCall;
		dispatchCall.freeDispatch = ::j_00044e27;
		dispatched = (manager->*dispatchCall.memberDispatch)(&audioEvent, force);
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
			&audioEvent, force, allowLocal);
	}
	if (!dispatched)
		return 1;

	unsigned int playingHandle = audioEvent.m_event->m_playingHandle;
	if (!allowLocal)
	{
		PendingRequestList *pending =
			(PendingRequestList *)((char *)manager + 0x4c);
	restart_requests:;
		PendingRequestNode *cursor = pending->m_sentinel;
		PendingRequestNode *end = cursor->m_prev;
		for (;;)
		{
			PendingRequestNode *node = cursor->m_next;
			if (cursor == end)
				break;

			PendingRequestRecord *request =
				(PendingRequestRecord *)node->m_value;
			if (request->m_kind == 0 && request->m_event == audioEvent.m_event)
			{
				PendingRequestHandle *waitHandle =
					(PendingRequestHandle *)((char *)request + 0xc);
				if (waitHandle->m_value)
				{
					PendingRequestHandle waiting(*waitHandle);
					guard.release();
					while (waiting.m_value &&
						!*(unsigned char *)((char *)waiting.m_value + 0x41) &&
						!*(unsigned char *)((char *)waiting.m_value + 0x42))
						Rva01358F30Wait(1);
					reacquire_audio_mutex(&guard, mutex);
					goto restart_requests;
				}

				unsigned char processResult = 1;
				typedef void (AudioManager::*Process)(PendingRequestRecord *,
					unsigned char *, int);
				union
				{
					void (*freeProcess)(void);
					Process memberProcess;
				} processCall;
				processCall.freeProcess = ::j_0000bd75;
				(manager->*processCall.memberProcess)(request, &processResult, 0);
				if (processResult)
				{
					PendingRequestIterator position;
					position.m_node = node;
					typedef PendingRequestIterator (PendingRequestList::*Erase)(
						PendingRequestIterator);
					union
					{
						void (*freeErase)(void);
						Erase memberErase;
					} eraseCall;
					eraseCall.freeErase = ::j_00007ce3;
					(pending->*eraseCall.memberErase)(position);
					if (request)
					{
						request->destroy();
						operator delete(request);
					}
				}
				break;
			}
			cursor = node;
		}
	}

	return playingHandle;
}

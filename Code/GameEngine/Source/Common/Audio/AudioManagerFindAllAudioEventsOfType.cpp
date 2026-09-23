// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/stringinline
// stlport

// ?findAllAudioEventsOfType@AudioManager@@ -- retail 0x006AEAE0, 401 bytes.
//
// AudioManager vtable 0x0111C0C0 slot 80 (+0x140) holds ILT 0x0002E785, which
// jumps here; slot 69 is addAudioEventInfo (0x006AE910) and slot 70 is the
// findAudioEventInfo that body calls through [eax+0x118]. The body is the Zero
// Hour AudioManager::findAllAudioEventsOfType: under the mutex at +0x95c it walks
// m_allAudioEventInfo (+0x70) and appends every entry whose m_soundType (+0x84,
// as AudioEventRTS::adjustForLocalization at 0x000B3730 reads it) equals the
// requested type. BFME's vector holds refcounted handles, so the append bumps
// m_refCount through the 4-byte-element _M_insert_overflow at 0x000BD3B0.
//
// begin() is reached through ILT 0x0001BA18, whose body 0x006A0320 is ICF-shared
// with another hashtable instantiation, so the call is spelled by that thunk.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <vector>

#include "StringInline.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(
	void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

enum AudioType
{
	AT_Music = 0
};

namespace rts
{
template <class T>
struct hash
{
	unsigned int operator()(T value) const
	{
		const char *text = value.str();
		unsigned int result = 0;
		for (; *text; ++text)
			result = 5 * result + *text;
		return result;
	}
};
}

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
	char m_pad00c[0x84 - 0x0c];
	AudioType m_soundType;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef(AudioEventInfo *info) : m_info(info)
	{
		if (m_info)
			InterlockedIncrement(&m_info->m_refCount);
	}

	AudioEventInfoRef(const AudioEventInfoRef &other) : m_info(other.m_info)
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

// The element type as the ledger names the vector's _M_insert_overflow
// (0x000BD3B0): an AudioEventInfoRef by its copy (store + InterlockedIncrement)
// and its destroy (InterlockedDecrement + deleting destructor).
struct Rva000BD3B0Element : public AudioEventInfoRef
{
	Rva000BD3B0Element(AudioEventInfo *info) : AudioEventInfoRef(info) { }
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

extern void j_0001ba18(void);

class AudioEventInfoMap : public AudioEventInfoHash
{
public:
	iterator begin(void)
	{
		typedef void (AudioEventInfoMap::*Begin)(iterator *result);
		union BeginBits
		{
			void (*freeFunction)(void);
			Begin memberFunction;
		} first;
		first.freeFunction = j_0001ba18;
		iterator result;
		(this->*first.memberFunction)(&result);
		return result;
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
	virtual void slot68();
	virtual void addAudioEventInfo(AudioEventInfo *newEvent);
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString *eventName) const;
	virtual void slot71(); virtual void slot72(); virtual void slot73(); virtual void slot74();
	virtual void slot75(); virtual void slot76(); virtual void slot77(); virtual void slot78();
	virtual void slot79();
	virtual void findAllAudioEventsOfType(AudioType audioType,
		_STL::vector<Rva000BD3B0Element> &allEvents);

private:
	char m_pad004[0x6c];
	AudioEventInfoMap m_allAudioEventInfo;
	char m_pad084[0x95c - 0x84];
	void *m_mutex;
};

void AudioManager::findAllAudioEventsOfType(AudioType audioType,
	_STL::vector<Rva000BD3B0Element> &allEvents)
{
	AudioManagerMutex guard(m_mutex);
	AudioEventInfoMap::iterator it;
	for (it = m_allAudioEventInfo.begin(); it != m_allAudioEventInfo.end(); ++it)
	{
		AudioEventInfo *audioEvent = (*it).second;
		if (audioEvent->m_soundType == audioType)
			allEvents.push_back(audioEvent);
	}
}

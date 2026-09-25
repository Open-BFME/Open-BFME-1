// ?d_006a9ce0@@YAXXZ
// partial score=0.345 date=2026-09-25
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>
#include <deque>
#include <vector>

struct BfmeAsciiStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

#include "ascii_string.h"

typedef unsigned int AudioHandle;
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);

class Rva006A9CE0AudioEventInfo
{
public:
	virtual void v00();
	virtual const AsciiString &getAudioName() const;
};

class AudioEventRTS
{
public:
	const AsciiString &getEventName() const { return m_info->getAudioName(); }
	~AudioEventRTS();

private:
	char m_pad000[8];
	Rva006A9CE0AudioEventInfo *m_info;
	char m_pad00c[0x28 - 0x0c];
	public:
	int m_audioType;
	private:
	char m_pad02c[0x70 - 0x2c];
};

class Rva00698DD0Base
{
public:
	Rva00698DD0Base &operator=(const Rva00698DD0Base &other);

private:
	char m_pad[0x70];
};

class Rva0069C9D0Element : public Rva00698DD0Base
{
public:
	Rva0069C9D0Element &operator=(const Rva0069C9D0Element &other)
	{
		Rva00698DD0Base::operator=(other);
		m_word70 = other.m_word70;
		m_byte74 = other.m_byte74;
		return *this;
	}

	const AsciiString &getEventName() const
	{
		return reinterpret_cast<const AudioEventRTS *>(this)->getEventName();
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
	char m_pad008[0x14 - 8];
	AudioEventRTS *m_audioEventRTS;
};

class ThingRef
{
public:
	ThingRef(void) : m_ptr(0) {}

	~ThingRef(void)
	{
		if (m_ptr)
			m_ptr->Release_Ref();
	}

	ThingRef &operator=(const ThingRef &other)
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

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

class BfmeHostESG
{
public:
	~BfmeHostESG();
	unsigned char m_head[4];
	AudioEventRTS *m_event;
	unsigned int m_hash;
	unsigned char m_member[4];
};

typedef BfmeHostESG Rva006A0810Key;

class Rva006A0810Table;

struct Rva006A0810Node
{
	Rva006A0810Node *m_next;
	Rva006A0810Key *m_key;
};

struct Rva006A0810Buckets
{
	Rva006A0810Node **m_start;
	Rva006A0810Node **m_finish;
	Rva006A0810Node **m_storageEnd;

	unsigned int size(void) const { return (unsigned int)(m_finish - m_start); }
	Rva006A0810Node **begin(void) { return m_start; }
	Rva006A0810Node *&operator[](unsigned int slot) { return m_start[slot]; }
};

struct Rva006A0810Iterator
{
	Rva006A0810Node *m_value;
	Rva006A0810Table *m_owner;

	Rva006A0810Iterator(Rva006A0810Node *value, Rva006A0810Table *owner)
		: m_value(value), m_owner(owner) {}
	Rva006A0810Key *operator*(void) const { return m_value->m_key; }
	Rva006A0810Iterator &operator++(void);
	bool operator!=(const Rva006A0810Iterator &other) const
		{ return m_value != other.m_value; }
};

class Rva006A0810Table
{
public:
	typedef Rva006A0810Iterator iterator;
	iterator begin(void);
	iterator end(void) { return iterator(0, this); }
	void erase(Rva006A0810Node **it);

	unsigned char m_pad0[4];
	Rva006A0810Buckets m_buckets;
	int m_count;
};

inline Rva006A0810Table::iterator Rva006A0810Table::begin(void)
{
	unsigned int slot = 0;
	unsigned int bucketCount = m_buckets.size();
	Rva006A0810Node **bucket = m_buckets.begin();
	Rva006A0810Node *node = 0;
	while (node == 0 && slot < bucketCount)
	{
		node = *bucket++;
		++slot;
	}
	return iterator(node, this);
}

inline Rva006A0810Iterator &Rva006A0810Iterator::operator++(void)
{
	Rva006A0810Node *next = m_value->m_next;
	if (next != 0)
	{
		m_value = next;
	}
	else
	{
		Rva006A0810Key *key = m_value->m_key;
		unsigned int hash = (unsigned int)key;
		if (key != 0)
			hash = key->m_hash;
		unsigned int bucket = hash % m_owner->m_buckets.size();
		unsigned int bucketCount = m_owner->m_buckets.size();
		Rva006A0810Node **buckets = m_owner->m_buckets.begin();
		Rva006A0810Node *node = 0;
		while (node == 0 && ++bucket < bucketCount)
			node = buckets[bucket];
		m_value = node;
	}
	return *this;
}

class Rva006A9CE0MutexGuard
{
public:
	Rva006A9CE0MutexGuard(void *mutex)
	{
		m_held = 0;
		m_mutex = mutex;
		if (WaitForSingleObject(m_mutex, 0xFFFFFFFFu) != 0x102u)
			m_held = 1;
	}

	~Rva006A9CE0MutexGuard(void)
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

struct AudioRequest
{
	int m_request;
	AudioEventRTS *m_pendingEvent;
	bool m_usePendingEvent;
	bool m_requiresCheckForSample;
};

typedef _STL::list<AudioRequest *> AudioRequestList;
typedef _STL::list<ThingRef> PlayingAudioList;
typedef _STL::deque<ThingRef> PlayingAudioDeque;
typedef _STL::vector<Rva0069C9D0Element> Rva006A9CE0EventVector;

class MilesAudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17();
	virtual void rva006A9CE0(const AsciiString &eventName, int audioType);
	void rva006A59F0(PlayingAudio *release);

private:
	char m_pad004[0x4c - 4];
	AudioRequestList m_audioRequests;
	Rva006A0810Table m_requestTable050;
	char m_pad064[0x94 - 0x64];
	Rva006A9CE0EventVector m_eventVectors[3];
	char m_pad0b8[0x95c - 0xb8];
	void *m_mutex;
	char m_pad960[0x9c8 - 0x960];
	PlayingAudioList m_playingSounds;
	PlayingAudioList m_playing3DSounds;
	PlayingAudioList m_playingStreams;
	PlayingAudioDeque m_deques9d4[3][2];
};

void MilesAudioManager::rva006A9CE0(const AsciiString &eventName, int audioType)
{
	Rva006A9CE0MutexGuard guard(m_mutex);

	PlayingAudioList::iterator it;
	ThingRef playing;
	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); )
	{
		playing = *it;
		if (playing && playing->m_audioEventRTS->getEventName().compare(eventName) == 0 &&
			playing->m_audioEventRTS->m_audioType == audioType)
		{
			rva006A59F0(playing);
			it = m_playingSounds.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); )
	{
		playing = *it;
		if (playing && playing->m_audioEventRTS->getEventName().compare(eventName) == 0 &&
			playing->m_audioEventRTS->m_audioType == audioType)
		{
			rva006A59F0(playing);
			it = m_playing3DSounds.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); )
	{
		playing = *it;
		if (playing && playing->m_audioEventRTS->getEventName().compare(eventName) == 0 &&
			playing->m_audioEventRTS->m_audioType == audioType)
		{
			rva006A59F0(playing);
			it = m_playingStreams.erase(it);
		}
		else
		{
			++it;
		}
	}

	for (int j = 0; j < 2; ++j)
	{
		PlayingAudioDeque &queue = m_deques9d4[audioType][j];
		PlayingAudioDeque::iterator qit;
		for (qit = queue.begin(); qit != queue.end(); )
		{
			playing = *qit;
			if (playing && playing->m_audioEventRTS->getEventName().compare(eventName) == 0 &&
				playing->m_audioEventRTS->m_audioType == audioType)
			{
				qit = queue.erase(qit);
			}
			else
			{
				++qit;
			}
		}
	}

	Rva006A9CE0EventVector &events = m_eventVectors[audioType];
	Rva0069C9D0Element *event = events.begin();
	for (; event != events.end(); ++event)
	{
		if (event->getEventName().compare(eventName) == 0)
		{
			events.erase(event);
			reinterpret_cast<AudioEventRTS *>(events.end())->~AudioEventRTS();
		}
	}

	for (Rva006A0810Table::iterator it = m_requestTable050.begin();
		it != m_requestTable050.end(); )
	{
		Rva006A0810Key *key = *it;
		if (key->m_event && key->m_event->getEventName().compare(eventName) == 0)
		{
			Rva006A0810Iterator eraseIt = it;
			++it;
			m_requestTable050.erase(&eraseIt.m_value);
			delete key;
		}
		else
		{
			++it;
		}
	}

	AudioRequestList::iterator ait = m_audioRequests.begin();
	while (ait != m_audioRequests.end())
	{
		AudioRequest *request = *ait;
		if (request->m_request == 0 && request->m_pendingEvent &&
			request->m_pendingEvent->getEventName().compare(eventName) == 0)
		{
			ait = m_audioRequests.erase(ait);
		}
		else
		{
			++ait;
		}
	}
}

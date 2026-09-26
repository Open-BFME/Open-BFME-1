// ?d_006a20d0@@YAXXZ
// partial score=0.19 date=2026-09-23
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A20D0 is the three-argument audio-handle resolver reached by
// the anonymous ILT 0x00008549.  The callers prove its contract and the
// retail body proves the list/vector/deque offsets below.  No public owner or
// method name is proved for this helper, so the address remains in the owner
// type used for the conversion.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <list>

typedef unsigned int AudioHandle;

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
// This barrier makes MSVC issue an IAT call for each increment site.
extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva006A20D0Counted
{
public:
	virtual ~Rva006A20D0Counted();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
		_ReadWriteBarrier();
	}

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
};

class AudioEventRTS
{
public:
	void *m_vftable;
	unsigned char m_pad004[8];
	AudioHandle m_playingHandle;
	unsigned char m_tail010[0x68];
};

class Rva006A20D0PlayingAudio : public Rva006A20D0Counted
{
public:
	void *m_milesHandle;
	int m_type;
	int m_status;
	AudioEventRTS *m_audioEventRTS;
};

class Rva006A20D0PlayingRef
{
public:
	Rva006A20D0PlayingRef(void) : m_pointer(0) {}

	Rva006A20D0PlayingRef(const Rva006A20D0PlayingRef &other) :
		m_pointer(other.m_pointer)
	{
		if (m_pointer != 0)
			m_pointer->Add_Ref();
	}

	~Rva006A20D0PlayingRef(void)
	{
		if (m_pointer != 0)
			m_pointer->Release_Ref();
	}

	Rva006A20D0PlayingRef &operator=(const Rva006A20D0PlayingRef &other)
	{
		if (this != &other)
		{
			if (other.m_pointer != 0)
				InterlockedIncrement(&other.m_pointer->m_refCount);
		_ReadWriteBarrier();
			if (m_pointer != 0)
				if (InterlockedDecrement(&m_pointer->m_refCount) <= 0)
					delete m_pointer;
			m_pointer = other.m_pointer;
		}
		return *this;
	}

	Rva006A20D0PlayingRef &operator=(Rva006A20D0Counted *pointer)
	{
		if (pointer != 0)
			InterlockedIncrement(&pointer->m_refCount);
		_ReadWriteBarrier();
		if (m_pointer != 0)
			if (InterlockedDecrement(&m_pointer->m_refCount) <= 0)
				delete m_pointer;
		m_pointer = pointer;
		return *this;
	}

	operator Rva006A20D0PlayingAudio *(void) const
	{
		return (Rva006A20D0PlayingAudio *)m_pointer;
	}

	Rva006A20D0PlayingAudio *operator->(void) const
	{
		return (Rva006A20D0PlayingAudio *)m_pointer;
	}

	Rva006A20D0Counted *m_pointer;
};

class Rva00087750Ref
{
public:
	Rva00087750Ref(void) : m_pointer(0) {}

	Rva00087750Ref &operator=(const Rva00087750Ref &other);

	Rva00087750Ref &operator=(Rva006A20D0Counted *pointer)
	{
		if (pointer != 0)
			InterlockedIncrement(&pointer->m_refCount);
		_ReadWriteBarrier();
		if (m_pointer != 0)
			if (InterlockedDecrement(&m_pointer->m_refCount) <= 0)
				delete m_pointer;
		m_pointer = pointer;
		return *this;
	}

	Rva00087750Ref &assignInline(const Rva006A20D0PlayingRef &other)
	{
		if (other.m_pointer != 0)
			InterlockedIncrement(&other.m_pointer->m_refCount);
		_ReadWriteBarrier();
		if (m_pointer != 0)
			if (InterlockedDecrement(&m_pointer->m_refCount) <= 0)
				delete m_pointer;
		m_pointer = other.m_pointer;
		return *this;
	}

	Rva006A20D0Counted *m_pointer;
};

typedef _STL::list<Rva006A20D0PlayingRef> Rva006A20D0PlayingList;
typedef _STL::deque<Rva006A20D0PlayingRef> Rva006A20D0PlayingDeque;

struct Rva006A20D0EventRecord
{
	void *m_vftable;
	unsigned char m_pad004[8];
	AudioHandle m_playingHandle;
	unsigned char m_tail010[0x68];
};

class Rva006A20D0EventVector
{
public:
	Rva006A20D0EventRecord *begin(void)
	{
		return m_start;
	}

	Rva006A20D0EventRecord *end(void)
	{
		return m_finish;
	}

	Rva006A20D0EventRecord *m_start;
	Rva006A20D0EventRecord *m_finish;
	Rva006A20D0EventRecord *m_endOfStorage;
};

struct Rva006A20D0Pending
{
	void *m_unused;
	AudioEventRTS *m_event;
};

typedef _STL::list<Rva006A20D0Pending *> Rva006A20D0PendingList;

struct SelfPair006A1650
{
	void *m_value;
	void *m_owner;
};

// Retail's unwind map puts `playing` at -0x4c in a 0x40-byte frame.
// The maker writes only the pair's first two pointers. The adjacent bytes
// preserve the eight-byte pair and reproduce the retail frame size.
struct Rva006A1650PairStorage
{
	SelfPair006A1650 m_pair;
	unsigned char m_pad[8];
};

class Rva006A1650Maker
{
public:
	SelfPair006A1650 *make(SelfPair006A1650 *result, void *argument);
};

class Rva006A20D0Owner
{
public:
	virtual void owner00(void);

	bool resolve(AudioHandle handle, AudioEventRTS **eventOut,
		Rva00087750Ref *infoOut);

private:
	char m_pad004[0x4c - 4];
	Rva006A20D0PendingList m_pending;
	char m_pad050[0x94 - 0x50];
	Rva006A20D0EventVector m_events[3];
	char m_pad0b8[0x9c8 - 0xb8];
	Rva006A20D0PlayingList m_playingSounds;
	Rva006A20D0PlayingList m_playing3DSounds;
	Rva006A20D0PlayingList m_playingStreams;
	unsigned char m_audioQueuesStorage[3][2][0x28];
};

// ?resolve@Rva006A20D0Owner@@QAE_NIPAPAVAudioEventRTS@@PAVRva00087750Ref@@@Z
bool Rva006A20D0Owner::resolve(AudioHandle handle,
	register AudioEventRTS **eventOut,
	register Rva00087750Ref *infoOut)
{
	void *nullPointer = 0;
	if (eventOut != nullPointer)
		*eventOut = (AudioEventRTS *)nullPointer;
	if (infoOut != nullPointer)
		*infoOut = (Rva006A20D0Counted *)nullPointer;
	if (handle < 5)
		return false;

	Rva006A20D0PlayingRef playing;
	Rva006A20D0PlayingList::iterator it;

	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); ++it)
	{
		playing = *it;
		if (playing != nullPointer &&
			playing->m_audioEventRTS->m_playingHandle == handle)
		{
			if (eventOut != nullPointer)
				*eventOut = playing->m_audioEventRTS;
			if (infoOut != nullPointer)
				infoOut->operator=(*(const Rva00087750Ref *)
					(const void *)&playing);
			return true;
		}
	}

	for (it = m_playing3DSounds.begin(); it != m_playing3DSounds.end(); ++it)
	{
		playing = *it;
		if (playing != nullPointer &&
			playing->m_audioEventRTS->m_playingHandle == handle)
		{
			if (eventOut != nullPointer)
				*eventOut = playing->m_audioEventRTS;
			if (infoOut != nullPointer)
				infoOut->assignInline(playing);
			return true;
		}
	}

	for (it = m_playingStreams.begin(); it != m_playingStreams.end(); ++it)
	{
		playing = *it;
		if (playing != nullPointer &&
			playing->m_audioEventRTS->m_playingHandle == handle)
		{
			if (eventOut != nullPointer)
				*eventOut = playing->m_audioEventRTS;
			if (infoOut != nullPointer)
				infoOut->assignInline(playing);
			return true;
		}
	}

	Rva006A20D0PlayingDeque *queueGroup =
		(Rva006A20D0PlayingDeque *)((char *)this + 0x9d4);
	Rva006A20D0EventRecord **eventFinish = &m_events[0].m_finish;
	for (unsigned int group = 0; group < 3;
		++group, eventFinish += 3, queueGroup += 2)
	{
		Rva006A20D0EventRecord *eventIt;
		for (eventIt = eventFinish[-1]; eventIt != *eventFinish; ++eventIt)
		{
			if (eventIt->m_playingHandle == handle)
			{
				if (eventOut != nullPointer)
					*eventOut = (AudioEventRTS *)eventIt;
				return true;
			}
		}

		Rva006A20D0PlayingDeque *queue = queueGroup;
		for (unsigned int queueIndex = 0; queueIndex < 2;
			++queueIndex, ++queue)
		{
			Rva006A20D0PlayingDeque::iterator queueIt;
			for (queueIt = queue->begin();
				queueIt != queue->end(); ++queueIt)
			{
				playing = *queueIt;
				if (playing != nullPointer &&
					playing->m_audioEventRTS->m_playingHandle == handle)
				{
					if (eventOut != nullPointer)
						*eventOut = playing->m_audioEventRTS;
					if (infoOut != nullPointer)
						infoOut->assignInline(playing);
					return true;
				}
			}
		}
	}

	Rva006A20D0PendingList::iterator pending = m_pending.begin();
	for (; pending != m_pending.end(); ++pending)
	{
		Rva006A20D0Pending *entry = *pending;
		if (entry != nullPointer && entry->m_event != nullPointer &&
			entry->m_event->m_playingHandle == handle)
		{
			if (eventOut != nullPointer)
				*eventOut = entry->m_event;
			return true;
		}
	}

	Rva006A1650PairStorage pairStorage;
	SelfPair006A1650 &pair = pairStorage.m_pair;
	Rva006A1650Maker *maker =
		(Rva006A1650Maker *)((char *)this + 0xb10);
	maker->make(&pair, (void *)handle);
	if (pair.m_value == 0)
		return false;

	if (eventOut != nullPointer)
		*eventOut = *(AudioEventRTS **)((char *)pair.m_value + 4);
	return true;
}

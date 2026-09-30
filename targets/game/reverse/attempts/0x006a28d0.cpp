// ?xferAudioHandle@AudioManager@@UAEXPAVXfer@@PAI@Z
// partial score=0.928 date=2026-09-30
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport

// Open-BFME5: AudioManager::xferAudioHandle, retail 0x006A28D0, 502 bytes.
// The MilesAudioManager vtable at 0x0111C0C0 names this slot 82.  The three
// address-derived helper declarations below retain the retail call contracts
// without claiming identities that are not present in the ledger.
//
// Retail keeps the resolved info and event pointers in ESI/EBP across the
// Xfer call and releases the info without a reload or a second null test.
// MSVC 7.1 does that only when the resolver 0x006A20D0 and the reference
// copy-assign 0x00696810 have visible bodies in the TU (retail shares the
// resolver's TU), so both are defined here, noinline; the resolver body is
// the 0x006A20D0 bank, not a matched body.  The version record sits in its
// own block because retail reuses its slot for the info reference.
// Residue: retail materialises a zero in EBX (state/info stores, pointer
// compares) and keeps the event in EBP; this source keeps the event in EBX.

#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"
#include <deque>
#include <list>

typedef unsigned int AudioHandle;
typedef unsigned char UnsignedByte;

#include "xfer.h"
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
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
		unsigned long status = WaitForSingleObject(m_mutex, 0xFFFFFFFFu);
		if (status != 0x102u)
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

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	virtual ~AudioEventRTS();

	// These two fields are the only AudioEventRTS members this body observes.
	// Keep the intervening layout faithful to the proven 0x70-byte object while
	// leaving its ownership fields opaque to this caller.
	unsigned char m_pad004[8];
	unsigned int m_playingHandle;
	unsigned char m_pad010[0x45 - 0x10];
	unsigned char m_flag45;
	unsigned char m_pad046[0x70 - 0x46];
};

class Rva006AInfo
{
public:
	virtual ~Rva006AInfo();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	char m_pad008[0x34 - 0x08];
	unsigned char m_flag34;
};

class AudioInfo006A28D0Ref {
public:
 AudioInfo006A28D0Ref() : ptr(0) {}
 __forceinline ~AudioInfo006A28D0Ref() { if (ptr) ptr->Release_Ref(); }
 Rva006AInfo *ptr;
};

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
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

	__declspec(noinline) Rva00087750Ref &operator=(const Rva00087750Ref &other)
	{
		if (this != &other)
		{
			if (other.m_pointer)
				InterlockedIncrement(&other.m_pointer->m_refCount);
			if (m_pointer)
				m_pointer->Release_Ref();
			m_pointer = other.m_pointer;
		}
		return *this;
	}

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

class MilesAudioManager
{
public:
	virtual void owner00(void);

	bool rva006A20D0(AudioHandle handle, void *eventOutArg, void *infoOutArg);

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

// ?rva006A20D0@MilesAudioManager@@QAE_NIPAX0@Z present-unmatched
__declspec(noinline) bool MilesAudioManager::rva006A20D0(AudioHandle handle, void *eventOutArg, void *infoOutArg)
{
	AudioEventRTS **eventOut = (AudioEventRTS **)eventOutArg;
	Rva00087750Ref *infoOut = (Rva00087750Ref *)infoOutArg;
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

class BfmeSeedTarget;

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);

private:
	char m_bfmePad0[0xC];
	void *m_bfmeField;
};

extern void j_00008549(void);
extern AsciiString TheBfmeCrateNameDefault;

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z=?j_00025306@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")


class AudioManager
{
public:
#define AUDIO_SLOT(n) virtual void audioSlot##n();
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
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68) AUDIO_SLOT(69) AUDIO_SLOT(70) AUDIO_SLOT(71)
	AUDIO_SLOT(72) AUDIO_SLOT(73) AUDIO_SLOT(74) AUDIO_SLOT(75)
	AUDIO_SLOT(76) AUDIO_SLOT(77) AUDIO_SLOT(78) AUDIO_SLOT(79)
	AUDIO_SLOT(80) AUDIO_SLOT(81)
#undef AUDIO_SLOT
	virtual void xferAudioHandle(Xfer *xfer, AudioHandle *handle);

private:
	char m_pad004[0x95c - 4];
	void *m_mutex;
};

void AudioManager::xferAudioHandle(Xfer *xfer, AudioHandle *handle)
{
	{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		*xfer == version;
	}
	if (xfer->IsCRC())
		return;

	if (xfer->IsStoring())
	{
		AudioManagerMutex guard(m_mutex);
		bool accepted;
		AudioInfo006A28D0Ref info;
		AudioEventRTS *event;
		accepted = reinterpret_cast<MilesAudioManager *>(this)->rva006A20D0(*handle, &event, &info);

		if (accepted)
		{
			if (event == 0 || event->m_flag45)
				accepted = false;
			if (info.ptr != 0 && info.ptr->m_flag34)
				accepted = false;
		}

		*xfer == accepted;
		if (accepted)
		{
			reinterpret_cast<BfmeSubAccept_0002C41C *>(event)->bfmeAccept(
				reinterpret_cast<BfmeSeedTarget *>(xfer));
		}

	}
	else
	{
		AudioManagerMutex guard(m_mutex);
		bool hasEvent;
		*xfer == hasEvent;
		if (hasEvent)
		{
			AudioEventRTS event(TheBfmeCrateNameDefault, 0);
			reinterpret_cast<BfmeSubAccept_0002C41C *>(&event)->bfmeAccept(
				 reinterpret_cast<BfmeSeedTarget *>(xfer));
			*handle = event.m_playingHandle;
		}
		else
		{
			*handle = 1;
		}
	}
}

// ?bfmeOneTED@BfmeThingTED@@QAEXH@Z
// partial score=0.25 date=2026-09-18
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail 0x006A9200 is a 0x49B-byte, ret-4 audio-owner operation.  The
// matched BfmeThingTED::bfmeGoTED caller reaches it through the pinned
// bfmeOneTED(int) ILT at 0x0003E045, which proves the public method spelling
// used here.  The body boundary is the ret 4 at +0x498; the supplied 1168B
// generated row ended in the middle of the EH epilogue.
//
// The owner offsets are witnessed by the adjacent Miles audio conversions:
// the event vectors begin at +0x94, the quick-handle list is at +0x9BC, the
// three playing lists are at +0x9C8/+0x9CC/+0x9D0, and the six 0x28-byte
// deques begin at +0x9D4.  The retail callees are kept at their ledger names:
// the release helper is the ILT j_0002669d, vector copy is j_00044396, and
// the event destructor is j_00026f35.

#define _STLP_NO_EXCEPTIONS 1
#include <deque>
#include <list>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(
	long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);
extern "C" __declspec(dllimport) void __stdcall AIL_quick_unload(void *handle);

class Rva006A9200Counted
{
public:
	virtual ~Rva006A9200Counted();

	void Add_Ref(void)
	{
		InterlockedIncrement(&m_refCount);
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
	~AudioEventRTS();

	unsigned char m_pad000[0x28];
	int m_soundType;
	unsigned char m_pad02c[0x78 - 0x2c];
};

class Rva006A9200PlayingAudio : public Rva006A9200Counted
{
public:
	void *m_milesHandle;
	int m_type;
	int m_status;
	AudioEventRTS *m_audioEventRTS;
};

class Rva006A9200PlayingRef
{
public:
	Rva006A9200PlayingRef(void) : m_pointer(0) {}

	Rva006A9200PlayingRef(const Rva006A9200PlayingRef &other) :
		m_pointer(other.m_pointer)
	{
		if (m_pointer != 0)
			m_pointer->Add_Ref();
	}

	~Rva006A9200PlayingRef(void)
	{
		if (m_pointer != 0)
			m_pointer->Release_Ref();
	}

	Rva006A9200PlayingRef &operator=(const Rva006A9200PlayingRef &other)
	{
		if (this != &other)
		{
			if (other.m_pointer != 0)
				other.m_pointer->Add_Ref();
			if (m_pointer != 0)
				if (InterlockedDecrement(&m_pointer->m_refCount) <= 0)
					delete m_pointer;
			m_pointer = other.m_pointer;
		}
		return *this;
	}

	operator Rva006A9200PlayingAudio *(void) const
	{
		return (Rva006A9200PlayingAudio *)m_pointer;
	}

	Rva006A9200PlayingAudio *operator->(void) const
	{
		return (Rva006A9200PlayingAudio *)m_pointer;
	}

	Rva006A9200Counted *m_pointer;
};

struct Rva006A9200EventVectorElement
{
	~Rva006A9200EventVectorElement();

	unsigned char m_pad000[0x28];
	int m_soundType;
	unsigned char m_pad02c[0x78 - 0x2c];
};

// The retail vector helper is an out-of-line STLport instantiation.  Keep the
// call out of this TU so MSVC 7.1 does not inline the copy loop into the owner
// body; its linker alias below gives the call the retail ILT target.
extern "C" Rva006A9200EventVectorElement *Rva006A9200EventVectorCopy(
	Rva006A9200EventVectorElement *first,
	Rva006A9200EventVectorElement *last,
	Rva006A9200EventVectorElement *result,
	const _STL::random_access_iterator_tag &tag,
	int *distance);

class Rva006A9200EventVector
{
public:
	Rva006A9200EventVectorElement *m_start;
	Rva006A9200EventVectorElement *m_finish;
	Rva006A9200EventVectorElement *m_endOfStorage;
};

typedef _STL::list<Rva006A9200PlayingRef> Rva006A9200PlayingList;
typedef _STL::deque<Rva006A9200PlayingRef> Rva006A9200PlayingDeque;
typedef _STL::list<void *> Rva006A9200QuickList;

class BfmeThingTED
{
public:
	void bfmeOneTED(int flags);

	void releasePlayingAudio(Rva006A9200PlayingAudio *playing);

private:
	char m_pad000[0x94];
	Rva006A9200EventVector m_events[3];
	char m_pad0b8[0x9bc - 0xb8];
	Rva006A9200QuickList m_quickAudio;
	Rva006A9200QuickList m_availableSamples;
	Rva006A9200QuickList m_available3DSamples;
	Rva006A9200PlayingList m_playingSounds;
	Rva006A9200PlayingList m_playing3DSounds;
	Rva006A9200PlayingList m_playingStreams;
	Rva006A9200PlayingDeque m_audioQueues[3][2];
};

#pragma comment(linker, "/alternatename:?releasePlayingAudio@BfmeThingTED@@QAEXPAVRva006A9200PlayingAudio@@@Z=?j_0002669d@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva006A9200EventVectorElement@@QAE@XZ=?j_00026f35@@YAXXZ")
#pragma comment(linker, "/alternatename:_Rva006A9200EventVectorCopy=?j_00044396@@YAXXZ")

void BfmeThingTED::bfmeOneTED(int flags)
{
	Rva006A9200PlayingRef playing;
	Rva006A9200PlayingList::iterator it;

	for (it = m_playingSounds.begin(); it != m_playingSounds.end(); )
	{
		playing = *it;
		if (playing != 0 &&
			(flags & (1 << playing->m_audioEventRTS->m_soundType)) != 0)
		{
			releasePlayingAudio(playing);
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
		if (playing != 0 &&
			(flags & (1 << playing->m_audioEventRTS->m_soundType)) != 0)
		{
			releasePlayingAudio(playing);
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
		if (playing != 0 &&
			(flags & (1 << playing->m_audioEventRTS->m_soundType)) != 0)
		{
			releasePlayingAudio(playing);
			it = m_playingStreams.erase(it);
		}
		else
		{
			++it;
		}
	}

	int group = 0;
	Rva006A9200EventVectorElement **eventFinish = &m_events[0].m_finish;
	Rva006A9200PlayingDeque (*queueGroup)[2] = m_audioQueues;
	while (group < 3)
	{
		if ((flags & (1 << group)) != 0)
		{
			Rva006A9200EventVectorElement *first = eventFinish[-1];
			Rva006A9200EventVectorElement *finish = *eventFinish;
			_STL::random_access_iterator_tag tag;
			Rva006A9200EventVectorElement *newFinish =
				Rva006A9200EventVectorCopy(finish, finish, first, tag,
					(int *)0);
			Rva006A9200EventVectorElement *element = newFinish;
			while (element != finish)
			{
				element->~Rva006A9200EventVectorElement();
				++element;
			}
			*eventFinish = newFinish;

			Rva006A9200PlayingDeque *queue = *queueGroup;
			for (unsigned int queueIndex = 0; queueIndex < 2;
				++queueIndex, ++queue)
			{
				while (!queue->empty())
				{
					releasePlayingAudio(queue->back());
					queue->pop_back();
				}
			}
		}
		++group;
		eventFinish += 3;
		++queueGroup;
	}

	if ((flags & 4) != 0)
	{
		Rva006A9200QuickList::iterator quick = m_quickAudio.begin();
		for (; quick != m_quickAudio.end(); ++quick)
		{
			if (*quick != 0)
				AIL_quick_unload(*quick);
		}
		m_quickAudio.clear();
	}
}

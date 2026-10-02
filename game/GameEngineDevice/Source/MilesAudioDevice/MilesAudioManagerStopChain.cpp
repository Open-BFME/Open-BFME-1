// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// MilesAudioManager bodies 0x006ABDA0..0x006AFD00 and 0x006B2230, kept in one TU in retail
// address order. Retail compiled them together: 0x006AFD00 passes the address
// of its local PlayingAudioRef to 0x006ADD50, which forwards it to 0x006ABFD0
// and 0x006ABDA0, and still keeps the ref pointer in ESI across the call; VC7.1
// only does that when every body that receives the address is visible here.
//
// Owner layout: MilesAudioManagerConstructor.cpp (+0x0C AudioSettings, +0x4C
// request list, +0x50 request set, +0x94 three vectors, +0x624 flag word,
// +0x9C8/+0x9CC/+0x9D0 PlayingAudioRef lists, +0x9D4 six deques, +0xAD0 three
// refs, +0xB00 worker). PlayingAudio/PlayingAudioRef copy the matched stopAudio
// sibling (MilesAudioManagerStopAudio.cpp). Method names stay address-derived.
//
// The +0x624 affect mask is a plain word; 0x006ADD50 clears its bit through a
// reference alias, as the matched sibling MilesAudioManagerRva006B86D0.cpp
// clears +0x61C/+0x624. That keeps retail's test-in-memory then reload.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <vector>
#include <deque>

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long volatile *value);

// Callees whose ledger rows still carry placeholder owners are reached through
// their ILT thunks, as the matched siblings (SubmitAudioEvent006AD790.cpp,
// MilesAudioManagerRva006AF840.cpp) do.
extern void j_00023f79();
extern void j_000256cb();
extern void j_00005a42();
extern void j_0000fa1f();
extern void j_0004066f();
extern void j_00049c01();
extern void j_0003aa6c();
extern void j_000311bf();
extern void j_00001b77();
extern void j_00023911();
extern void j_0001ee7a();
extern void j_00023a38();
extern void j_00002f13();
extern void j_000280f6();
extern void j_00020d24();

extern "C" __declspec(dllimport) void __stdcall AIL_set_stream_loop_count(void *stream, int count);
extern "C" __declspec(dllimport) void __stdcall AIL_start_stream(void *stream);

// Loop count for a stream (Rva006990E0Weight.cpp): the request pointer is in EDX.
struct Rva006990E0Request;
int __fastcall rva006990E0(int unused, Rva006990E0Request *request);

class Rva006ABDA0Call
{
};

template <class Function>
__forceinline Function thunk006ABDA0(void (*raw)())
{
	union { void (*raw)(); Function member; } fn;
	fn.raw = raw;
	return fn.member;
}

// A by-value call through a thunk has to be written at the call site: VC7.1
// does not inline a wrapper that returns an object with a destructor.
#define THUNK_CALL006ABDA0(object, Function, raw) \
	(reinterpret_cast<Rva006ABDA0Call *>(object)->*thunk006ABDA0<Function>(raw))

template <typename T>
class StringBase
{
public:
	int compareNoCase(const StringBase<T> &other) const throw();
	bool isEmpty(void) const { return m_data == 0 || m_data->length == 0; }
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();

	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : public StringBase<char>
{
};

extern const AsciiString Rva01336E50EmptyString;
// Retail VA 0x0112E8B0 is the IEEE binary32 +infinity bits 0x7F800000.
// VC7.1 cannot spell this float with a literal. Its supported union-punning
// behavior lets consumers load the float view of a statically initialized
// four-byte object; both TUs declare the same object type, with no alias.
union Rva0112E8B0Value
{
    unsigned int bits;
    float value;
};
extern const Rva0112E8B0Value g_Va0112E8B0;
// Retail VA 0x0111BB98: bytes 55 55 05 42. The fcomp dword in
// RVA 0x006ABDA0 + 0xF9 proves this four-byte delay threshold.
float g_bfmeElapsedScale = 33.333332061767578125f;

// Refcounted base the event carries at +0x70 (Rva0069B4B0HandleAssignPtr.cpp).
class RefCountedEvent0070
{
public:
	virtual ~RefCountedEvent0070();

	void Add_Ref(void) { InterlockedIncrement(&m_refCount); }

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

private:
	long m_refCount;
};

struct AudioEventInfo
{
	char pad0[0x3c];
	unsigned char m_control;	// +0x3c, bit 0 loops
	char pad3d[0x84 - 0x3d];
	int m_soundType;			// +0x84
};

class AudioEventRTS
{
public:
	void setIsLogicalAudio(bool value);
	bool isPositionalAudio(void) const;
	bool hasMoreLoops(void) const;
	void advanceNextPlayPortion(void);
	void bfmeGenerateFilename(void);

	// 0x000B2860 via ILT 0x00001B77.
	void rva000B2860(float low, float high)
	{
		typedef void (Rva006ABDA0Call::*Function)(float, float);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00001b77))(low, high);
	}
	// 0x000B21F0 via ILT 0x00023911: stores the next play portion.
	void rva000B21F0(int portion)
	{
		typedef void (Rva006ABDA0Call::*Function)(int);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00023911))(portion);
	}

	const AudioEventInfo *getAudioEventInfo(void) const { return m_eventInfo; }

	char pad0[8];
	AudioEventInfo *m_eventInfo;	// +0x08
	unsigned int m_playingHandle;	// +0x0c
	char pad10[0x28 - 0x10];
	int category28;					// +0x28
	char pad2c[0x44 - 0x2c];
	bool m_44;					// +0x44
	bool flag45;				// +0x45
	char pad46[0x54 - 0x46];
	float m_delay;					// +0x54
	char m_pad58[0x60 - 0x58];
	int portion60;						// +0x60, play portion
	int m_64;						// +0x64
	int loops68;						// +0x68
	AsciiString m_6c;				// +0x6c

	RefCountedEvent0070 *refCounted(void) { return reinterpret_cast<RefCountedEvent0070 *>(pad0 + 0x70); }
};


class AudioEventRef
{
public:
	AudioEventRef &operator=(const AudioEventRef &other)
	{
		if (this != &other)
		{
			if (other.ptr)
				other.ptr->refCounted()->Add_Ref();
			if (ptr)
				ptr->refCounted()->Release_Ref();
			ptr = other.ptr;
		}
		return *this;
	}

	AudioEventRTS *operator->(void) const { return ptr; }

	AudioEventRTS *ptr;
};

struct Rva006910F0Target
{
	AsciiString m_name;
};

// PlayingAudio +0x18 / request +0x0C file handle; its bodies are reached
// through their ILT thunks (their ledger rows carry placeholder owners).
class Rva006910F0Handle
{
public:
	~Rva006910F0Handle(void);										// 0x00691130
	// 0x00691140 via ILT 0x0004066F.
	Rva006910F0Handle &operator=(const Rva006910F0Handle &other)
	{
		typedef Rva006910F0Handle &(Rva006ABDA0Call::*Function)(const Rva006910F0Handle &);
		return (reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_0004066f))(other);
	}


	// 0x00691080 via ILT 0x000311BF: drops the file.
	void rva00691080(void)
	{
		typedef void (Rva006ABDA0Call::*Function)();
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_000311bf))();
	}

	const AsciiString &getName(void) const
	{
		return m_file ? m_file->m_name : Rva01336E50EmptyString;
	}

	Rva006910F0Target *m_file;
};


class RefCountedPlayingAudio
{
public:
	virtual ~RefCountedPlayingAudio();

	void Add_Ref(void) { InterlockedIncrement(&m_refCount); }

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
	void *m_milesHandle;			// +0x08
	int m_type;						// +0x0c
	volatile int m_status;			// +0x10
	AudioEventRef m_audioEventRTS;	// +0x14
	Rva006910F0Handle m_file;			// +0x18
	char m_pad1c[0x28 - 0x1c];
	float m_28;						// +0x28
	char pad2c[0x39 - 0x2c];
	bool m_39;						// +0x39
	bool m_3a;						// +0x3a
	bool m_3b;						// +0x3b
	bool m_3c;						// +0x3c
	bool m_3d;						// +0x3d
};

class PlayingAudioRef
{
public:
	PlayingAudioRef(void) : ptr(0) {}
	PlayingAudioRef(const PlayingAudioRef &other) : ptr(other.ptr)
	{
		if (ptr)
			ptr->Add_Ref();
	}
	~PlayingAudioRef(void)
	{
		if (ptr)
			ptr->Release_Ref();
	}
	PlayingAudioRef &operator=(const PlayingAudioRef &other)
	{
		if (this != &other)
		{
			if (other.ptr)
				other.ptr->Add_Ref();
			if (ptr)
				ptr->Release_Ref();
			ptr = other.ptr;
		}
		return *this;
	}
	void clear(void)
	{
		if (ptr)
		{
			ptr->Release_Ref();
			ptr = 0;
		}
	}
	operator PlayingAudio *(void) const { return ptr; }
	PlayingAudio *operator->(void) const { return ptr; }

private:
	PlayingAudio *ptr;
};

struct AudioRequest006A6B40
{
	int m_request;					// +0x00
	AudioEventRef m_pendingEvent;	// +0x04
	unsigned int m_handleToInteractOn;	// +0x08
	Rva006910F0Handle m_file;			// +0x0c
	char m_10;
	bool m_11;
	bool m_12;
	bool m_13;
	int m_14;

	bool matches(unsigned int handle) const
	{
		if (m_pendingEvent.ptr)
			return m_pendingEvent.ptr->m_playingHandle == handle;
		return m_handleToInteractOn == handle;
	}
};

class BfmeHostESG
{
public:
	~BfmeHostESG(void);		// 0x006912A0, the request destructor
};

// 0x78-byte element of the three +0x94 vectors.
struct InlineEvent006AFD00
{
	char pad0[0xc];
	unsigned int m_handle;		// +0x0c
	char pad10[0x74 - 0x10];
	bool byte_74;					// +0x74
	char pad75[3];
};

// Result of the handle lookup 0x006A1650 in the +0x50 set.
struct Node006AFD00
{
	Node006AFD00 *m_next;
	AudioRequest006A6B40 *value;
};

struct SelfPair006A1650
{
	Node006AFD00 *m_node;
	void *m_table;
};

struct Rva006A0730InsertResult
{
	void *m_node;
	void *m_table;
	bool m_inserted;
};

// The +0x50 pointer-keyed request set; resize and insert_unique_noresize are
// reached through their ILT thunks.
class Rva006A43D0RequestTable
{
public:
	void insert(AudioRequest006A6B40 *const &value)
	{
		rva006A43D0(m_numElements + 1);
		Rva006A0730InsertResult result;
		rva006A0730(&result, value);
	}

	// resize, 0x006A43D0 via ILT 0x000256CB
	void rva006A43D0(unsigned int hint)
	{
		typedef void (Rva006ABDA0Call::*Function)(unsigned int);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_000256cb))(hint);
	}

	// insert_unique_noresize, 0x006A0730 via ILT 0x00005A42
	void rva006A0730(Rva006A0730InsertResult *result, AudioRequest006A6B40 *const &request)
	{
		typedef void (Rva006ABDA0Call::*Function)(Rva006A0730InsertResult *, AudioRequest006A6B40 *const &);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00005a42))(result, request);
	}

	// 0x006A1650 via ILT 0x0001EE7A: find the request for a handle.
	void rva006A1650(SelfPair006A1650 *found, unsigned int handle)
	{
		typedef void (Rva006ABDA0Call::*Function)(SelfPair006A1650 *, unsigned int);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_0001ee7a))(found, handle);
	}

	// 0x006A0810 via ILT 0x00023A38: erase the found node.
	void rva006A0810(SelfPair006A1650 *found)
	{
		typedef void (Rva006ABDA0Call::*Function)(SelfPair006A1650 *);
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00023a38))(found);
	}

private:
	char m_functors[4];
	void *m_buckets[3];
	unsigned int m_numElements;
};


// list<PlayingAudioRef>::erase stays out of line: 0x0069DBE0 via ILT 0x00020D24.
#pragma comment(linker, "/alternatename:?erase@?$list@VPlayingAudioRef@@V?$allocator@VPlayingAudioRef@@@_STL@@@_STL@@QAE?AU?$_List_iterator@VPlayingAudioRef@@U?$_Nonconst_traits@VPlayingAudioRef@@@_STL@@@2@U32@@Z=?j_00020d24@@YAXXZ")

class AudioSettings
{
public:
	char pad0[0x3c];
	int m_fadeAudioFrames;
};

class Rva00694710AudioWorker
{
public:
};


// Retail callers use ILT 0x0002669D -> 0x006A59F0, a thiscall with one
// PlayingAudio pointer. The old member declaration had no linked provider.
extern void j_0002669d();
template <class Function>
__forceinline Function rva006A59F0Thunk()
{
    union { void (*raw)(); Function member; } fn;
    fn.raw = j_0002669d;
    return fn.member;
}

class MilesAudioManager
{
public:
	void rva006ABDA0(PlayingAudioRef *playing);
	bool rva006ABFD0(PlayingAudioRef *playing);
	void rva006ADD50(PlayingAudioRef *playing);
	void rva006AE250(PlayingAudioRef *playing);
	void rva006AFD00(unsigned int handle);
	bool rva006B2230(AudioEventRTS *event);


private:
	// 0x006955C0 via ILT 0x00023F79: a new 0x18-byte request.
	AudioRequest006A6B40 *rva006955C0(void)
	{
		typedef AudioRequest006A6B40 *(Rva006ABDA0Call::*Function)();
		return (reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00023f79))();
	}

	char m_pad000[0xc];
	AudioSettings *m_audioSettings;		// +0x00c
	char m_pad010[0x4c - 0x10];
	_STL::list<AudioRequest006A6B40 *> m_requests;	// +0x04c
	Rva006A43D0RequestTable m_requestTable;	// +0x050
	char m_pad064[0x94 - 0x64];
	_STL::vector<InlineEvent006AFD00> m_vectors094[3];	// +0x094
	char m_pad0b8[0x624 - 0xb8];
	unsigned int flags624;				// +0x624, affect mask
	// 0x006A5570 via ILT 0x00002F13.
	void rva006A5570(void)
	{
		typedef void (Rva006ABDA0Call::*Function)();
		(reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00002f13))();
	}

	// 0x006B1FC0 via ILT 0x000280F6: ZH findLowestPrioritySound, the playing event of lowest priority.
	AudioEventRTS *findLowestPrioritySound(AudioEventRTS *event)
	{
		typedef AudioEventRTS *(Rva006ABDA0Call::*Function)(AudioEventRTS *);
		return (reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_000280f6))(event);
	}

	char m_pad628[0x9c4 - 0x628];
	_STL::list<void *> m_list9c4;				// +0x9c4
	_STL::list<PlayingAudioRef> m_list9c8;		// +0x9c8
	_STL::list<PlayingAudioRef> m_list9cc;		// +0x9cc
	_STL::list<PlayingAudioRef> m_list9d0;		// +0x9d0
	_STL::deque<PlayingAudioRef> m_queues[3][2];	// +0x9d4
	unsigned int m_ac4[3];						// +0xac4
	PlayingAudioRef m_ad0[3];					// +0xad0
	char m_padadc[0xb00 - 0xadc];
	Rva00694710AudioWorker *m_worker;	// +0xb00
};


void MilesAudioManager::rva006ABDA0(PlayingAudioRef *playing)
{
	(*playing)->m_status = 1;
	AudioRequest006A6B40 *request = rva006955C0();
	request->m_request = 0;
	AudioRequest006A6B40 *queued = request;
	request->m_pendingEvent = (*playing)->m_audioEventRTS;
	request->m_11 = true;
	if ((*playing)->m_audioEventRTS->getAudioEventInfo()->m_soundType == 2)
	{
		// 0x000B3BF0 (ILT 0x0000FA1F): the event's file name for this play portion.
		typedef AsciiString (Rva006ABDA0Call::*FileName)();
		// 0x006910A0 (ILT 0x00049C01): a copy of the playing file handle.
		typedef Rva006910F0Handle (Rva006ABDA0Call::*CopyHandle)();
		// 0x00694130 (ILT 0x0003AA6C): the worker opens a handle for the event.
		typedef Rva006910F0Handle (Rva006ABDA0Call::*OpenHandle)(const AudioEventRef &, int);
		if (THUNK_CALL006ABDA0(request->m_pendingEvent.ptr, FileName, j_0000fa1f)().compareNoCase((*playing)->m_file.getName()) == 0)
			request->m_file = THUNK_CALL006ABDA0(&(*playing)->m_file, CopyHandle, j_00049c01)();
		else
			request->m_file = THUNK_CALL006ABDA0(m_worker, OpenHandle, j_0003aa6c)(request->m_pendingEvent, request->m_pendingEvent->m_delay >= g_bfmeElapsedScale ? 0 : 1);
	}
	request->m_12 = (*playing)->m_39;
	request->m_13 = (*playing)->m_3a;
	if ((*playing)->m_28 >= m_audioSettings->m_fadeAudioFrames)
		request->m_pendingEvent->setIsLogicalAudio(true);
	request->m_handleToInteractOn = request->m_pendingEvent->m_playingHandle;
	m_requestTable.insert(queued);
}

// 0x006ABFD0: restart a finished loop unless the audio is a stream.
bool MilesAudioManager::rva006ABFD0(PlayingAudioRef *playing)
{
	if ((*playing)->m_type != 2)
	{
		(*playing)->m_file.rva00691080();
		if ((*playing)->m_audioEventRTS->hasMoreLoops())
		{
			(*playing)->m_audioEventRTS->bfmeGenerateFilename();
			rva006ABDA0(playing);
			return true;
		}
	}
	return false;
}

// 0x006ADD50: a playing audio reached the end of its current portion.
void MilesAudioManager::rva006ADD50(PlayingAudioRef *playing)
{
	if (!*playing)
		return;
	unsigned int bit = 1 << (*playing)->m_audioEventRTS->category28;
	unsigned int &bits = flags624;
	if ((flags624 & bit) && (*playing)->m_audioEventRTS->getAudioEventInfo()->m_soundType == 1)
		bits &= ~bit;
	if ((*playing)->m_audioEventRTS->getAudioEventInfo()->m_control & 1)
	{
		if ((*playing)->m_audioEventRTS->portion60 == 0)
			(*playing)->m_audioEventRTS->rva000B21F0(1);
		if ((*playing)->m_audioEventRTS->portion60 == 1 && rva006ABFD0(playing))
			return;
	}
	(*playing)->m_audioEventRTS->advanceNextPlayPortion();
	PlayingAudio *audio = *playing;
	AudioEventRTS *event = audio->m_audioEventRTS.ptr;
	if (event->portion60 != 3 && audio->m_type != 3)
	{
		event->bfmeGenerateFilename();
		rva006ABDA0(playing);
		return;
	}
	if (audio->m_type == 3 && !event->flag45)
	{
		bool loops;
		switch (event->getAudioEventInfo()->m_soundType)
		{
		case 0:
			loops = event->loops68 == -1;
			break;
		case 1:
		case 4:
			loops = (event->getAudioEventInfo()->m_control & 1) != 0;
			break;
		case 3:
			loops = true;
			break;
		default:
			loops = false;
			break;
		}
		if (loops)
		{
			AIL_set_stream_loop_count(audio->m_milesHandle, rva006990E0((int)event, (Rva006990E0Request *)event));
			AIL_start_stream((*playing)->m_milesHandle);
			return;
		}
	}
	if (!event->flag45 && !event->m_6c.isEmpty())
		audio->m_3d = true;
	(*playing)->m_status = 1;
}

// 0x006AE250
void MilesAudioManager::rva006AE250(PlayingAudioRef *playing)
{
	(*playing)->m_audioEventRTS->bfmeGenerateFilename();
	if ((*playing)->m_audioEventRTS->hasMoreLoops())
	{
		(*playing)->m_audioEventRTS->advanceNextPlayPortion();
		(*playing)->m_audioEventRTS->rva000B2860(34.3333321f, g_Va0112E8B0.value);
		(*playing)->m_audioEventRTS->m_44 = true;
		rva006ABDA0(playing);
	}
}

// 0x006AFD00: stop everything playing, queued or requested for one handle.
void MilesAudioManager::rva006AFD00(unsigned int handle)
{
	if (handle < 5)
		return;
	for (_STL::list<PlayingAudioRef>::iterator it = m_list9d0.begin(); it != m_list9d0.end(); ++it)
	{
		PlayingAudioRef audio = *it;
		if (!audio)
			continue;
		if (audio->m_audioEventRTS->m_playingHandle == handle)
		{
			audio->m_audioEventRTS->flag45 = true;
			if (!(audio->m_audioEventRTS->getAudioEventInfo()->m_control & 0x10))
				rva006ADD50(&audio);
			break;
		}
	}
	for (_STL::list<PlayingAudioRef>::iterator it = m_list9c8.begin(); it != m_list9c8.end(); ++it)
	{
		PlayingAudioRef audio = *it;
		if (!audio)
			continue;
		if (audio->m_audioEventRTS->m_playingHandle == handle)
		{
			audio->m_audioEventRTS->flag45 = true;
			break;
		}
	}
	for (_STL::list<PlayingAudioRef>::iterator it = m_list9cc.begin(); it != m_list9cc.end(); ++it)
	{
		PlayingAudioRef audio = *it;
		if (!audio)
			continue;
		if (audio->m_audioEventRTS->m_playingHandle == handle)
		{
			audio->m_audioEventRTS->flag45 = true;
			break;
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		for (_STL::vector<InlineEvent006AFD00>::iterator it = m_vectors094[i].begin(); it != m_vectors094[i].end(); ++it)
		{
			if (it->m_handle == handle)
			{
				it->byte_74 = true;
				break;
			}
		}
		if (m_ad0[i] && m_ad0[i]->m_audioEventRTS->m_playingHandle == handle)
			m_ad0[i].clear();
		for (int j = 0; j < 2; ++j)
		{
			for (_STL::deque<PlayingAudioRef>::iterator it = m_queues[i][j].begin(); it != m_queues[i][j].end(); ++it)
			{
				if (*it && (*it)->m_audioEventRTS->m_playingHandle == handle)
				{
					m_queues[i][j].erase(it);
					break;
				}
			}
		}
	}
	{
		SelfPair006A1650 found;
		m_requestTable.rva006A1650(&found, handle);
		if (found.m_node)
		{
			AudioRequest006A6B40 *request = found.m_node->value;
			SelfPair006A1650 copy = found;
			m_requestTable.rva006A0810(&copy);
			delete (BfmeHostESG *)request;
		}
	}
	for (_STL::list<AudioRequest006A6B40 *>::iterator it = m_requests.begin(); it != m_requests.end(); )
	{
		AudioRequest006A6B40 *request = *it;
		if (request && request->m_request == 0 && request->matches(handle))
		{
			delete (BfmeHostESG *)request;
			it = m_requests.erase(it);
		}
		else
			++it;
	}
}

// 0x006B2230: make room for an event by stopping the lowest-priority sound
// (Zero Hour killLowestPrioritySoundImmediately twin, plus the +0x9C4 check).
bool MilesAudioManager::rva006B2230(AudioEventRTS *event)
{
	if (event->isPositionalAudio())
	{
		rva006A5570();
		if (!m_list9c4.empty())
			return true;
	}
	AudioEventRTS *lowest = findLowestPrioritySound(event);
	if (lowest)
	{
		_STL::list<PlayingAudioRef>::iterator it;
		if (event->isPositionalAudio())
		{
			for (it = m_list9cc.begin(); it != m_list9cc.end(); ++it)
			{
				PlayingAudioRef playing = *it;
				if (!playing)
					continue;
				if (playing->m_audioEventRTS.ptr == lowest)
				{
					if (playing->m_audioEventRTS->hasMoreLoops())
						rva006AE250(&playing);
					(this->*rva006A59F0Thunk<void (MilesAudioManager::*)(PlayingAudio *)>())(playing);
					m_list9cc.erase(it);
					return true;
				}
			}
		}
		else
		{
			for (it = m_list9c8.begin(); it != m_list9c8.end(); ++it)
			{
				PlayingAudioRef playing = *it;
				if (!playing)
					continue;
				if (playing->m_audioEventRTS.ptr == lowest)
				{
					if (playing->m_audioEventRTS->hasMoreLoops())
						rva006AE250(&playing);
					(this->*rva006A59F0Thunk<void (MilesAudioManager::*)(PlayingAudio *)>())(playing);
					m_list9c8.erase(it);
					return true;
				}
			}
		}
	}
	return false;
}

// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// MilesAudioManager bodies 0x006ABDA0..0x006AFD00, kept in one TU in retail
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
extern float g_bfmeElapsedScale;	// 0x0111BB98, milliseconds per logic frame

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
	char m_pad00[0x3c];
	unsigned int m_control;		// +0x3c, bit 0 loops
	char m_pad40[0x84 - 0x40];
	int m_soundType;			// +0x84
};

class AudioEventRTS
{
public:
	void setIsLogicalAudio(bool value);
	const AudioEventInfo *getAudioEventInfo(void) const { return m_eventInfo; }

	char m_pad00[8];
	AudioEventInfo *m_eventInfo;	// +0x08
	unsigned int m_playingHandle;	// +0x0c
	char m_pad10[0x45 - 0x10];
	bool m_requestStop;			// +0x45
	char m_pad46[0x54 - 0x46];
	float m_delay;					// +0x54
	char m_pad58[0x70 - 0x58];

	RefCountedEvent0070 *refCounted(void) { return reinterpret_cast<RefCountedEvent0070 *>(m_pad00 + 0x70); }
};


class AudioEventRef
{
public:
	AudioEventRef &operator=(const AudioEventRef &other)
	{
		if (this != &other)
		{
			if (other.m_ptr)
				other.m_ptr->refCounted()->Add_Ref();
			if (m_ptr)
				m_ptr->refCounted()->Release_Ref();
			m_ptr = other.m_ptr;
		}
		return *this;
	}

	AudioEventRTS *operator->(void) const { return m_ptr; }

	AudioEventRTS *m_ptr;
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
	char m_pad2c[0x39 - 0x2c];
	bool m_39;						// +0x39
	bool m_3a;						// +0x3a
};

class PlayingAudioRef
{
public:
	PlayingAudio *operator->(void) const { return m_ptr; }

private:
	PlayingAudio *m_ptr;
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

private:
	char m_functors[4];
	void *m_buckets[3];
	unsigned int m_numElements;
};


class AudioSettings
{
public:
	char m_pad00[0x3c];
	int m_fadeAudioFrames;
};

class Rva00694710AudioWorker
{
public:
};


class MilesAudioManager
{
public:
	void rva006ABDA0(PlayingAudioRef *playing);

private:
	// 0x006955C0 via ILT 0x00023F79: a new 0x18-byte request.
	AudioRequest006A6B40 *rva006955C0(void)
	{
		typedef AudioRequest006A6B40 *(Rva006ABDA0Call::*Function)();
		return (reinterpret_cast<Rva006ABDA0Call *>(this)->*thunk006ABDA0<Function>(j_00023f79))();
	}

	char m_pad000[0xc];
	AudioSettings *m_audioSettings;		// +0x00c
	char m_pad010[0x50 - 0x10];
	Rva006A43D0RequestTable m_requestTable;	// +0x050
	char m_pad064[0xb00 - 0x64];
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
		if (THUNK_CALL006ABDA0(request->m_pendingEvent.m_ptr, FileName, j_0000fa1f)().compareNoCase((*playing)->m_file.getName()) == 0)
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

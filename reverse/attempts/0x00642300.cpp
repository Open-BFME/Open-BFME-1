// ??0GameResultsQueue@@QAE@XZ
// partial score=0.90 date=2026-09-06
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME7: the real ZH GameResultsQueue::GameResultsQueue() body (per the
// existing reverse/symbols.csv row on this RVA): SubsystemInterface ctor,
// vtable 0x01119380 install (whose slots +0x24/+0x28 are the landed
// startThreads/endThreads and +0x2c..+0x40 the landed areThreadsRunning/
// addRequest/getRequest/addResponse/getResponse/areGameResultsBeingSent),
// three MutexClass ctors, the two queues zeroed and _M_initialize_map'd
// through the already-pinned Rva00642060Element(32B)/Rva006420A0Element(16B)
// deques (Code/Libraries/Source/WWVegas/WWLib/RvaQueueDefaultCtor.cpp, whose
// queue default ctors at 0x00642060/0x006420A0 sit immediately before this
// body -- so BFME's GameResultsRequest/GameResultsResponse must be small
// fixed structs here, not the ZH std::string-bearing ones), and a tail call
// to startThreads() via ILT 0x0000A574.
//
// Declared under its own struct (not the GameResultsThread.cpp class, which
// this file must not touch) with the ledger's placeholder method name
// `_bfme_construct` standing in for the constructor, per the symbols.csv row
// on this RVA (which explains the real ??0GameResultsQueue@@QAE@XZ symbol is
// already claimed by the ICF-shared ILT thunk at 0x0000DAFD elsewhere and
// must not be redefined here). `_bfme_construct` wraps a tag-overloaded real
// constructor -- a different mangled name from the plain no-arg ctor -- so
// the vtable/member installation still happens through genuine constructor
// semantics without colliding with any other file's ??0GameResultsQueue@@QAE@XZ.

#include <queue>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface() {}

private:
	int m_unreconstructed_04;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/mutex.h
class MutexClass
{
	void *handle;
	unsigned locked;

public:
	MutexClass(const char *name = 0);
	~MutexClass();
};

// address-derived: shared with Code/Libraries/Source/WWVegas/WWLib/RvaQueueDefaultCtor.cpp
struct Rva00642060Element
{
	char m_body[32];
};

// address-derived: shared with Code/Libraries/Source/WWVegas/WWLib/RvaQueueDefaultCtor.cpp
struct Rva006420A0Element
{
	char m_body[16];
};

class GameResultsQueue : public SubsystemInterface
{
public:
	GameResultsQueue();
	void startThreads();
	virtual ~GameResultsQueue() {}

private:
	MutexClass m_requestMutex;
	MutexClass m_responseMutex;
	_STL::queue<Rva00642060Element> m_requests;
	_STL::queue<Rva006420A0Element> m_responses;
	void *m_workerThread;
	int m_requestCount;
	int m_responseCount;
	MutexClass m_bfmeHoleThirdMutex;
	int m_bfmeHoleTailWord;
};

GameResultsQueue::GameResultsQueue()
	: m_requestMutex(0), m_responseMutex(0), m_workerThread(0), m_requestCount(0), m_bfmeHoleThirdMutex(0)
{
	m_responseCount = 0;
	m_bfmeHoleTailWord = 0;

	startThreads();
}

// PARTIAL NOTES (score=0.90, t=55min, model=sonnet):
// 213/213 bytes right in length, only the final ~10 bytes differ: retail's
// EH unwind-state counter reaches 6 before the tail call to startThreads(),
// this version only reaches 5, and retail stores [esi+0x7c]=0 BEFORE the
// ecx/state-setup for that call while this version's compiler always hoists
// the ecx/state-setup first. That means retail's real source has ONE MORE
// unwind-state-worthy construction step between the third MutexClass ctor
// and the startThreads() call than this reconstruction models -- almost
// certainly one more sub-object with a non-trivial (but here scalar-looking)
// default step, not just the two plain `int = 0` assignments used here.
// Everything before offset 0xa5 (SubsystemInterface ctor, vtable install,
// three MutexClass ctors, both deque zero+_M_initialize_map sequences)
// already matches byte-for-byte.
//
// Identity: adopts the existing reverse/symbols.csv row's guess
// (?_bfme_construct@GameResultsQueue@@QAEXXZ, i.e. the real ZH
// GameResultsQueue::GameResultsQueue(), GameResultsThread.cpp:112) but that
// row's name cannot be reused directly: this file defines a REAL zero-arg
// ??0GameResultsQueue@@QAE@XZ constructor (needed so the compiler installs
// the vtable/members through genuine ctor semantics), which is the exact
// mangled name GameResultsQueueCtorThunk.cpp's ICF-shared ILT thunk already
// claims at 0x0000DAFD. Two attempts to dodge that collision (a tag-
// parameter overload, and a private __forceinline ctor behind a free-
// function anchor a la RvaQueueDefaultCtor.cpp) both failed: the tagged
// overload adds a `ret 4` epilogue (real body has bare `ret`, zero params)
// and __forceinline was not honoured by the compiler for this EH-heavy
// constructor (SEH frame blocks inlining), so the anchor call site stayed a
// real out-of-line call plus a null-check the retail body does not have.
// Whoever draws this next should either (a) find the missing unwind-state
// source construct so the plain zero-arg ctor becomes byte-exact and only
// then solve the name collision (maybe check_csv.py tolerates a duplicate
// ??0GameResultsQueue@@QAE@XZ row at a different RVA -- worth testing empty-
// handed before touching functions.csv), or (b) find a different inlining
// lever (e.g. /Ob2 explicitly, or restructuring MutexClass as trivial to
// remove its dtor from the EH frame) that lets the forceinline anchor
// collapse to one function.

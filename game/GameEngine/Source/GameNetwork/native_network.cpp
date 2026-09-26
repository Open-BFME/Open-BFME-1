// cl: /DNDEBUG /MD /GX

#include <new>

typedef bool Bool;

class BFMENetworkQueue;
class BFMENetworkQueue1;
class BFMENetwork;
struct BFMENetworkList;

namespace _STL
{
template <class T> class char_traits { };
template <class T> class allocator { };
template <class Char, class Traits, class Allocator>
class basic_string
{
public:
	 basic_string(const basic_string &that);
	 ~basic_string();
};

template <bool threads, int inst>
class __node_alloc
{
	friend struct ::BFMENetworkList;
	static void *_M_allocate(unsigned int bytes);

public:
	static void _M_deallocate(void *p, unsigned int bytes);
};

template <class T, class Allocator>
class deque
{
protected:
	void _M_push_back_aux_v(const T &value);
	friend class ::BFMENetworkQueue;
	friend class ::BFMENetworkQueue1;
	friend class ::BFMENetwork;
};

template <class T1, class T2>
inline void _Construct(T1 *destination, const T2 &value)
{
	new (destination) T1(value);
}
}

typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > BFMENetworkString;

class BFMENetworkLock;
void *BFMENetworkAllocate(unsigned int bytes);

struct BFMENetworkListNode
{
	Bool flag;
	int value;
	BFMENetworkListNode *next;
	BFMENetworkListNode *previous;
};

struct BFMENetworkList
{
	BFMENetworkList() : head(0)
	{
		head = new (_STL::__node_alloc<true, 0>::_M_allocate(0x18)) BFMENetworkListNode;
		size = 0;
		head->flag = false;
		head->value = 0;
		head->next = head;
		head->previous = head;
	}

	BFMENetworkListNode *head;
	int size;
	int allocatorStorage;
};

class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);
    __declspec(noinline) bool Is_Running();
    __declspec(noinline) void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};


class BFMENetworkBackend : public ThreadClass
{
public:
	BFMENetworkBackend(BFMENetworkLock *ownerLock);
	virtual ~BFMENetworkBackend();
	void *destroyAndMaybeDelete(unsigned int flags);
	virtual void Thread_Function();

private:
	Bool m_flag50;
	Bool m_flag51;
	char m_pad52[2];
	int m_value54;
	Bool m_flag58;
	char m_pad59[3];
	BFMENetworkList m_list;
	BFMENetworkLock *m_ownerLock;
};

class BFMENetworkBackendDestructorShim
{
public:
	void destroy();
};

class BFMENetworkLock
{
public:
	BFMENetworkLock(const char *name);
	~BFMENetworkLock();

	void *m_handle;
	int m_refCount;
};

class BFMEAutoLockRef
{
public:
	BFMEAutoLockRef(BFMENetworkLock *lock, unsigned int timeout);
	__declspec(noinline) ~BFMEAutoLockRef();
	Bool failed() const { return m_failed; }

private:
	BFMENetworkLock *m_lock;
	Bool m_failed;
};

class BFMENetworkLockRefOwner
{
public:
	~BFMENetworkLockRefOwner()
	{
		BFMEAutoLockRef *ref = m_ref;
		if (ref)
			delete ref;
	}

	BFMEAutoLockRef *m_ref;
};

class BFMENetworkQueueItem
{
public:
	BFMENetworkQueueItem(const BFMENetworkQueueItem &that);
	void copyFromQueueNode(void *node);
};

class BFMENetworkQueueItem1
{
public:
	BFMENetworkQueueItem1(const BFMENetworkQueueItem1 &that);
	void copyFromQueueNode(void *node);
};

struct BFMENetworkQueuePushFields
{
	char m_padding[0x10];
	char *m_end;
	char *m_first;
	char *m_storageEnd;
};

class BFMENetworkListPayload
{
private:
	char m_data[0x1c4];
};

class BFMENetworkQueue
{
public:
	BFMENetworkQueue()
	{
		m_begin = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_end = 0;
		m_14 = 0;
		m_storageEnd = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
		finishConstruct(0);
	}
	~BFMENetworkQueue();

	Bool empty() const { return m_end == m_begin; }
	__forceinline void pushBack(const BFMENetworkQueueItem &item)
	{
		BFMENetworkQueuePushFields *fields = reinterpret_cast<BFMENetworkQueuePushFields *>(this);
		if (fields->m_end != fields->m_storageEnd - 0x210) {
			_STL::_Construct(reinterpret_cast<BFMENetworkQueueItem *>(fields->m_end), item);
			fields->m_end += 0x210;
		} else {
			reinterpret_cast<_STL::deque<BFMENetworkQueueItem, _STL::allocator<BFMENetworkQueueItem> > *>(this)->_M_push_back_aux_v(item);
		}
	}
	void popFront();
	void finishConstruct(void *unused);

	void *volatile m_begin;
	void *volatile m_04;
	void *volatile m_08;
	void *volatile m_0c;
	char *volatile m_end;
	void *volatile m_14;
	char *volatile m_storageEnd;
	void *volatile m_1c;
	void *volatile m_20;
	void *m_24;
};

class BFMENetworkQueue1
{
public:
	BFMENetworkQueue1()
	{
		m_begin = 0;
		m_04 = 0;
		m_08 = 0;
		m_0c = 0;
		m_end = 0;
		m_14 = 0;
		m_storageEnd = 0;
		m_1c = 0;
		m_20 = 0;
		m_24 = 0;
		finishConstruct(0);
	}
	~BFMENetworkQueue1();

	Bool empty() const { return m_end == m_begin; }
	__forceinline void pushBack(const BFMENetworkQueueItem1 &item)
	{
		BFMENetworkQueuePushFields *fields = reinterpret_cast<BFMENetworkQueuePushFields *>(this);
		if (fields->m_end != fields->m_storageEnd - 0x1f0) {
			_STL::_Construct(reinterpret_cast<BFMENetworkQueueItem1 *>(fields->m_end), item);
			fields->m_end += 0x1f0;
		} else {
			reinterpret_cast<_STL::deque<BFMENetworkQueueItem1, _STL::allocator<BFMENetworkQueueItem1> > *>(this)->_M_push_back_aux_v(item);
		}
	}
	void popFront();
	void finishConstruct(void *unused);

	void *volatile m_begin;
	void *volatile m_04;
	void *volatile m_08;
	void *volatile m_0c;
	char *volatile m_end;
	void *volatile m_14;
	char *volatile m_storageEnd;
	void *volatile m_1c;
	void *volatile m_20;
	void *volatile m_24;
};

class BFMENetworkState
{
public:
	BFMENetworkState();
	__forceinline ~BFMENetworkState()
	{
		char *start = m_start;
		unsigned int bytes = (unsigned int)(m_capacity - start);
		if (start != 0) {
			if (bytes > 128)
				::operator delete(start);
			else
				_STL::__node_alloc<true, 0>::_M_deallocate(start, bytes);
		}
	}

private:
	char *m_start;
	char *m_finish;
	char *m_capacity;
};

struct BFMENetworkPayloadList
{
	BFMENetworkPayloadList() : head(0)
	{
		head = static_cast<BFMENetworkListNode *>(BFMENetworkAllocate(0x1d8));
		size = 0;
		head->flag = false;
		head->value = 0;
		head->next = head;
		head->previous = head;
	}
	~BFMENetworkPayloadList();

	BFMENetworkListNode *head;
	int size;
	int allocatorStorage;
};

class BFMENetworkThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void threadTick();
};

class BFMENetworkBackendThreadRunner
{
public:
	virtual void v00();
	virtual void v04();
	virtual void dispatchEvents();
};

class BFMENetworkInterfaceBase
{
public:
	virtual ~BFMENetworkInterfaceBase()
	{
		*(void **)this = reinterpret_cast<void *>(0x0111985c);
	}
};

class BFMENetwork : public BFMENetworkInterfaceBase
{
public:
	BFMENetwork();
	virtual ~BFMENetwork();
	void *destroyAndMaybeDelete(unsigned int flags);
	void init();
	Bool backendHasLiveHandle();
	void destroyBackend();
	void pushQueue0(BFMENetworkQueueItem *item);
	Bool popQueue0(BFMENetworkQueueItem *item);
	void pushQueue1(BFMENetworkQueueItem1 *item);
	Bool popQueue1(BFMENetworkQueueItem1 *item);
	BFMENetworkString copyState6C();
	BFMENetworkString copyState78();
	BFMENetworkString copyState84();

private:
	BFMENetworkLock m_lock0;
	BFMENetworkLock m_lock1;
	BFMENetworkQueue m_queue0;
	BFMENetworkQueue1 m_queue1;
	BFMENetworkBackend *m_backend;
	void *m_unknown68;
	BFMENetworkState m_state6c;
	BFMENetworkState m_state78;
	BFMENetworkState m_state84;
	BFMENetworkPayloadList m_list90;
	BFMENetworkLock m_lock9c;
	BFMENetworkLockRefOwner m_backendLockRef;
};

class BFMENetworkDestructorShim
{
public:
	void destroy();
};

extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern "C" unsigned int __stdcall BFMENetworkBackendThreadStart(void *backend)
{
	BFMENetworkThreadRunner *globalNetwork = *reinterpret_cast<BFMENetworkThreadRunner **>(0x01336e5c);
	globalNetwork->threadTick();
	reinterpret_cast<BFMENetworkBackendThreadRunner *>(backend)->dispatchEvents();
	return 0;
}

BFMENetworkBackend::BFMENetworkBackend(BFMENetworkLock *ownerLock) :
	ThreadClass(0),
	m_ownerLock(ownerLock)
{
	m_flag51 = false;
	m_flag58 = false;
	m_flag50 = false;
	m_value54 = 0;
}

void *BFMENetworkBackend::destroyAndMaybeDelete(unsigned int flags)
{
	void *self = this;
	((BFMENetworkBackendDestructorShim *)self)->destroy();
	if (flags & 1) {
		::operator delete(self);
	}
	return self;
}

Bool BFMENetwork::backendHasLiveHandle()
{
	if (m_backend) {
		return m_backend->Is_Running();
	}
	return false;
}

void BFMENetwork::destroyBackend()
{
	if (m_backend) {
		if (m_backendLockRef.m_ref) {
			delete m_backendLockRef.m_ref;
		}
		BFMENetworkBackend *volatile *backendSlot = &m_backend;
		m_backendLockRef.m_ref = 0;
		(*backendSlot)->Stop();
		if (m_backend) {
			delete m_backend;
		}
	}
	m_backend = 0;
}

void *BFMENetwork::destroyAndMaybeDelete(unsigned int flags)
{
	void *self = this;
	((BFMENetworkDestructorShim *)self)->destroy();
	if (flags & 1) {
		::operator delete(self);
	}
	return self;
}

BFMENetwork::BFMENetwork() :
	m_lock0(0),
	m_lock1(0),
	m_lock9c(0)
{
	m_backendLockRef.m_ref = 0;
	m_backend = 0;
	m_unknown68 = 0;
}

// The ledger retains a shim alias with this destructor as its object-symbol.
// ?destroy@BFMENetworkDestructorShim@@QAEXXZ
BFMENetwork::~BFMENetwork()
{
	if (m_backend) {
		if (m_backendLockRef.m_ref) {
			delete m_backendLockRef.m_ref;
		}
		BFMENetworkBackend *volatile *backendSlot = &m_backend;
		m_backendLockRef.m_ref = 0;
		(*backendSlot)->Stop();
		if (m_backend) {
			delete m_backend;
		}
	}
	m_backend = 0;
}

void BFMENetwork::init()
{
	if (m_backend) {
		return;
	}

	BFMEAutoLockRef *lockRef = new BFMEAutoLockRef(&m_lock9c, -1);
	if (lockRef != m_backendLockRef.m_ref) {
		delete m_backendLockRef.m_ref;
		m_backendLockRef.m_ref = lockRef;
	}

	m_backend = new BFMENetworkBackend(&m_lock9c);
	m_backend->Execute();
}

void BFMENetwork::pushQueue0(BFMENetworkQueueItem *item)
{
	BFMEAutoLockRef lock(&m_lock0, -1);

	if (!lock.failed()) {
		m_queue0.pushBack(*item);
	}
}

Bool BFMENetwork::popQueue0(BFMENetworkQueueItem *item)
{
	BFMEAutoLockRef lock(&m_lock0, 2);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue *queue = &m_queue0;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

void BFMENetwork::pushQueue1(BFMENetworkQueueItem1 *item)
{
	BFMEAutoLockRef lock(&m_lock1, -1);

	if (!lock.failed()) {
		m_queue1.pushBack(*item);
	}
}

Bool BFMENetwork::popQueue1(BFMENetworkQueueItem1 *item)
{
	BFMEAutoLockRef lock(&m_lock1, 0);

	if (lock.failed()) {
		return false;
	}

	BFMENetworkQueue1 *queue = &m_queue1;
	if (queue->empty()) {
		return false;
	}

	void *node = queue->m_begin;
	item->copyFromQueueNode(node);
	queue->popFront();
	return true;
}

BFMENetworkString BFMENetwork::copyState6C()
{
	return *reinterpret_cast<const BFMENetworkString *>(reinterpret_cast<const char *>(this) + 0x6c);
}

BFMENetworkString BFMENetwork::copyState78()
{
	return *reinterpret_cast<const BFMENetworkString *>(reinterpret_cast<const char *>(this) + 0x78);
}

BFMENetworkString BFMENetwork::copyState84()
{
	return *reinterpret_cast<const BFMENetworkString *>(reinterpret_cast<const char *>(this) + 0x84);
}

__declspec(noinline) BFMEAutoLockRef::~BFMEAutoLockRef()
{
	if (!m_failed) {
		BFMENetworkLock *lock = m_lock;
		--lock->m_refCount;
		ReleaseMutex(lock->m_handle);
	}
}

// cl: /DNDEBUG /MD /GX
// readable body of ?Is_Running@ThreadClass@@: Code/Libraries/Source/WWVegas/WWLib/thread.cpp

#include <new>

typedef bool Bool;

class BFMENetworkQueue;
class BFMENetworkQueue1;
class BFMENetwork;

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
		head = static_cast<BFMENetworkListNode *>(::operator new(0x18));
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

class BFMENetworkThreadBase
{
public:
	BFMENetworkThreadBase(const char *name);
	virtual ~BFMENetworkThreadBase();
	virtual void start();

protected:
	char m_threadName[0x40];
	void *m_auxHandle;
	void *m_liveHandle;
	int m_threadPriority;
};

class BFMENetworkBackend : public BFMENetworkThreadBase
{
public:
	BFMENetworkBackend(BFMENetworkLock *ownerLock);
	virtual ~BFMENetworkBackend();
	void *destroyAndMaybeDelete(unsigned int flags);
	void openLiveHandle();
	__declspec(noinline) Bool hasLiveHandle();
	__declspec(noinline) void closeLiveHandle();

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
	~BFMENetworkState();

private:
	int m_data[3];
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
	virtual ~BFMENetworkInterfaceBase();
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
	BFMEAutoLockRef *m_backendLockRef;
};

class BFMENetworkDestructorShim
{
public:
	void destroy();
};

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long milliseconds);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void *handle);

extern "C" unsigned long __stdcall BFMENetworkBackendThreadStart(BFMENetworkBackend *backend)
{
	BFMENetworkThreadRunner *globalNetwork = *reinterpret_cast<BFMENetworkThreadRunner **>(0x01336e5c);
	globalNetwork->threadTick();
	reinterpret_cast<BFMENetworkBackendThreadRunner *>(backend)->dispatchEvents();
	return 0;
}

BFMENetworkBackend::BFMENetworkBackend(BFMENetworkLock *ownerLock) :
	BFMENetworkThreadBase(0),
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

void BFMENetworkBackend::openLiveHandle()
{
	typedef void *(*CreateThreadProc)(void *, unsigned long, unsigned long (__stdcall *)(BFMENetworkBackend *), BFMENetworkBackend *, unsigned long, unsigned long *);
	typedef int (__stdcall *SetThreadPriorityProc)(void *, int);
	typedef int (__stdcall *CloseHandleProc)(void *);

	m_liveHandle = (*reinterpret_cast<CreateThreadProc *>(0x01359298))(
		0, 0, BFMENetworkBackendThreadStart, this, 4, reinterpret_cast<unsigned long *>(reinterpret_cast<char *>(this) + 0x44));
	(*reinterpret_cast<SetThreadPriorityProc *>(0x01358f20))(m_liveHandle, *reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x4c));
	(*reinterpret_cast<CloseHandleProc *>(0x01358ed4))(m_liveHandle);
}

extern "C" __declspec(naked) void __stdcall BFMENetworkBackendEventCallback(void *a0, void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7, void *a8, void *a9)
{
	__asm {
		__emit 0x6a
		__emit 0xff
		__emit 0x68
		__emit 0xf8
		__emit 0x2c
		__emit 0x04
		__emit 0x01
		__emit 0x64
		__emit 0xa1
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x50
		__emit 0x64
		__emit 0x89
		__emit 0x25
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xec
		__emit 0x24
		__emit 0x55
		__emit 0x56
		__emit 0x57
		__emit 0x8b
		__emit 0xf1
		__emit 0xc6
		__emit 0x46
		__emit 0x50
		__emit 0x00
		__emit 0xc6
		__emit 0x46
		__emit 0x51
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xb4
		__emit 0x71
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x01
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x02
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xff
		__emit 0x50
		__emit 0x2c
		__emit 0x50
		__emit 0xe8
		__emit 0xb2
		__emit 0xf9
		__emit 0x1f
		__emit 0x00
		__emit 0x8b
		__emit 0x0d
		__emit 0xb4
		__emit 0x71
		__emit 0x2f
		__emit 0x01
		__emit 0x8b
		__emit 0x11
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8b
		__emit 0xf8
		__emit 0xff
		__emit 0x52
		__emit 0x30
		__emit 0x50
		__emit 0xe8
		__emit 0x9c
		__emit 0xf9
		__emit 0x1f
		__emit 0x00
		__emit 0x8b
		__emit 0xe8
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8d
		__emit 0x44
		__emit 0x24
		__emit 0x0c
		__emit 0x50
		__emit 0x55
		__emit 0x6a
		__emit 0x00
		__emit 0xe8
		__emit 0x7a
		__emit 0xef
		__emit 0x37
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x50
		__emit 0xe8
		__emit 0x81
		__emit 0xe0
		__emit 0x37
		__emit 0x00
		__emit 0x8b
		__emit 0x54
		__emit 0x24
		__emit 0x4c
		__emit 0x56
		__emit 0x68
		__emit 0xe0
		__emit 0x17
		__emit 0xa5
		__emit 0x00
		__emit 0x8d
		__emit 0x4c
		__emit 0x24
		__emit 0x20
		__emit 0x51
		__emit 0x57
		__emit 0x52
		__emit 0xe8
		__emit 0xcb
		__emit 0x02
		__emit 0x38
		__emit 0x00
		__emit 0x57
		__emit 0x8b
		__emit 0x3d
		__emit 0xd4
		__emit 0x93
		__emit 0x35
		__emit 0x01
		__emit 0xff
		__emit 0xd7
		__emit 0x55
		__emit 0xff
		__emit 0xd7
		__emit 0x8a
		__emit 0x46
		__emit 0x51
		__emit 0x83
		__emit 0xc4
		__emit 0x28
		__emit 0x84
		__emit 0xc0
		__emit 0x75
		__emit 0x1a
		__emit 0xeb
		__emit 0x03
		__emit 0x8d
		__emit 0x49
		__emit 0x00
		__emit 0xe8
		__emit 0xfb
		__emit 0xe0
		__emit 0x37
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x0c
		__emit 0xe8
		__emit 0x42
		__emit 0x09
		__emit 0x38
		__emit 0x00
		__emit 0x8a
		__emit 0x46
		__emit 0x51
		__emit 0x84
		__emit 0xc0
		__emit 0x74
		__emit 0xeb
		__emit 0x8a
		__emit 0x46
		__emit 0x50
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x44
		__emit 0x88
		__emit 0x44
		__emit 0x24
		__emit 0x40
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x4c
		__emit 0x5f
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0x5e
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x30
		__emit 0x01
		__emit 0x5d
		__emit 0x74
		__emit 0x1c
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x0b
		__emit 0x51
		__emit 0xe8
		__emit 0x11
		__emit 0xd4
		__emit 0x22
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x0a
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0x45
		__emit 0x9b
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x44
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x4c
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0xc6
		__emit 0x44
		__emit 0x24
		__emit 0x2c
		__emit 0x00
		__emit 0x74
		__emit 0x1c
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x0b
		__emit 0x51
		__emit 0xe8
		__emit 0xe2
		__emit 0xd3
		__emit 0x22
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0xeb
		__emit 0x0a
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0x16
		__emit 0x9b
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x50
		__emit 0x8b
		__emit 0x44
		__emit 0x24
		__emit 0x58
		__emit 0x2b
		__emit 0xc1
		__emit 0x85
		__emit 0xc9
		__emit 0xc7
		__emit 0x44
		__emit 0x24
		__emit 0x2c
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0xff
		__emit 0x74
		__emit 0x2f
		__emit 0x3d
		__emit 0x80
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x76
		__emit 0x1e
		__emit 0x51
		__emit 0xe8
		__emit 0xb0
		__emit 0xd3
		__emit 0x22
		__emit 0x00
		__emit 0x8a
		__emit 0x44
		__emit 0x24
		__emit 0x38
		__emit 0x83
		__emit 0xc4
		__emit 0x04
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x30
		__emit 0xc2
		__emit 0x28
		__emit 0x00
		__emit 0x50
		__emit 0x51
		__emit 0xe8
		__emit 0xd1
		__emit 0x9a
		__emit 0x1d
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x08
		__emit 0x8b
		__emit 0x4c
		__emit 0x24
		__emit 0x24
		__emit 0x8a
		__emit 0x44
		__emit 0x24
		__emit 0x34
		__emit 0x64
		__emit 0x89
		__emit 0x0d
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0x83
		__emit 0xc4
		__emit 0x30
		__emit 0xc2
		__emit 0x28
		__emit 0x00
	}
}

__declspec(noinline) Bool BFMENetworkBackend::hasLiveHandle()
{
	void *liveHandle = m_liveHandle;
	return liveHandle != 0;
}

__declspec(noinline) void BFMENetworkBackend::closeLiveHandle()
{
	if (m_liveHandle) {
		WaitForSingleObject(m_liveHandle, 0xffffffff);
		m_liveHandle = 0;
		m_auxHandle = 0;
	}
}

Bool BFMENetwork::backendHasLiveHandle()
{
	if (m_backend) {
		return m_backend->hasLiveHandle();
	}
	return false;
}

void BFMENetwork::destroyBackend()
{
	if (m_backend) {
		if (m_backendLockRef) {
			delete m_backendLockRef;
		}
		BFMENetworkBackend *volatile *backendSlot = &m_backend;
		m_backendLockRef = 0;
		(*backendSlot)->closeLiveHandle();
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
	m_backendLockRef = 0;
	m_backend = 0;
	m_unknown68 = 0;
}

void BFMENetwork::init()
{
	if (m_backend) {
		return;
	}

	BFMEAutoLockRef *lockRef = new BFMEAutoLockRef(&m_lock9c, -1);
	if (lockRef != m_backendLockRef) {
		delete m_backendLockRef;
		m_backendLockRef = lockRef;
	}

	m_backend = new BFMENetworkBackend(&m_lock9c);
	m_backend->start();
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
